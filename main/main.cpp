#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "dither/dither.hpp"

int main()
{
    cv::Mat input_image;
    cv::namedWindow("PhotoFrame");
    input_image = cv::imread("images/donald_knuth.jpeg");
    if (input_image.empty())
    {
        std::cout << "Couldn't load the image." << std::endl;
        system("pause");
        return -1;
    }

    input_image = dither::floyd_stienberg(input_image, 4);
    cv::imshow("PhotoFrame", input_image);
    cv::waitKey(0);
    cv::destroyWindow("PhotoFrame");
    return 0;
}