// Chapter_01_01.cpp
// Book example: read and display an EXR image.

#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char* argv[]) {
    std::string path = (argc > 1) ? argv[1] : "test_image.jpg";

    cv::Mat src = cv::imread(path, cv::IMREAD_UNCHANGED);
    if (src.empty()) {
        std::cerr << "Error: cannot read image: " << path << "\n";
        return 1;
    }

    // Fixed bug: was using convertTo with color conversion code
    if (src.channels() == 3) {
        cv::cvtColor(src, src, cv::COLOR_BGR2RGB);
    }

    if (src.depth() != CV_8U) {
        src.convertTo(src, CV_8UC3);
    }

    cv::imshow("image", src);
    cv::waitKey(1000);
    cv::destroyAllWindows();

    return 0;
}
