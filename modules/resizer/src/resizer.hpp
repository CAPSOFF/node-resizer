#ifndef RESIZER_H
#define RESIZER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "base64.h"

class Resizer {
    public:
        Resizer();
        ~Resizer() = default;
        
        auto image_resizer(cv::Mat source, int width, int height) -> cv::Mat;
        auto base64_to_mat(std::string encoded_base64) -> cv::Mat;
        auto mat_to_base64(cv::Mat image) -> std::string;
};

#endif 