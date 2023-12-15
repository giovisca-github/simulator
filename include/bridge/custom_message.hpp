
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

// camera template
struct Camera {
  std::string ID;
  // camera settings
  int width{1024};
  int height{768};
  Scalar fov{70.0f};

  Scalar near_clip_plane{0.1};
  Scalar far_clip_plane{1000};

  std::vector<Scalar> rel_position{0, 0, 0};
  std::vector<Scalar> rel_rotation{0.0, 0.0, 0.0, 0.0};
};

// vehicle sent for settings the simulation
struct Settings_vehicle {
  std::string ID;
  std::vector<Scalar> position{0.0, 0.0, 0.0};
  std::vector<Scalar> rotation{0.0, 0.0, 0.0, 1.0};
  Commands commands;
  bool is_kinematic;  // 1 use PhysX dynamics
  std::vector<Camera> cameras;
};

//  vehicle to send to unity
struct Vehicle {
  std::string ID;
  std::vector<Scalar> position{0.0, 0.0, 0.0};
  std::vector<Scalar> rotation{0.0, 0.0, 0.0, 1.0};
  Commands commands;
  // bool is_kinematic;  // 1 use PhysX dynamics
  // std::vector<Camera> cameras;
  Vehicle(Settings_vehicle v) {
    ID = v.ID;
    position = v.position;
    rotation = v.position;
    commands = v.commands;
  };
  Vehicle() {
    ID = "";
    position = {0.0, 0.0, 0.0};
    rotation = {0.0, 0.0, 0.0, 1.0};
  }
};

// vehicle received from unity
struct Vehicle_sub {
  bool collision;
  std::vector<Scalar> position{NAN};
  std::vector<Scalar> rotation{NAN};
  std::vector<Scalar> velocity_lin{NAN};
  std::vector<Scalar> velocity_ang{NAN};
};
// initial setting message: define the vehicles and object in the scene to place
// them and also unity settings
struct Settings {
  enum class Solver { CONT, STEP };

  Solver solver = Solver::CONT;
};

struct SettingsMessage {
  Settings setings;
  // PubMessage initialization_msg;
  std::vector<Settings_vehicle> vehicles;
};
// message received from unity
struct SubMessage {
  std::vector<Vehicle_sub> vehicles;
};

// message published to unity for updates
struct PubMessage {
  std::vector<Vehicle> vehicles;

  PubMessage(SettingsMessage &s) {
    for (auto i = 0; i < s.vehicles.size(); i++) {
      vehicles.push_back(s.vehicles[i]);
    }
  }
  PubMessage(){};
};

// --- JSON Serialization ---------------------------- //

inline void to_json(json &j, const Camera &c) {
  j = json{
      {"ID", c.ID},
      {"width", c.width},
      {"height", c.height},
      {"fov", c.fov},
      {"nearClipPlane", c.near_clip_plane},
      {"farClipPlane", c.far_clip_plane},
      {"positionRel", c.rel_position},
      {"rotationRel", c.rel_rotation},
  };
}

inline void to_json(json &j, const Commands &c) {
  j = json{{"throttle", c.throttle}, {"steering", c.steering}};
}

inline void from_json(const json &j, Commands &c) {
  c.throttle = j.at("throttle").get<float>();
  c.steering = j.at("steering").get<float>();
}

inline void to_json(json &j, const Settings_vehicle &v) {
  j = json{{"ID", v.ID},
           {"position", v.position},
           {"rotation", v.rotation},
           {"commands", v.commands},
           {"is_kinematic", v.is_kinematic},
           {"cameras", v.cameras}};
};

inline void to_json(json &j, const Vehicle &v) {
  j = json{{"ID", v.ID},
           {"position", v.position},
           {"rotation", v.rotation},
           {"commands", v.commands}};
};

inline void from_json(const json &j, Vehicle &v) {
  v.ID = j.at("ID").get<std::string>();
  v.position = j.at("position").get<std::vector<Scalar>>();
  v.rotation = j.at("roation").get<std::vector<Scalar>>();
  v.commands = j.at("commands").get<Commands>();
}

inline void from_json(const json &j, Settings_vehicle &v) {
  v.ID = j.at("ID").get<std::string>();
  v.position = j.at("position").get<std::vector<Scalar>>();
  v.rotation = j.at("roation").get<std::vector<Scalar>>();
  v.commands = j.at("commands").get<Commands>();
  v.is_kinematic = j.at("is_kinematic").get<bool>();
}

inline void to_json(json &j, const PubMessage &p) {
  j = json{{"vehicles", p.vehicles}};
};
inline void from_json(const json &j, PubMessage &p) {
  p.vehicles = j.at("vehicles").get<std::vector<Vehicle>>();
}

inline void from_json(const json &j, SubMessage &s) {
  s.vehicles = j.at("vehicles").get<std::vector<Vehicle_sub>>();
}

inline void from_json(const json &j, Vehicle_sub &v) {
  v.collision = j.at("collision").get<bool>();
  if (!j.at("position").empty()) {
    v.position = j.at("position").get<std::vector<Scalar>>();
    v.rotation = j.at("rotation").get<std::vector<Scalar>>();
    v.velocity_lin = j.at("velocity_lin").get<std::vector<Scalar>>();
    v.velocity_ang = j.at("velocity_ang").get<std::vector<Scalar>>();
  }
}

inline void to_json(json &j, const Settings &s) {
  j = {{"solver", static_cast<int>(s.solver)}};
}

inline void to_json(json &j, const SettingsMessage &s) {
  j = json{{"settings", s.setings}, {"vehicles", s.vehicles}};
}
// inline void from_json(const json &j, SettingsMessage &s) {
//   s.initialization_msg = j.at("PubMessage").get<PubMessage>();
//   s.solver = j.at("solver").get<SettingMessage::Solver>();
// }