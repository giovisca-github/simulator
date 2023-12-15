#include "common/car.hpp"
Car::Car(MODE physic_model) : physic_engine_{physic_model} {}

// setter
bool Car::setState(const CarState& state) {
  if (!state.valid()) return false;
  state_ = state;
  return true;
}

bool Car::setCommand(const Commands& command) {
  commands_ = command;

  return true;
}
bool Car::addRGBCamera(const std::shared_ptr<RGBCamera> camera) {
  rgb_cameras_.push_back(camera);
  return true;
};

// getters

bool Car::getState(CarState& state) {
  if (!state_.valid()) return false;
  state = state_;
  return true;
};
Commands Car::getCommands() { return commands_; }
bool Car::getRGBCamera(const size_t cam_id,
                       std::shared_ptr<RGBCamera> camera) const {
  if (cam_id <= rgb_cameras_.size()) {
    std::cout << "the camera doesn't exist\n";
    return false;
  }
  camera = rgb_cameras_[cam_id];
  return true;
}
bool Car::getPhysicEngine() { return static_cast<bool>(physic_engine_); }