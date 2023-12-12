#include "bridge/bridge.hpp"

int main() {
  // define vehicle in the scene
  std::shared_ptr<Car> f1tenth_dyn = std::make_shared<Car>(Car::UNITY);
  // std::shared_ptr<Car> f1tenth_dyn = std::make_shared<Car>(Car::KIN);

  //  initial states of the car:
  CarState initial_state;
  initial_state.setZero();

  // f1tenth_kin->setState(initial_state);
  // initial_state.p << 0, 0, 0;

  f1tenth_dyn->setState(initial_state);

  // unity bridge
  std::shared_ptr<UnityBridge> bridge_ptr_;
  bridge_ptr_ = UnityBridge::getInstance();
  // unity settings
  Settings settings;
  settings.solver = Settings::Solver::CONT;

  bridge_ptr_->setSettings(settings);
  // bridge_ptr_->addCar(f1tenth_kin);
  bridge_ptr_->addCar(f1tenth_dyn);
  bool unity_ready = bridge_ptr_->connectUnity();

  // simulation
  Commands c;
  while (unity_ready) {
    usleep(0.2e6);

    // // kinematic car
    // initial_state.p << 1.0, 0.0, 0;
    // f1tenth_kin->setState(initial_state);
    // dynamic car
    std::cout << "Input steering throttle = ";
    std::cin >> c.steering >> c.throttle;
    std::cout << "\n";
    f1tenth_dyn->setCommand(c);

    // send to unity
    bridge_ptr_->sendToUnity();

    // sleep
  }
  return 0;
}