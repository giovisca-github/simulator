#include <iostream>

#include "common/car_state.hpp"
#include "common/types.hpp"
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

  // getter
  bool getState(CarState& state);
  bool getPhysicEngine();
  Commands getCommands();

 private:
  Commands commands_;
  CarState state_;
  bool collision_;
};
