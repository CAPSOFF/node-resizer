#include "resizer.hpp"

Resizer::Resizer() {}

auto Resizer::image_resizer(cv::Mat source, int width, int height) -> cv::Mat {
  auto resizedImage = cv::Mat{};
  cv::resize(source, resizedImage, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);
  
  return resizedImage;
}

auto Resizer::base64_to_mat(std::string encoded_base64) -> cv::Mat {
  auto decoded_jpeg =  base64_decode(encoded_base64);
  auto buffer_jpeg = std::vector<uchar>{decoded_jpeg.begin(), decoded_jpeg.end()};
  
  return cv::imdecode(cv::Mat(buffer_jpeg), 1);
}

auto Resizer::mat_to_base64(cv::Mat image) -> std::string {
  auto buffer = std::vector<uchar>{};
  cv::imencode(".jpg", image, buffer);
  auto *encoded_image = reinterpret_cast<unsigned char*>(buffer.data());

  return base64_encode(encoded_image, buffer.size()); 
}