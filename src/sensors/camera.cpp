#include "sensors/camera.hpp"

RGBCamera::RGBCamera() : channels_{3}, width_{720}, heigth_{480}, fov_{70.0} {}

RGBCamera::~RGBCamera() {}

bool RGBCamera::setRelPose(const Ref<Vector<3>> rel_pos,
                           const Quaternion& rel_rot) {
  if (!rel_pos.allFinite()) {
    std::cerr << "The relative position is not valid!";
    return false;
  }
  rel_pos_ = rel_pos;
  rel_rot_ = rel_rot;
  return true;
}

bool RGBCamera::setWidth(const int width) {
  if (width <= 0.0) {
    std::cerr << "width must be greater than zer\n";
    return false;
  }

  width_ = width;
  return true;
}

bool RGBCamera::setHeight(const int height) {
  if (height <= 0.0) {
    std::cerr << "the height must be greater than zero\n";
    return false;
  }

  heigth_ = height;
  return true;
}

bool RGBCamera::setFov(const Scalar fov) {
  if (fov <= 0.0) {
    std::cerr << "fov must be positive\n";
    return false;
  }

  fov_ = fov;
  return true;
}

bool RGBCamera::feedImageQueue(const cv::Mat& image_mat) {
  queue_mutex_.lock();
  // keep a queu of 2 elements, only keep the last image and the one that is
  // going to be processed
  if (rgb_queue_.size() > queue_size_) rgb_queue_.resize(queue_size_);

  rgb_queue_.push_back(image_mat);
  queue_mutex_.unlock();
  return true;
}

bool RGBCamera::getRGBImage(cv::Mat& rgb_img) {
  if (!rgb_queue_.empty()) {
    rgb_img = rgb_queue_.front();
    rgb_queue_.pop_front();
    return true;
  }
  return false;
}
