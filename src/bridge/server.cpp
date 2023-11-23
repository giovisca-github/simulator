#include <unistd.h>

#include <iostream>
#include <sstream>
#include <zmqpp/zmqpp.hpp>

#include "external/json.hpp"

using json = nlohmann::json;

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

  zmqpp::message handshake;
  sub.receive(handshake);

  std::string header;

  header = handshake.get(0);
  std::cout << header << "\n";

  json handshake_json = json::parse(handshake.get(1));
  std::cout << handshake_json << "\n";
  bool there_is_publisher = handshake_json.at("ready").get<bool>();

  // sub.subscribe("Pose");

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

    if (header == "Command") {
      json msg_json = json::parse(msg.get(1));
      std::cout << "received message: " << msg_json << "\n";
      float t = msg_json.at("throttle").get<float>();

      x += 1 * t;  // do something with update value

      // publish  message

      zmqpp::message pub_msg;
      json pub_msg_json = {{"new_x", x}};

      pub_msg << pub_msg_json.dump();
      pub.send(pub_msg);
      std::cout << "message sent: " << x << "\n";
    };
  }

  return 0;
}