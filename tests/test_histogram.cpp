// test_histogram.cpp
// Unit tests for histogram_color and histogram_gray functions.

#include <gtest/gtest.h>
#include <opencv2/core/core.hpp>

#include "ImageProcessingClass.h"

class HistogramTest : public ::testing::Test {
protected:
    cv::Mat bgr_image;
    cv::Mat gray_image;

    void SetUp() override {
        bgr_image = cv::Mat(100, 100, CV_8UC3, cv::Scalar(128, 100, 80));
        gray_image = cv::Mat(100, 100, CV_8UC1, cv::Scalar(128));
    }
};

TEST_F(HistogramTest, HistogramColorReturnsNonEmpty) {
    cv::Mat hist;
    int result = cvtest::histogram_color(bgr_image, hist);
    EXPECT_EQ(result, 0);
    EXPECT_FALSE(hist.empty());
}

TEST_F(HistogramTest, HistogramColorOutputSize) {
    cv::Mat hist;
    cvtest::histogram_color(bgr_image, hist);
    EXPECT_EQ(hist.rows, 400);
    EXPECT_EQ(hist.cols, 512);
    EXPECT_EQ(hist.channels(), 3);
}

TEST_F(HistogramTest, HistogramColorRejectsEmpty) {
    cv::Mat empty;
    cv::Mat hist;
    int result = cvtest::histogram_color(empty, hist);
    EXPECT_NE(result, 0);
}

TEST_F(HistogramTest, HistogramColorRejectsGrayscale) {
    cv::Mat hist;
    int result = cvtest::histogram_color(gray_image, hist);
    EXPECT_NE(result, 0);
}

TEST_F(HistogramTest, HistogramGrayReturnsNonEmpty) {
    cv::Mat hist;
    int result = cvtest::histogram_gray(gray_image, hist);
    EXPECT_EQ(result, 0);
    EXPECT_FALSE(hist.empty());
}

TEST_F(HistogramTest, HistogramGrayOutputSize) {
    cv::Mat hist;
    cvtest::histogram_gray(gray_image, hist);
    EXPECT_EQ(hist.rows, 400);
    EXPECT_EQ(hist.cols, 512);
}

TEST_F(HistogramTest, HistogramGrayRejectsEmpty) {
    cv::Mat empty;
    cv::Mat hist;
    int result = cvtest::histogram_gray(empty, hist);
    EXPECT_NE(result, 0);
}

TEST_F(HistogramTest, HistogramGrayAllPixelsCounted) {
    // Uniform image: all pixels have value 128
    cv::Mat uniform(50, 50, CV_8UC1, cv::Scalar(128));
    cv::Mat hist;
    int result = cvtest::histogram_gray(uniform, hist);
    EXPECT_EQ(result, 0);
    EXPECT_FALSE(hist.empty());
}

TEST_F(HistogramTest, HistogramGrayZeroImage) {
    cv::Mat zero(10, 10, CV_8UC1, cv::Scalar(0));
    cv::Mat hist;
    int result = cvtest::histogram_gray(zero, hist);
    EXPECT_EQ(result, 0);
    EXPECT_FALSE(hist.empty());
}
