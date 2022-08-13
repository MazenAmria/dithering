#include <iostream>
#include <opencv2/opencv.hpp>
#include "dither/dither.hpp"

#define N_BITS 4

int main()
{
    cv::Mat input_img;
    input_img = cv::imread("images/donald_knuth.jpeg");
    if (input_img.empty())
    {
        std::cout << "Couldn't load the image." << std::endl;
        system("pause");
        return -1;
    }

    cv::Mat input_img_gray;
    cv::cvtColor(input_img, input_img_gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(input_img_gray, input_img_gray, cv::COLOR_GRAY2BGR);

    cv::Mat quantized_img = dither::quantize(input_img, N_BITS);
    cv::Mat quantized_img_gray;
    cv::cvtColor(quantized_img, quantized_img_gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(quantized_img_gray, quantized_img_gray, cv::COLOR_GRAY2BGR);

    cv::Mat dithered_img = dither::floyd_stienberg(input_img, N_BITS);
    cv::Mat dithered_img_gray;
    cv::cvtColor(dithered_img, dithered_img_gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(dithered_img_gray, dithered_img_gray, cv::COLOR_GRAY2BGR);

    cv::vconcat(input_img_gray, input_img, input_img);
    cv::vconcat(quantized_img_gray, quantized_img, quantized_img);
    cv::vconcat(dithered_img_gray, dithered_img, dithered_img);

    cv::Mat comparison;
    cv::hconcat(input_img, quantized_img, comparison);
    cv::hconcat(comparison, dithered_img, comparison);

    cv::namedWindow("Original vs. Quantized vs. Dithered", cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO | cv::WINDOW_GUI_EXPANDED);
    cv::imshow("Original vs. Quantized vs. Dithered", comparison);
    cv::imwrite("result_4b.jpeg", comparison);
    cv::waitKey(0);
    cv::destroyWindow("Original vs. Quantized vs. Dithered");

    return 0;
}