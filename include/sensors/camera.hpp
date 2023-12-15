#pragma once
#include <deque>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>

#include "common/types.hpp"

class RGBCamera {
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
 public:
  RGBCamera();
  ~RGBCamera();
  // set functions
  bool setRelPose(const Ref<Vector<3>> rel_pos, const Quaternion& rel_rot);
  bool setWidth(const int width);
  bool setHeight(const int height);
  bool setFov(const Scalar fov);
  bool feedImageQueue(const cv::Mat& image_mat);

  // get functions
  int getChannels() const { return channels_; }
  int getWidth() const { return width_; }
  int getHeight() const { return heigth_; }
  Scalar getFov() const { return fov_; }
  Vector<3> getRelPos() const { return rel_pos_; }
  Quaternion getRelRot() const { return rel_rot_; }
  bool getRGBImage(cv::Mat& rgb_img);

 private:
  int channels_;
  int width_;
  int heigth_;
  Scalar fov_;

  // relative position

  Vector<3> rel_pos_{0, 0, 0};
  Quaternion rel_rot_;

  std::mutex queue_mutex_;  // avoid race condition between threads
  const int queue_size_{1};

  std::deque<cv::Mat> rgb_queue_;
};