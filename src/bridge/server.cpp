#include <unistd.h>

#include <iostream>
#include <sstream>
#include <zmqpp/zmqpp.hpp>

#include "bridge/custom_message.hpp"
#include "external/json.hpp"

using json = nlohmann::json;
std::vector < std::shared_ptr<Vehicle>();

int main() {
  zmqpp::context context;
  zmqpp::socket pub(context, zmqpp::socket_type::pub);
  pub.connect("tcp://localhost:10254");
  pub.set(zmqpp::socket_option::send_high_water_mark, 6);

  zmqpp::socket sub(context, zmqpp::socket_type::sub);
  sub.connect("tcp://localhost:10253");
  sub.subscribe("");
  sub.set(zmqpp::socket_option::send_high_water_mark, 6);

  std::cout << "waiting for subscriber ... \n";

  zmqpp::message msg_settings;
  sub.receive(msg_settings);

  std::string header;
  header = msg_settings.get(0);

  std::cout << header << "\n";

  json settings_json = json::parse(msg_settings.get(1));
  std::cout << settings_json.dump() << std::endl;
  PubMessage pub_msg = settings_json;

  // store vehicles

  zmqpp::message message;
  json hanshake_json = {{"ready", true}};
  message << hanshake_json.dump();

  pub.send(message);
  float x = 0;

  while (true) {
    zmqpp::message msg;
    sub.receive(msg);  // receive upadte
    header = msg.get(0);
    std::cout << header << "\n";

    if (header == "Update") {
      json msg_json = json::parse(msg.get(1));
      std::cout << "received message: " << msg_json << "\n";

      for (Vehicle& v : vechiles) {
        if (v.physic_engine) {
          std::cout << "using phsyic engine, apply command \n";

        } else {
          std::cout << "update position on unity\n";
        }
      }
      std::cout << "send back a message with sensor data \n";
    };
  }

  return 0;
}