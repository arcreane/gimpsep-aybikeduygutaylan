//
// Created by Duygu Karadadaş on 9.06.2024.
//

#ifndef MULTIMEDIAPROJECT_VIDEOMANIPULATIONS_H
#define MULTIMEDIAPROJECT_VIDEOMANIPULATIONS_H


#ifndef VIDEO_MANIPULATIONS_H
#define VIDEO_MANIPULATIONS_H

#include <opencv2/opencv.hpp>
#include <string>

class VideoManipulations {
public:

    // Play a video from a file
    static void playVideo(const std::string& filePath);

    // Capture video from a device
    static void captureVideo(const std::string& outputFilePath);

    static cv::Mat captureBWFrames(const std::string& outputFilePath);

    static void reverseVideo(const std::string& filePath);

    void detectFaces(const std::string& filePath);

private:
    cv::CascadeClassifier faceCascade;

};

#endif // VIDEO_MANIPULATIONS_H


#endif //MULTIMEDIAPROJECT_VIDEOMANIPULATIONS_H
