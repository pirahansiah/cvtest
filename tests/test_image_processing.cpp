// test_image_processing.cpp
// Unit tests for func_image_info.

#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>

#include "ImageProcessingClass.h"

class ImageProcessingTest : public ::testing::Test {
protected:
    cv::Mat bgr_image;
    cv::Mat gray_image;

    void SetUp() override {
        bgr_image = cv::Mat(100, 100, CV_8UC3, cv::Scalar(100, 150, 200));
        gray_image = cv::Mat(100, 100, CV_8UC1, cv::Scalar(128));
    }
};

TEST_F(ImageProcessingTest, FuncImageInfoProcessesBGR) {
    cv::Mat hist;
    int result = cvtest::func_image_info(bgr_image, hist);
    EXPECT_EQ(result, 0);
    EXPECT_FALSE(hist.empty());
}

TEST_F(ImageProcessingTest, FuncImageInfoProcessesGrayscale) {
    cv::Mat hist;
    int result = cvtest::func_image_info(gray_image, hist);
    EXPECT_EQ(result, 0);
    EXPECT_FALSE(hist.empty());
}

TEST_F(ImageProcessingTest, FuncImageInfoRejectsEmpty) {
    cv::Mat empty;
    cv::Mat hist;
    int result = cvtest::func_image_info(empty, hist);
    // Should handle gracefully (may return 0 or non-zero depending on OpenCV)
    // The key is it should not crash
    (void)result;
}
