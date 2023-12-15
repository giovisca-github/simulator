#pragma once
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <zmqpp/zmqpp.hpp>

#include "bridge/custom_message.hpp"
#include "common/car.hpp"
#include "common/math_stuff.hpp"
#include "external/json.hpp"
#include "sensors/camera.hpp"

using json = nlohmann::json;

class UnityBridge {
 public:
  UnityBridge();
  // ~UnityBridge();

  // connect functions
  bool connectUnity();
  bool disconnectUnity();

  // used the values of the shared pointer car to send them to unity
  bool sendToUnity();
  bool receiveFromUnity();
  // add shard resource
  bool addCar(std::shared_ptr<Car> vehicle);

  // create unity bridge
  static std::shared_ptr<UnityBridge> getInstance(void) {
    static std::shared_ptr<UnityBridge> bridge_ptr =
        std::make_shared<UnityBridge>();
    return bridge_ptr;
  }

  // setter
  void setSettings(const Settings& settings) { settings_.setings = settings; }

 private:
  std::vector<std::shared_ptr<Car>> unity_cars_;

  bool initializeConnection(void);
  // ZMQ
  std::string client_address_;
  std::string pub_port_;
  std::string sub_port_;
  zmqpp::context context_;
  zmqpp::socket pub_{context_, zmqpp::socket_type::pub};
  zmqpp::socket sub_{context_, zmqpp::socket_type::sub};
  // messages types

  SettingsMessage settings_;
  PubMessage pub_msg_;  // store all the data that has to be then send to unity
  bool sendSettings();
  bool receiveFirstMessage();

  const int connection_time_out{10};
  bool unity_ready{false};
};