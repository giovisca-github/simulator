#include "bridge/bridge.hpp"

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

  std::cout << "connection done\n";
  return true;
}

bool UnityBridge::connectUnity() {  // test communication in both direction so
                                    // first send, then wait for a response
                                    // related to the message sent
  std::cout << "trying to connect to unity ";
  while (!unity_ready) {
    std::cout << "---";
    std::cout.flush();
    sendFirstMessage();
    unity_ready = receiveFirstMessage();
    usleep(0.5e6);
  }
  std::cout << "\n connected!\n";
  return unity_ready;
};

bool UnityBridge::sendFirstMessage() {
  zmqpp::message message;

  json hanshake_json = {{"ready", true}};
  message << "Connect" << hanshake_json.dump();

  pub_.send(message, true);
  return true;
};

bool UnityBridge::receiveFirstMessage() {
  zmqpp::message msg;

  bool done = false;

  if (sub_.receive(msg, true)) {
    std::string metadata_string = msg.get(0);
    if (json::parse(metadata_string).size() > 1) {
      return false;  // hack
    }
    done = json::parse(metadata_string).at("ready").get<bool>();
  }
  return done;
};

bool UnityBridge::addCar(std::shared_ptr<Car> vehicle) {
  unity_car_ = vehicle;

  return false;
};

bool UnityBridge::getFromUnity() {
  zmqpp::message msg;
  sub_.receive(msg);

    return true;
}

bool UnityBridge::send_command(Commands& command) {
  zmqpp::message msg;
  json msg_json = command;
  msg << "Command";
  msg << msg_json.dump();

  pub_.send(msg, true);
  return true;
};