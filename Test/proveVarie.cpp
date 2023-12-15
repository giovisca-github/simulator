#include <deque>
#include <iostream>
#include <opencv2/opencv.hpp>

// int main() {
//   std::deque<cv::Mat> rgb_queue;
//   const int queue_size = 1;

//   for (int i = 0; i < 3; ++i) {
//     cv::Mat image_mat(1, 1, CV_8UC3, cv::Scalar(i, i, i));

//     // Check and resize
//     // if (rgb_queue.size() >= queue_size) {
//     std::cout << rgb_queue.size() << " resizing\n";
//     rgb_queue.resize(queue_size);
//     // }

//     // Add new image to the deque
//     rgb_queue.push_back(image_mat);

//     // Print the deque contents
//     std::cout << "Deque size: " << rgb_queue.size()
//               << ", Front: " << rgb_queue.front()
//               << ", Back: " << rgb_queue.back() << std::endl;
//   }

//   return 0;
// }

int main() {
  // Construct from a flattened one-dimensional array
  uint8_t greyArr[11 * 11] = {
      0,   25,  50,  75,  100, 125, 150, 175, 200, 225, 255, 0,   25,  50,
      75,  100, 125, 150, 175, 200, 225, 255, 0,   25,  50,  75,  100, 125,
      150, 175, 200, 225, 255, 0,   25,  50,  75,  100, 125, 150, 175, 200,
      225, 255, 0,   25,  50,  75,  100, 125, 150, 175, 200, 225, 255, 0,
      25,  50,  75,  100, 125, 150, 175, 200, 225, 255, 0,   25,  50,  75,
      100, 125, 150, 175, 200, 225, 255, 0,   25,  50,  75,  100, 125, 150,
      175, 200, 225, 255, 0,   25,  50,  75,  100, 125, 150, 175, 200, 225,
      255, 0,   25,  50,  75,  100, 125, 150, 175, 200, 225, 255, 0,   25,
      50,  75,  100, 125, 150, 175, 200, 225, 255};

  cv::Mat greyImg = cv::Mat(11, 11, CV_8U, greyArr);

  // Display the image
  std::string greyArrWindow = "Grey Array Image";
  cv::namedWindow(greyArrWindow, cv::WINDOW_AUTOSIZE);
  cv::resizeWindow(greyArrWindow, 400, 400);  // Set your desired window size
  cv::imshow(greyArrWindow, greyImg);

  cv::waitKey(1000);
  cv::destroyAllWindows();

  return 0;
}