#ifndef CAMERA_H
#define CAMERA_H
#include <opencv2/opencv.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
int plus2(int a, int b);
void camera_show(int usb_port);
void camera_cutpart(int usb_port, int x, int y, int col, int row);
int fix_two(void);
void on_Trackbar(int, void*);
int mouse_scan(void);
void on_MouseHandle(int event, int x, int y, int flags, void *param);
void DrawRectangle(cv::Mat& img, cv::Rect box);

void on_MouseHandle_image(int event, int x, int y, int flags, void *param);
int mouse_scan_image(void);

//void on_MouseHandle_camera(int event, int x, int y, int flags, void *param);
//int mouse_scan_camera(void);
#endif