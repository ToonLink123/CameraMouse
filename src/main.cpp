#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <string>

//Sets webcam resolution
void setResolution(cv::VideoCapture& cap, int width, int height) {
    // cap.set tells the webcam to change a property
    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
}


int main(int argc, char** argv) {
    //Change webcam used with number here
    int camIndex = 0;
    
    //Set default camera res
    int targetWidth = 1280;
    int targetHeight = 720;

    if (argc >= 2) {
        try {
            camIndex = std::stoi(argv[1]);
        } catch (...) {
            camIndex = 0;
        }
    }

    if (argc >= 3) {
        std::string res = argv[2];
        if (res == "1080") {
            targetWidth = 1920;
            targetHeight = 1080;
        }
    }

    //Create VideoCapture object called cap
    cv::VideoCapture cap(camIndex);

    //Check if webcam opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Could not open webcam index "  << camIndex << std::endl;
        return -1;
    }

    setResolution(cap, targetWidth, targetHeight);
    cv::namedWindow("HandControl Webcam", cv::WINDOW_NORMAL);

    auto lastTime = std::chrono::high_resolution_clock::now();
    double fps = 0.0;
    const double alpha = 0.1;

    while (true) {
        //Create matrix
        cv::Mat frame;
        //cap.read(frame) gets a frame from webcam
        if (!cap.read(frame) || frame.empty()) {
            std::cerr << "Failed to get frame" << std::endl;
            break;
        }
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> delta = currentTime - lastTime;
        lastTime = currentTime;
        double instantFPS = 1.0 / delta.count();
        if (fps == 0.0)
            fps = instantFPS;
        fps = (1 - alpha) * fps + alpha * instantFPS;
        std::string fpsText = "FPS: " + std::to_string(static_cast<int>(fps));
        cv::putText(frame, fpsText, cv::Point(20, 40), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
        cv::imshow("HandControl Webcam", frame);
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    //Close webcam and openCV windows
    cap.release();
    cv::destroyAllWindows();
    return 0;
}