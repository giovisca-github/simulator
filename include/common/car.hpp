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
  Car();

  // setter methods
  bool setState(const CarState& state);
  bool setCommand(const Commands& command);

  // getter
  bool getState(CarState& state);

 private:
  Commands commands_;
  CarState state_;
};
