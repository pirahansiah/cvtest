// ImageProcessingClass.cpp
// Computer vision image processing utilities with histogram computation.
// Modernized to C++17 with const correctness and bug fixes.

#include "ImageProcessingClass.h"

#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace cvtest {

int histogram_color(const cv::Mat& src, cv::Mat& dst) {
    if (src.empty() || src.channels() != 3) {
        std::cerr << "histogram_color: input must be a 3-channel BGR image\n";
        return -1;
    }

    std::vector<cv::Mat> bgr_planes;
    cv::split(src, bgr_planes);

    int hist_size = 256;
    float range[] = {0.0f, 256.0f};
    const float* hist_range[] = {range};

    cv::Mat b_hist, g_hist, r_hist;
    cv::calcHist(&bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &hist_size, hist_range, true, false);
    cv::calcHist(&bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &hist_size, hist_range, true, false);
    cv::calcHist(&bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &hist_size, hist_range, true, false);

    int hist_w = 512;
    int hist_h = 400;
    int bin_w = cvRound(static_cast<double>(hist_w) / hist_size);

    cv::Mat hist_image(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

    cv::normalize(b_hist, b_hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(g_hist, g_hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
    cv::normalize(r_hist, r_hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());

    for (int i = 1; i < hist_size; ++i) {
        cv::line(hist_image,
                 cv::Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
                 cv::Point(bin_w * i, hist_h - cvRound(b_hist.at<float>(i))),
                 cv::Scalar(255, 0, 0), 2, cv::LINE_AA);
        cv::line(hist_image,
                 cv::Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
                 cv::Point(bin_w * i, hist_h - cvRound(g_hist.at<float>(i))),
                 cv::Scalar(0, 255, 0), 2, cv::LINE_AA);
        cv::line(hist_image,
                 cv::Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
                 cv::Point(bin_w * i, hist_h - cvRound(r_hist.at<float>(i))),
                 cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    }

    dst = hist_image;
    return 0;
}

int histogram_gray(const cv::Mat& image, cv::Mat& out) {
    if (image.empty()) {
        std::cerr << "histogram_gray: input image is empty\n";
        return -1;
    }

    // Fixed off-by-one: initialize all 256 bins
    std::vector<int> histogram(256, 0);

    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            ++histogram[static_cast<int>(image.at<uchar>(y, x))];
        }
    }

    int hist_w = 512;
    int hist_h = 400;
    int bin_w = cvRound(static_cast<double>(hist_w) / 256);

    cv::Mat hist_image(hist_h, hist_w, CV_8UC1, cv::Scalar(255));

    int max_val = *std::max_element(histogram.begin(), histogram.end());
    if (max_val == 0) {
        out = hist_image;
        return 0;
    }

    for (int i = 0; i < 256; ++i) {
        histogram[i] = static_cast<int>((static_cast<double>(histogram[i]) / max_val) * hist_image.rows);
    }

    for (int i = 0; i < 256; ++i) {
        cv::line(hist_image,
                 cv::Point(bin_w * i, hist_h),
                 cv::Point(bin_w * i, hist_h - histogram[i]),
                 cv::Scalar(0), 1, cv::LINE_AA);
    }

    out = hist_image;
    return 0;
}

int func_image_info(const cv::Mat& src, cv::Mat& dst) {
    try {
        int type = src.type();
        uchar depth = type & CV_MAT_DEPTH_MASK;
        uchar chans = 1 + (type >> CV_CN_SHIFT);

        std::string type_str;
        switch (depth) {
            case CV_8U:  type_str = "8U"; break;
            case CV_8S:  type_str = "8S"; break;
            case CV_16U: type_str = "16U"; break;
            case CV_16S: type_str = "16S"; break;
            case CV_32S: type_str = "32S"; break;
            case CV_32F: type_str = "32F"; break;
            case CV_64F: type_str = "64F"; break;
            default:     type_str = "User"; break;
        }
        type_str += "C" + std::to_string(chans);

        std::cout << "Image info:\n";
        std::cout << "\tType: " << type_str << "\n";
        std::cout << "\tDimensions: " << src.rows << " x " << src.cols << "\n";

        if (src.channels() == 3) {
            std::cout << "\tColor: BGR\n";
        } else {
            std::cout << "\tColor: Grayscale\n";
        }

        cv::Mat hist;
        if (src.channels() == 1) {
            histogram_gray(src, hist);
            int nz_count = cv::countNonZero(src);
            std::cout << "\tNon-zero pixels: " << nz_count
                      << " of " << (src.rows * src.cols) << "\n";
        } else {
            histogram_color(src, hist);
        }
        dst = hist;
    } catch (const cv::Exception& e) {
        std::cerr << "OpenCV exception: " << e.what() << "\n";
        return -1;
    }
    return 0;
}

}  // namespace cvtest

int main(int argc, char* argv[]) {
    std::string image_path = "Image/test_image.jpg";
    if (argc > 1) {
        image_path = argv[1];
    }

    cv::Mat src = cv::imread(image_path, cv::IMREAD_COLOR);
    if (src.empty()) {
        std::cerr << "Error: cannot read image: " << image_path << "\n";
        return 1;
    }

    cv::imshow("Original", src);
    cv::waitKey(1000);

    cv::Mat hist;
    cvtest::func_image_info(src, hist);
    cv::imshow("Histogram", hist);
    cv::waitKey(1000);

    cv::Mat resized;
    double scale = 0.1;
    cv::resize(src, resized, cv::Size(), scale, scale, cv::INTER_CUBIC);
    cv::imshow("Resized", resized);
    cv::waitKey(1000);

    cv::Mat big_image = cv::Mat::zeros(src.size(), src.type());
    cv::Rect roi(cv::Point(0, 0), resized.size());
    resized.copyTo(big_image(roi));
    cv::imshow("Copy to ROI", big_image);
    cv::waitKey(0);

    cv::destroyAllWindows();
    return 0;
}
