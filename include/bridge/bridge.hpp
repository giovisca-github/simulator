#pragma once
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <zmqpp/zmqpp.hpp>

#include "bridge/custom_message.hpp"
#include "common/car.hpp"
#include "external/json.hpp"

using json = nlohmann::json;

class UnityBridge {
 public:
  UnityBridge();
  // ~UnityBridge();

  // connect functions
  bool connectUnity();
  bool disconnectUnity();

  // public getter

  bool getFromUnity();  // get all update from unity
  bool send_command(Commands& command);
  // add shard resource
  bool addCar(std::shared_ptr<Car> vehicle);

  // create unity bridge
  static std::shared_ptr<UnityBridge> getInstance(void) {
    static std::shared_ptr<UnityBridge> bridge_ptr =
        std::make_shared<UnityBridge>();
    return bridge_ptr;
  }

 private:
  std::vector<std::shared_ptr<Car>> unity_car_;

  bool initializeConnection(void);
  // ZMQ
  std::string client_address_;
  std::string pub_port_;
  std::string sub_port_;
  zmqpp::context context_;
  zmqpp::socket pub_{context_, zmqpp::socket_type::pub};
  zmqpp::socket sub_{context_, zmqpp::socket_type::sub};
  // messages types

  SettingMessage setting_msg_;
  PubMessage pub_msg_;
  bool sendFirstMessage();
  bool receiveFirstMessage();

  const int connection_time_out{10};
  bool unity_ready{false};
};