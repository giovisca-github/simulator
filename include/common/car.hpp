#include <iostream>

#include "common/car_state.hpp"
#include "common/types.hpp"
#include "sensors/camera.hpp"
/*
attributes:
- states
- commands
- dynamic model
- sensors : camera, lidar, imu, wheel encoders

methods:
- get state
-set_state
- setcommand
*/

class Car {
 public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  enum MODE {
    UNITY,
    KIN

  };

  Car(MODE physic_engine);

  // setter methods
  MODE physic_engine_;
  bool setState(const CarState& state);
  bool setCommand(const Commands& command);
  inline void setCollision(const bool collision) { collision_ = collision; };
  bool addRGBCamera(const std::shared_ptr<RGBCamera> camera);

  // getter
  bool getState(CarState& state);
  bool getPhysicEngine();
  Commands getCommands();
  bool getRGBCamera(const size_t cam_id,
                    std::shared_ptr<RGBCamera> camera) const;
  std::vector<std::shared_ptr<RGBCamera>> getRGBCameras() const {
    return rgb_cameras_;
  }

 private:
  Commands commands_;
  CarState state_;
  bool collision_;

  // sensors
  std::vector<std::shared_ptr<RGBCamera>> rgb_cameras_;
};
