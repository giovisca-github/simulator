#include "bridge/bridge.hpp"

int main() {
  std::shared_ptr<F1tenth> f1tenth_ptr_ = std::make_shared<F1tenth>();

  // unity bridge
  std::shared_ptr<UnityBridge> bridge_ptr_;
  bridge_ptr_ = UnityBridge::getInstance();

  bridge_ptr_->addF1tenth(f1tenth_ptr_);
  bool unity_ready = bridge_ptr_->connectUnity();

  //   float x = 0;
  //   Commands command;
  //   while (true) {
  //     command.throttle = 1;
  //     bridge_ptr_->send_command(command);
  //     bridge_ptr_->get_value();
  //     f1tenth_ptr_->get_x(x);
  //     std::cout << x << "\n";
  //     usleep(0.5e6);
  //     }
  //   return 0;
  // }