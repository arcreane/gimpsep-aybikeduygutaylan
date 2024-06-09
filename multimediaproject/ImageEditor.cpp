//
// Created by Duygu Karadadaş on 9.06.2024.
//

#include "ImageEditor.h"
#include <opencv2/opencv.hpp>

cv::Mat ImageEditor::dilate(const cv::Mat& src, int size) {
    cv::Mat dst;
    cv::dilate(src, dst, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(size, size)));
    return dst;
}

cv::Mat ImageEditor::erode(const cv::Mat& src, int size) {
    cv::Mat dst;
    cv::erode(src, dst, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(size, size)));
    return dst;
}

cv::Mat ImageEditor::resize(const cv::Mat& src, double fx, double fy) {
    cv::Mat dst;
    cv::resize(src, dst, cv::Size(), fx, fy);
    return dst;
}

cv::Mat ImageEditor::lighten(const cv::Mat& src, double factor) {
    cv::Mat dst;
    src.convertTo(dst, -1, 1, factor);
    return dst;
}

cv::Mat ImageEditor::darken(const cv::Mat& src, double factor) {
    cv::Mat dst;
    src.convertTo(dst, -1, 1, -factor);
    return dst;
}

cv::Mat ImageEditor::stitch(const std::vector<std::string>& imageIndexes) {
    std::vector<cv::Mat> inputImages;
    for (const std::string& path : imageIndexes) {
        cv::Mat img = cv::imread(path);
        if (img.empty()) {
            throw std::runtime_error("Could not open or find image: " + path);
        }
        inputImages.push_back(img);
    }

    cv::Mat result;
    cv::Stitcher::Mode mode = cv::Stitcher::PANORAMA;
    cv::Ptr<cv::Stitcher> stitcher = cv::Stitcher::create(mode);

    // Set the panorama confidence threshold
    stitcher->setPanoConfidenceThresh(0.0); // Adjust this threshold as needed

    cv::Stitcher::Status status = stitcher->stitch(inputImages, result);
    if (status != cv::Stitcher::OK) {
        throw std::runtime_error("Panorama stitching failed with status: " + std::to_string(status));
    }

    return result;
}


cv::Mat ImageEditor::cannyEdgeDetection(const cv::Mat& src, double threshold1, double threshold2, int apertureSize) {
    cv::Mat dst;
    cv::Canny(src, dst, threshold1, threshold2, apertureSize);
    return dst;
}
