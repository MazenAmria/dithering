#ifndef __DITHER_HPP__
#define __DITHER_HPP__

#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <cmath>

namespace dither
{
    cv::Mat floyd_stienberg(cv::Mat img, int n_bits);
    cv::Mat quantize(cv::Mat img, int n_bits);
    cv::Vec3b rectified_addition(cv::Vec3b v1, cv::Vec3b v2);
}

#endif //__DITHER_HPP__