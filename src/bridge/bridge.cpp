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
    std::cout << "---\n";
    std::cout.flush();
    sendSettings();
    unity_ready = receiveFirstMessage();
    usleep(1e6);
  }
  std::cout << "\n connected!\n";
  return unity_ready;
};

bool UnityBridge::sendSettings() {
  zmqpp::message message;

  json json_msg = settings_;
  // std::cout << json_msg.dump(2);
  message << "InitialSettings" << json_msg.dump();
  pub_.send(message, true);
  return true;
};

bool UnityBridge::receiveFirstMessage() {
  zmqpp::message msg;

  bool done = false;

  if (sub_.receive(msg, true)) {
    std::string header = msg.get(0);
    // std::cout << "\n received " << header << "\n";
    std::string metadata_string = msg.get(1);
    // if (json::parse(metadata_string).size() > 1) {
    //   return false;  // hack
    // }
    done = json::parse(metadata_string).at("ready").get<bool>();
  }
  return done;
};

bool UnityBridge::addCar(std::shared_ptr<Car> car) {
  Settings_vehicle settings_vehicles;
  CarState car_state;
  if (!car->getState(car_state)) {
    std::cerr << "Error in adding car, no states set for the car!!\n";
    return false;
  }
  // each vehile is called "car<number>"
  settings_vehicles.ID = "car" + std::to_string(pub_msg_.vehicles.size());
  settings_vehicles.position = position2Unity(car_state.p);
  settings_vehicles.rotation = quaternion2Unity(car_state.q());
  settings_vehicles.is_kinematic = car->getPhysicEngine();
  settings_vehicles.commands = car->getCommands();

  // add camera settings
  std::vector<std::shared_ptr<RGBCamera>> rgb_cameras = car->getRGBCameras();

  for (size_t cam_idx = 0; cam_idx < rgb_cameras.size(); cam_idx++) {
    std::shared_ptr<RGBCamera> cam = rgb_cameras[cam_idx];
    Camera camera;
    camera.ID = "camera_" + std::to_string(cam_idx);
    camera.rel_position = position2Unity(cam->getRelPos());
    camera.rel_rotation = quaternion2Unity(cam->getRelRot());
    camera.width = cam->getWidth();
    camera.height = cam->getHeight();
    camera.fov = cam->getFov();
    settings_vehicles.cameras.push_back(camera);
  }
  unity_cars_.push_back(car);

  settings_.vehicles.push_back(settings_vehicles);
  pub_msg_ = settings_;
  json json_msg = pub_msg_;
  // std::cout << json_msg.dump(2) << "\n";
  return true;
};

bool UnityBridge::sendToUnity() {
  CarState car_state;

  for (size_t idx = 0; idx < pub_msg_.vehicles.size(); idx++) {
    if (settings_.vehicles[idx].is_kinematic) {
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
  // std::cout << json_msg.dump(1);
  pub_.send(msg, true);
  return true;
};

bool UnityBridge::receiveFromUnity() {
  zmqpp::message msg;
  sub_.receive(msg);
  std::string header = msg.get(0);

  if (msg.get(0) == "Update") {
    std::string json_sub_msg = msg.get(1);
    // std::cout << json_sub_msg << "\n";
    SubMessage sub_msg = json::parse(json_sub_msg);

    CarState car_state;
    // each image from a camera is in a frame of the message
    size_t msg_img_frame = 2;

    for (size_t idx = 0; idx < settings_.vehicles.size(); idx++) {
      unity_cars_[idx]->setCollision(sub_msg.vehicles[idx].collision);
      // retrieve state from unity if using unity dynamics
      if (!unity_cars_[idx]->getPhysicEngine()) {
        car_state.setStatesFromUnity(sub_msg.vehicles[idx]);
        unity_cars_[idx]->setState(car_state);
      }

      // get cameras values
      int cam_id{0};
      for (const auto& cam : settings_.vehicles[idx].cameras) {
        uint32_t image_len = cam.width * cam.height * 3;  // 3 channels
        const uint8_t* image_data;
        msg.get(image_data, msg_img_frame);
        msg_img_frame += 1;

        // pack image from byte to cv::Mat
        cv::Mat new_image =
            cv::Mat(cam.height, cam.width, CV_MAKETYPE(CV_8U, 3));
        memcpy(new_image.data, image_data, image_len);

        cv::flip(new_image, new_image, 0);
        cv::cvtColor(new_image, new_image, cv::COLOR_RGB2BGR);

        unity_cars_[idx]->getRGBCameras()[cam_id]->feedImageQueue(new_image);
        cam_id++;
      }
    }
    return true;
  } else {
    return false;
  }
};