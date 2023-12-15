#include <deque>
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  std::deque<cv::Mat> rgb_queue;
  const int queue_size = 1;

  for (int i = 0; i < 3; ++i) {
    cv::Mat image_mat(1, 1, CV_8UC3, cv::Scalar(i, i, i));

    // Check and resize
    // if (rgb_queue.size() >= queue_size) {
    std::cout << rgb_queue.size() << " resizing\n";
    rgb_queue.resize(queue_size);
    // }

    // Add new image to the deque
    rgb_queue.push_back(image_mat);

    // Print the deque contents
    std::cout << "Deque size: " << rgb_queue.size()
              << ", Front: " << rgb_queue.front()
              << ", Back: " << rgb_queue.back() << std::endl;
  }

  return 0;
}