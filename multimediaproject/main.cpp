#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "ImageEditor.h" //we have to include to use the classes' functions.
#include "VideoManipulations.h"

using namespace cv;
using namespace std;

vector<int> pickImage (int size, const vector<string>& imagePaths);

int main() {

    string imageDirectory;
    cout << "Welcome. Enter the path to the image directory: ";
    getline(cin, imageDirectory);


    vector<string> imagePaths;
    cv::glob(imageDirectory + "/*.jpg", imagePaths);

    if (imagePaths.size() < 2) {
        cerr << "There should be at least 2 images in the directory." << endl;
        return -1;
    }

    // Print the names of images in the directory
    cout << "Available images in the directory:" << endl;
    for (size_t i = 0; i < imagePaths.size(); ++i) {   //size_t :
        cout << i + 1 << ". " << imagePaths[i] << endl;
    }   //print the names.



    cout << "Choose the operation:\n";
    cout << "1. Dilate or Erode\n";
    cout << "2. Resize Image\n";
    cout << "3. Lighten\n";
    cout << "4. Darken\n";
    cout << "5. Stitch\n";
    cout << "6. Canny Edge Detection\n";
    cout << "7. Video Manipulations\n";


    cout << "Enter your choice (1/2/3/4/5/6/7): ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1: {
            int morphSize;
            char operation;
            cout << "Enter the morphological operation (D for dilation, E for erosion): ";
            cin >> operation;
            cout << "Enter the morphological operation size: ";
            cin >> morphSize;
            bool isDilation = (toupper(operation) == 'D');

            for (int index : pickImage(1, imagePaths)) {
                string pickedImagePath = imagePaths[index - 1]; // Adjust index for 0-based indexing
                cv::Mat image = imread(pickedImagePath);
                if (image.empty()) {
                    cerr << "Could not open or find the selected image." << endl;
                    return -1;
                }

                Mat morphedImage;
                if (isDilation) {
                    morphedImage = ImageEditor::dilate(image, morphSize);
                } else {
                    morphedImage = ImageEditor::erode(image, morphSize);
                }

                imshow("Original Image", image);
                imshow("Morphological Image", morphedImage);
            }
            break;
        }
        case 2: {
            for (int index : pickImage(1, imagePaths)) {
                string pickedImagePath = imagePaths[index - 1]; // Adjust index for 0-based indexing
                cv::Mat image = imread(pickedImagePath);
                if (image.empty()) {
                    cerr << "Could not open or find the selected image." << endl;
                    return -1;
                }

                int newWidth, newHeight;
                cout << "Enter the new width for resizing: ";
                cin >> newWidth;
                cout << "Enter the new height for resizing: ";
                cin >> newHeight;

                Mat resizedImage = ImageEditor::resize(image, newWidth, newHeight);
                imshow("Original Image", image);
                imshow("Resized Image", resizedImage);
            }
            break;
        }

        case 3: {
            vector<int> pickedImageIndices = pickImage(1, imagePaths); // Pick one image
            if (pickedImageIndices.empty()) {
                cerr << "No image selected." << endl;
                return -1;
            }

            // process each selected image
            for (int index : pickedImageIndices) {
                string pickedImagePath = imagePaths[index - 1]; // Adjust index for 0-based indexing
                cv::Mat image = imread(pickedImagePath);
                if (image.empty()) {
                    cerr << "Could not open or find the selected image." << endl;
                    return -1;
                }
                float factor;
                cout << "Enter the brightness adjustment factor: ";
                cin >> factor;
                Mat result=  ImageEditor::lighten(image, factor);
                imshow("Original Image", image);
                imshow("Lighted Image", result);
            }
            break;
        }

        case 4: {
            vector<int> pickedImageIndices = pickImage(1, imagePaths); // Pick one image
            if (pickedImageIndices.empty()) {
                cerr << "No image selected." << endl;
                return -1;
            }

            for (int index : pickedImageIndices) {
                string pickedImagePath = imagePaths[index - 1]; // Adjust index for 0-based indexing
                cv::Mat image = imread(pickedImagePath);
                if (image.empty()) {
                    cerr << "Could not open or find the selected image." << endl;
                    return -1;
                }
                float factor;
                cout << "Enter the darkness adjustment factor: ";
                cin >> factor;
                cv::Mat result = ImageEditor::darken(image, factor);
                imshow("Original Image", image);
                imshow("Darkened Image", result);
            }
            break;
        }
        case 5: {
            int numImages;
            cout << "Enter the number of images to stitch: ";
            cin >> numImages;

            vector<int> indexesToStitch = pickImage(numImages, imagePaths);

            vector<string> imagePathsToStitch;
            for (int index : indexesToStitch) {
                string pickedImagePath = imagePaths[index - 1]; // Adjust index for 0-based indexing
                imagePathsToStitch.push_back(pickedImagePath);
            }
            try {
                Mat panorama = ImageEditor::stitch(imagePathsToStitch);
                imshow("Panorama", panorama);
            } catch (const std::exception& e) {
                cerr << e.what() << endl;
                return -1;
            }
            break;
        }

        case 6: {
            int lowThreshold, highThreshold, kernelSize;
            cout << "Enter the low threshold for Canny edge detection: ";
            cin >> lowThreshold;
            cout << "Enter the high threshold for Canny edge detection: ";
            cin >> highThreshold;
            cout << "Enter the kernel size for Canny edge detection: ";
            cin >> kernelSize;

            for (int index : pickImage(1, imagePaths)) {    //hardcoded for 1 image only.
                string pickedImagePath = imagePaths[index - 1]; // Adjust index for 0-based indexing
                cv::Mat image = imread(pickedImagePath);
                if (image.empty()) {
                    cerr << "Could not open or find the selected image." << endl;
                    return -1;
                }

                Mat adjusted = ImageEditor::cannyEdgeDetection(image, lowThreshold, highThreshold, kernelSize);
                imshow("Original Image", image);
                imshow("Canny Edges", adjusted);
            }
            break;
        }

        case 7: {
            break;
        }

        default:
            cout << "Invalid choice. Please choose a valid operation." << endl;
            break;
    }
       if(choice==7){
           cout << "Which Video Manipulation? " << endl;
           cout << "1: Capture Video From Webcam" << endl;
           cout << "2: Play Video " << endl;
           cout << "3: BW Filter to a Webcam Video" << endl;
           cout << "4: Play a video in reverse " << endl;
           cout << "5: Face Detection " << endl;

           int vidchoice;
           cin>>vidchoice;
           switch (vidchoice) {
               case 1: {
                   std::string outputFilePath;
                   std::cout << "Enter the output file path: ";
                   std::cin >> outputFilePath;
                   try {
                       VideoManipulations::captureVideo(outputFilePath);
                       std::cout << "Video captured successfully!" << std::endl;
                   } catch (const std::exception& e) {
                       std::cerr << "Error: " << e.what() << std::endl;
                   }
                   break;
               }

               case 2: {
                   std::string filePath;
                   std::cout << "Enter the path of the video file: ";
                   std::cin.ignore(); // clears the input buffer
                   getline(cin, filePath);

                   try {
                       VideoManipulations::playVideo(filePath);
                   } catch (const std::exception& e) {
                       std::cerr << "Error: " << e.what() << std::endl;
                   }
                   break;
               }

               case 3: {
                   std::string filePath;
                   std::cout << "Enter the path you want to save the video file to: ";
                   std::cin.ignore(); // clears the input buffer
                   getline(cin, filePath);
                   try {
                       VideoManipulations::captureBWFrames(filePath) ;
                   } catch (const std::exception& e) {
                       std::cerr << "Error: " << e.what() << std::endl;
                   }
                   break;
               }

               case 4: {
                   std::string filePath;
                   std::cout << "Enter the path of the video file: ";
                   std::cin.ignore(); // clears the input buffer
                   getline(cin, filePath);
                   try {
                       VideoManipulations::reverseVideo(filePath);
                   } catch (const std::exception& e) {
                       std::cerr << "Error: " << e.what() << std::endl;
                   }
                   break;
               }

               case 5: {
                   std::string filePath;
                   std::cout << "Enter the path of the video file: ";
                   std::cin.ignore(); // clears the input buffer
                   getline(cin, filePath);

                   try {
                       VideoManipulations manipulations;
                       manipulations.detectFaces(filePath);
                   } catch (const std::exception& e) {
                       std::cerr << "Error: " << e.what() << std::endl;
                   }
                   break;
               }

               default:
                   std::cerr << "Invalid choice!" << std::endl;
                   break;
           }

       }

    waitKey(0);
    return 0;
}

vector<int> pickImage (int size, const vector<string>& imagePaths) {  //func to return desired images indexes
    vector<int> returnVector;
    cout << "Please specify " << size << " images."
            " Pick indexes of the image(s) you want to use: " << endl;
    int imageIndex;
    while (size>=1 && imageIndex > 0){
        cout << "Enter the index of the image you want to use: ";
        cin >> imageIndex;
        returnVector.push_back(imageIndex);
        size --;
    }
    return returnVector;
}