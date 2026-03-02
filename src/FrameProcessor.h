#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

#include <opencv2/opencv.hpp>

class FrameProcessor {
//Defining Stages
public:
  FrameProcessor();
  ~FrameProcessor();
  cv::Mat read(const cv::Mat& frame);

private:
  HandDetector* detector;
  Guestures* guesture;
  ActionExectution* execute;
  Visualization* visuals;

}

#endif
