#include <iostream>
#include "opencv2/opencv.hpp"
int main(int argc, char* argv[])
{
    std::string path = "c:\\farshid\\src.exr";
    cv::Mat src = cv::imread(path, cv::IMREAD_UNCHANGED);    
    src.convertTo(src, cv::COLOR_BGR2RGB);
    src.convertTo(src, CV_8UC3);
    bool show = true;
    if (show)
    {
        cv::imshow("image", src);
        cv::waitKey(1000);
    }
}