
/*
custom type used only for messages and json serialization - deserialization
*/
#pragma once

#include "common/types.hpp"
#include "external/json.hpp"
/*
the simulator has to receive:
 - vehicle states
 - vehicle commands -> works on this know

 the simulator has to send:
 - camera
 - lidar
 - vehicle states


 note that unity use a left hand rf with y upward, z-forward
*/

using json = nlohmann::json;

// unity vehicle
struct Vehicle {
  std::uint64_t ID;
  std::vector<Scalar> position{0.0, 0.0, 0.0};
  std::vector<Commands> commands;
};

// initial message
struct SettingMessage {
  std::vector<Vehicle> vehicles;
  std::vector<bool> unity_dynamics;  // 1 use PhysX dynamics
};

// message published to unity
struct PubMessage {
  std::vector<Vehicle> vehicles;
};

// message received from unity
struct SubMessage {
  std::vector<Vehicle> vehicles;
};

// --- JSON Serialization ---------------------------- //

inline void to_json(json& j, const Commands& c) {
  j = json{{"throttle", c.throttle}, {"steering", c.steering}};
}

inline void from_json(const json& j, Commands& c) {
  c.throttle = j.at("throttle").get<float>();
  c.steering = j.at("steering").get<float>();
}

inline void to_json(json& j, const Vehicle& v) {
  j = json{{"ID", v.ID}, {"position", v.position}, {"commands", v.commands}};
};

inline void from_json(const json& j, Vehicle& v) {
  v.ID = j.at("ID").get<uint64_t>();
  v.position = j.at("position").get<std::vector<Scalar>>();
  v.commands = j.at("commands").get<std::vector<Commands>>();
}

inline void to_json(json& j, const PubMessage& p) {
  j = json{{"vehicles", p.vehicles}};
};

inline void from_json(const json& j, SubMessage& s) {
  s.vehicles = j.at("vehicles").get<std::vector<Vehicle>>();
}
