#pragma once

#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

namespace cvtest {

/// Compute and draw a BGR color histogram.
/// \param src Input BGR image.
/// \param dst Output histogram image (512x400, 3-channel).
/// \return 0 on success, non-zero on error.
int histogram_color(const cv::Mat& src, cv::Mat& dst);

/// Compute and draw a grayscale histogram.
/// \param src Input single-channel image.
/// \param dst Output histogram image (512x400, 1-channel).
/// \return 0 on success, non-zero on error.
int histogram_gray(const cv::Mat& src, cv::Mat& dst);

/// Print image metadata and compute appropriate histogram.
/// \param src Input image.
/// \param dst Output histogram image.
/// \return 0 on success, non-zero on error.
int func_image_info(const cv::Mat& src, cv::Mat& dst);

}  // namespace cvtest
