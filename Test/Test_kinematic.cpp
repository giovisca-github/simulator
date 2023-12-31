#include "bridge/bridge.hpp"
#include "math.h"

int main() {
  // define vehicle in the scene
  std::shared_ptr<Car> f1tenth_kin = std::make_shared<Car>(Car::KIN);
  //  initial states of the car:
  CarState state;
  state.setZero();

  f1tenth_kin->setState(state);

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
  float x{0};
  while (unity_ready) {
    usleep(0.2e6);
    // kinematic car
    std::cout << "insert x y z  values = ";
    for (int i = 0; i < 3; i++) {
      std::cin >> state.p(i);
    }
    std::cout << " yaw value = ";
    std::cin >> x;

    state.setYaw(x * M_PI / 180.0);
    std::cout << "\n";
    // initial_state.p << x, 1, 2;
    f1tenth_kin->setState(state);

    // send to unity
    bridge_ptr_->sendToUnity();
    bridge_ptr_->receiveFromUnity();

    // check rotation
    f1tenth_kin->getState(state);
    std::cout << state.q() << std::endl;
    std::cout << state.v[0] << std::endl;
  }
  return 0;
}