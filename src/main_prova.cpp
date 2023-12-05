#include "bridge/bridge.hpp"

int main() {
  std::shared_ptr<Car> f1tenth_ptr = std::make_shared<Car>(Car::UNITY);

  // set initial states of the car:
  CarState initial_state;
  initial_state.p.setZero();

  f1tenth_ptr->setState(initial_state);
  // unity bridge
  std::shared_ptr<UnityBridge> bridge_ptr_;
  bridge_ptr_ = UnityBridge::getInstance();

  bridge_ptr_->addCar(f1tenth_ptr);
  bool unity_ready = bridge_ptr_->connectUnity();

  // simulation
  initial_state.p << 1.0, 0.0, 0.1;
  f1tenth_ptr->setState(initial_state);
  bridge_ptr_->sendToUnity();
  return 0;
}