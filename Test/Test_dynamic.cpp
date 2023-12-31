#include "bridge/bridge.hpp"

int main() {
  cv::namedWindow("Display", cv::WINDOW_NORMAL);
  cv::resizeWindow("Display", 400, 400);  // Set your desired window size
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
  cv::Mat img;

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
    bridge_ptr_->receiveFromUnity();
    // check correctness of pared states
    CarState state;
    f1tenth_dyn->getState(state);

    Quaternion quaternion = state.q();
    std::cout << "quaternion: " << quaternion << std::endl;
    Matrix<3, 3> rotationMatrix = quaternion.toRotationMatrix();
    float angle = Eigen::AngleAxisf(rotationMatrix).angle() * 180 / M_PI;
    std::cout << "angle" << angle << std::endl;
    std::cout << "position z: " << state.p(2) << std::endl;

    // cv::imshow("camera from unity",
    //  f1tenth_dyn->getRGBCameras()[0]->getRGBImage(img));
    rgb_camera->getRGBImage(img);
    // std::cout << img;

    if (!img.empty()) {
      std::cout << "image display\n";
      cv::imshow("Display", img);
      cv::waitKey(300);
    }
    // sleep
  }
  return 0;
}