#include "bridge/bridge.hpp"

int main() {
  // define vehicle in the scene
  std::shared_ptr<Car> f1tenth_kin = std::make_shared<Car>(Car::KIN);
  //  initial states of the car:
  CarState initial_state;
  initial_state.p.setZero();

  f1tenth_kin->setState(initial_state);

  // unity bridge
  std::shared_ptr<UnityBridge> bridge_ptr_;
  bridge_ptr_ = UnityBridge::getInstance();
  // unity settings
  Settings settings;
  settings.solver = Settings::Solver::STEP;

  bridge_ptr_->setSettings(settings);
  bridge_ptr_->addCar(f1tenth_kin);
  bool unity_ready = bridge_ptr_->connectUnity();

  // simulation
  float x{-1};
  while (unity_ready) {
    usleep(0.2e6);
    x += 1;
    // kinematic car
    std::cout << "insert x y z values = ";
    for (int i = 0; i < 3; i++) {
      std::cin >> initial_state.p(i);
    }
    std::cout << "\n";
    // initial_state.p << x, 1, 2;
    f1tenth_kin->setState(initial_state);

    // send to unity
    bridge_ptr_->sendToUnity();
  }
  return 0;
}