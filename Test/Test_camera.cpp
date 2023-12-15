#include "bridge/bridge.hpp"

int main() {
  // define vehicle in the scene
  std::shared_ptr<Car> f1tenth_dyn = std::make_shared<Car>(Car::UNITY);
  // std::shared_ptr<Car> f1tenth_dyn = std::make_shared<Car>(Car::KIN);

  //  initial states of the car:
  CarState initial_state;
  initial_state.setZero();
  f1tenth_dyn->setState(initial_state);

  // add cameras
  std::shared_ptr<RGBCamera> rgb_camera = std::make_shared<RGBCamera>();
  Vector<3> rel_pos(-0.1, 0, 0.1);
  Quaternion rel_rot(1.0, 0.0, 0.0, 0.0);
  rgb_camera->setRelPose(rel_pos, rel_rot);
  f1tenth_dyn->addRGBCamera(rgb_camera);

  cv::namedWindow("Display", cv::WINDOW_NORMAL);
  cv::resizeWindow("Display", 1024, 768);  // Set your desired window size

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
  c.throttle = 0.5;
  c.steering = -1;
  f1tenth_dyn->setCommand(c);

  cv::Mat img;

  while (unity_ready) {
    // send to unity
    bridge_ptr_->sendToUnity();
    bridge_ptr_->receiveFromUnity();
    rgb_camera->getRGBImage(img);
    // std::cout << img;

    if (!img.empty()) {
      std::cout << "image display\n";
      cv::imshow("Display", img);
      cv::waitKey(3);
    }
    // sleep
  }
  return 0;
}