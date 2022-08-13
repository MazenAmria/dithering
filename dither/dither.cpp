#include "dither.hpp"
#include <iostream>

cv::Mat dither::floyd_stienberg(cv::Mat img, int n_bits)
{
    int levels = (1 << n_bits) - 1;
    cv::Mat dithered_img;
    dithered_img = img.clone();

    for (int i = 0; i < img.rows; ++i)
    {
        for (int j = 0; j < img.cols; ++j)
        {
            cv::Vec3b orig = img.at<cv::Vec3b>(i, j);
            cv::Vec3b dith = dithered_img.at<cv::Vec3b>(i, j);

            for (int i = 0; i < 3; ++i)
                dith[i] = std::round(dith[i] * levels * 1.0 / 255.0) * 255 / levels;

            cv::Vec3b err = orig - dith;
            dithered_img.at<cv::Vec3b>(i, j) = dith;

            if (j + 1 < img.cols)
                dithered_img.at<cv::Vec3b>(i + 0, j + 1) = dither::clipped_addition(dithered_img.at<cv::Vec3b>(i + 0, j + 1), err * 7 / 16);
            if (j + 1 < img.cols && i + 1 < img.rows)
                dithered_img.at<cv::Vec3b>(i + 1, j + 1) = dither::clipped_addition(dithered_img.at<cv::Vec3b>(i + 1, j + 1), err * 1 / 16);
            if (i + 1 < img.rows)
                dithered_img.at<cv::Vec3b>(i + 1, j + 0) = dither::clipped_addition(dithered_img.at<cv::Vec3b>(i + 1, j + 0), err * 5 / 16);
            if (j - 1 > 0 && i + 1 < img.rows)
                dithered_img.at<cv::Vec3b>(i + 1, j - 1) = dither::clipped_addition(dithered_img.at<cv::Vec3b>(i + 1, j - 1), err * 3 / 16);
        }
    }

    return dithered_img;
}

cv::Mat dither::quantize(cv::Mat img, int n_bits)
{
    int levels = (1 << n_bits) - 1;
    cv::Mat quantized_img = img.clone();

    for (int i = 0; i < img.rows; ++i)
    {
        for (int j = 0; j < img.cols; ++j)
        {
            cv::Vec3b vec = quantized_img.at<cv::Vec3b>(i, j);

            for (int i = 0; i < 3; ++i)
                vec[i] = std::round(vec[i] * levels * 1.0 / 255.0) * 255 / levels;

            quantized_img.at<cv::Vec3b>(i, j) = vec;
        }
    }

    return quantized_img;
}

cv::Vec3b dither::clipped_addition(cv::Vec3b v1, cv::Vec3b v2)
{
    cv::Vec3b result;
    for (int i = 0; i < 3; ++i)
    {
        result[i] = std::max(0, std::min(255, v1[i] + v2[i]));
    }
    return result;
}