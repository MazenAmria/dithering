#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "dither/dither.hpp"

int main()
{
    cv::Mat input_img;
    cv::namedWindow("Original vs. Quantized vs. Dithered");
    input_img = cv::imread("images/donald_knuth.jpeg");
    if (input_img.empty())
    {
        std::cout << "Couldn't load the image." << std::endl;
        system("pause");
        return -1;
    }

    cv::Mat quantized_img = dither::quantize(input_img, 1);
    cv::Mat dithered_img = dither::floyd_stienberg(input_img, 1);
    cv::Mat comparison;
    cv::hconcat(input_img, quantized_img, comparison);
    cv::hconcat(comparison, dithered_img, comparison);
    cv::imshow("Original vs. Quantized vs. Dithered", comparison);
    cv::waitKey(0);
    cv::destroyWindow("Original vs. Quantized vs. Dithered");
    return 0;
}