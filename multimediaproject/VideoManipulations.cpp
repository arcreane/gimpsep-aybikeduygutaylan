//
// Created by Duygu Karadadaş on 9.06.2024.
//

#include "VideoManipulations.h"


  void VideoManipulations::captureVideo(const std::string& outputFilePath) {
    int deviceIndex=0;
    cv::VideoCapture videoCapture(deviceIndex);
    if (!videoCapture.isOpened()) {
        throw std::runtime_error("Failed to open video capture device");
    }

    int frameWidth = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
    int frameHeight = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
    double fps = videoCapture.get(cv::CAP_PROP_FPS);


      // Define the codec and create a VideoWriter object
    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); // Change codec as necessary
    cv::VideoWriter videoWriter(outputFilePath, codec, fps, cv::Size(frameWidth, frameHeight));

    if (!videoWriter.isOpened()) {
        throw std::runtime_error("Failed to open video file for writing");
    }

    cv::Mat frame;
    while (true) {
        videoCapture >> frame;
        if (frame.empty()) break;
        // Write the frame to the video file
        videoWriter.write(frame);

        // Show the frame on screen (optional)
        cv::imshow("Video Capture", frame);

        // Break the loop on ESC key
        if (cv::waitKey(30) == 27) break;
    }
    // Release the VideoCapture and VideoWriter objects
    videoCapture.release();
    videoWriter.release();
    cv::destroyAllWindows();
}

void VideoManipulations::playVideo(const std::string& filePath) {
    cv::VideoCapture videoCapture(filePath);
    if (!videoCapture.isOpened()) {
        throw std::runtime_error("Failed to open video file: " + filePath);
    }

    cv::Mat frame;
    while (true) {
        videoCapture >> frame;
        if (frame.empty()) break;
        cv::imshow("Video Player", frame);
        if (cv::waitKey(30) == 27) break; // Exit on ESC key
    }
    cv::destroyAllWindows();
}

cv::Mat VideoManipulations::captureBWFrames(const std::string& outputFilePath) {
    int deviceIndex = 0;
    cv::VideoCapture videoCapture(deviceIndex);
    if (!videoCapture.isOpened()) {
        throw std::runtime_error("Failed to open video capture device");
    }

    int frameWidth = videoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
    int frameHeight = videoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
    double fps = videoCapture.get(cv::CAP_PROP_FPS);

    // Define the codec and create a VideoWriter object
    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G'); // Change codec as necessary

    cv::VideoWriter videoWriter(outputFilePath, codec, fps , cv::Size(frameWidth, frameHeight));

    if (!videoWriter.isOpened()) {
        throw std::runtime_error("Failed to open video file for writing");
    }

    cv::Mat frame, bwFrame;
    while (true) {
        videoCapture >> frame;
        if (frame.empty()) break;

        cv::cvtColor(frame, bwFrame, cv::COLOR_BGR2GRAY);

        videoWriter.write(bwFrame);

        cv::imshow("Black and White Frame", bwFrame);

        if (cv::waitKey(30) == 27) break;
    }

    videoCapture.release();
    videoWriter.release();
    cv::destroyAllWindows();

    return bwFrame;
}


void VideoManipulations::reverseVideo(const std::string& filePath) {
    cv::VideoCapture videoCapture(filePath);
    if (!videoCapture.isOpened()) {
        throw std::runtime_error("Failed to open video file: " + filePath);
    }

    int totalFrames = videoCapture.get(cv::CAP_PROP_FRAME_COUNT);
    int currentFrame = totalFrames - 1; //  last frame

    cv::Mat frame;
    while (currentFrame >= 0) {
        videoCapture.set(cv::CAP_PROP_POS_FRAMES, currentFrame); // Set the current frame position
        videoCapture >> frame;
        if (frame.empty()) break;
        cv::imshow("Video Player (Reverse)", frame);
        if (cv::waitKey(30) == 27) break; // Exit on ESC key
        currentFrame--;
    }

    cv::destroyAllWindows();
}

void VideoManipulations::detectFaces(const std::string& filePath) {
    //  face detection cascade classifier
    if (!faceCascade.load(cv::samples::findFile("haarcascades/haarcascade_frontalface_default.xml"))) {
        std::cerr << "Failed to load face detection cascade classifier" << std::endl;
        return;
    }

    cv::VideoCapture videoCapture(filePath);
    if (!videoCapture.isOpened()) {
        throw std::runtime_error("Failed to open video file: " + filePath);
    }

    cv::Mat frame;
    while (true) {
        videoCapture >> frame;
        if (frame.empty()) break;

        cv::Mat grayFrame;
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        //detect face
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(grayFrame, faces, 1.1, 4);

        // Draw rectangles around the detected faces
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }
        cv::imshow("Face Detection", frame);

        // Exit on ESC key
        if (cv::waitKey(30) == 27) break;
    }

    cv::destroyAllWindows();
}