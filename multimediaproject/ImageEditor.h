//
// Created by Duygu Karadadaş on 9.06.2024.
//

#ifndef MULTIMEDIAPROJECT_IMAGEEDITOR_H
#define MULTIMEDIAPROJECT_IMAGEEDITOR_H

#include <opencv2/opencv.hpp>  // we have to include this in the header file.


class ImageEditor {
public:
    static cv::Mat dilate(const cv::Mat& src, int size);
    static cv::Mat erode(const cv::Mat& src, int size);
    static cv::Mat resize(const cv::Mat& src, double fx, double fy);
    static cv::Mat lighten(const cv::Mat& src, double factor);
    static cv::Mat darken(const cv::Mat& src, double factor);
    static cv::Mat stitch(const std::vector<std::string>& directories );
    static cv::Mat cannyEdgeDetection(const cv::Mat& src, double threshold1, double threshold2, int apertureSize);
};

#endif //MULTIMEDIAPROJECT_IMAGEEDITOR_H
