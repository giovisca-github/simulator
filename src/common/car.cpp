#include "common/car.hpp"
Car::Car() {}

// setter
bool Car::setState(const CarState& state) {
  if (!state.valid()) return false;
  state_ = state;
  return true;
}

bool Car::setCommand(const Commands& command) {
  commands_ = command;

  return true;
};

// getters

bool Car::getState(CarState& state) {
  if (!state_.valid()) return false;
  state = state_;
  return true;
}