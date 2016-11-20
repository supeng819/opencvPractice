#ifndef ACCPIX_H
#define ACCPIX_H
#include <opencv2/opencv.hpp> 
#include <opencv2/imgproc/imgproc.hpp>

void colorReducePoint(cv::Mat& inputImage, cv::Mat &outputImage, int div);
void colorReduceSTL(cv::Mat& inputImage, cv::Mat &outputImage, int div);
void colorReduce_at(cv::Mat& inputImage, cv::Mat &outputImage, int div);

#endif