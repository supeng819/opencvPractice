#ifndef CAMBODER_H
#define CAMBODER_H
#include <opencv2/opencv.hpp> 
#include <opencv2/imgproc/imgproc.hpp>

void on_MouseHandle_camera(int event, int x, int y, int flags, void *param);
int mouse_scan_camera(void);
#endif