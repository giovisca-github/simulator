#include "bridge/bridge.hpp"

#include "common/math_stuff.hpp"

// constructor
UnityBridge::UnityBridge()
    : client_address_("tcp://*"), pub_port_("10253"), sub_port_("10254") {
  initializeConnection();
}

bool UnityBridge::initializeConnection() {
  std::cout << "Initializing Connection\n";

  pub_.set(zmqpp::socket_option::send_high_water_mark, 6);
  pub_.bind(client_address_ + ":" + pub_port_);

  sub_.set(zmqpp::socket_option::receive_high_water_mark, 6);
  sub_.bind(client_address_ + ":" + sub_port_);
  sub_.subscribe("");

  std::cout << "connection initialed\n";
  return true;
}

bool UnityBridge::connectUnity() {  // test communication in both direction so
                                    // first send, then wait for a response
                                    // related to the message sent
  std::cout << "trying to connect to unity ";
  while (!unity_ready) {
    std::cout << "---";
    std::cout.flush();
    sendSettings();
    unity_ready = receiveFirstMessage();
    usleep(0.5e6);
  }
  std::cout << "\n connected!\n";
  return unity_ready;
};

bool UnityBridge::sendSettings() {
  zmqpp::message message;
  SettingMessage setting_msg;
  setting_msg.initialization_msg = pub_msg_;
  setting_msg.setings = settings_;

  json json_msg = setting_msg;
  // std::cout << json_msg.dump();
  message << "InitialSettings" << json_msg.dump();
  pub_.send(message, true);
  return true;
};

bool UnityBridge::receiveFirstMessage() {
  zmqpp::message msg;

  bool done = false;

  if (sub_.receive(msg, true)) {
    std::string metadata_string = msg.get(0);
    // if (json::parse(metadata_string).size() > 1) {
    //   return false;  // hack
    // }
    done = json::parse(metadata_string).at("ready").get<bool>();
  }
  return done;
};

bool UnityBridge::addCar(std::shared_ptr<Car> car) {
  Vehicle vehicles_t;
  CarState car_state;
  if (!car->getState(car_state)) {
    std::cerr << "Error in adding car, no states set for the car!!\n";
    return false;
  }
  // each vehile is called "car<number>"
  vehicles_t.ID = "car" + std::to_string(pub_msg_.vehicles.size());
  vehicles_t.position = position2Unity(car_state.p);
  vehicles_t.rotation = quaternion2Unity(car_state.q());
  vehicles_t.is_kinematic = car->getPhysicEngine();
  if (vehicles_t.is_kinematic) vehicles_t.commands = car->getCommands();

  unity_cars_.push_back(car);

  pub_msg_.vehicles.push_back(vehicles_t);
  return true;
};

bool UnityBridge::sendToUnity() {
  CarState car_state;

  for (size_t idx = 0; idx < pub_msg_.vehicles.size(); idx++) {
    if (pub_msg_.vehicles[idx].is_kinematic) {
      unity_cars_[idx]->getState(car_state);
      pub_msg_.vehicles[idx].position = position2Unity(car_state.p);
      pub_msg_.vehicles[idx].rotation = quaternion2Unity(car_state.q());
    } else {
      pub_msg_.vehicles[idx].commands = unity_cars_[idx]->getCommands();
    }
  }
  zmqpp::message msg;
  msg << "Update";
  json json_msg = pub_msg_;
  msg << json_msg.dump();
  std::cout << json_msg.dump(1);
  pub_.send(msg, true);
  return true;
};

bool UnityBridge::receiveFromUnity() {
  zmqpp::message msg;
  sub_.receive(msg);

  std::string json_sub_msg = msg.get(0);

  SubMessage sub_msg = json::parse(json_sub_msg);

  CarState car_state;
  for (size_t idx = 0; idx < pub_msg_.vehicles.size(); idx++) {
    unity_cars_[idx]->setCollision(sub_msg.vehicles[idx].collision);

    // retrieve state from unity if using unity dynamics
    if (unity_cars_[idx]->getPhysicEngine()) {
      car_state.setPosition(sub_msg.vehicles[idx].position);
      unity_cars_[idx]->setState(car_state);
    }
  }
  return true;
};