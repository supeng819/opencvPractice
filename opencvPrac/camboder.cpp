#include <opencv2/opencv.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "camboder.h"
using namespace cv;
using namespace std;
//一些曲线绘制 椭圆 圆 直线
//ellipse(image0,Point(350,300),Size(150,17),0,0,360,Scalar(250,0,0),2,8);
//circle(image0, Point(280, 400), 50, Scalar(0, 0, 250), 2, 8);
//line(image0, Point(330, 400), Point(380, 400), Scalar(0, 250, 0), 2, 8);
static Rect g_rectangle;
static bool g_bDrawingBox = false;
vector<Point> v;
int signal_over = 0; Mat frame;
int mouse_scan_camera(void)
{
	VideoCapture capture(0);
	Mat frame0;
	namedWindow("capCameraBorder");
	capture >> frame0;
	Mat srcImage(frame0.rows, frame0.cols, frame0.type());//Mat(int rows, int cols, int type);
	setMouseCallback("capCameraBorder", on_MouseHandle_camera, (void*)&srcImage);

	namedWindow("capCameraBorder");
	while (1)
	{
		capture >> frame;
		if (signal_over == 1)
		{
			std::vector<Point>::iterator p;
			for (p = v.begin(); p < v.end() - 1; p++)
			{
				line(frame, *p, *(p + 1), Scalar(250, 0, 0), 2, 8);
			}
			line(frame, *(v.end() - 1), *(v.begin()), Scalar(250, 0, 0), 2, 8);
		}

		imshow("capCameraBorder", frame);

		if (waitKey(10) == 27)
			break;
	}
	return 0;
}
void on_MouseHandle_camera(int event, int x, int y, int flags, void *param)
{
	Mat& image = *(cv::Mat*) param;
	switch (event)
	{
	case EVENT_MOUSEMOVE:
	{
		if (g_bDrawingBox == true)
		{
			//printf("x=%d\ty=%d\n", x, y);
			v.push_back(Point(x, y));
		}
		//新建一个容器  动态向里面添加  Point类型的变量

	}
	break;
	case EVENT_LBUTTONUP:
	{
		g_bDrawingBox = false;
		signal_over = 1;

		//int x = 1, y = 1;
		//Point z(1, 1);
		//v.push_back(Point(x, y));
		//v.push_back(z);
		//v.push_back(z);
		//std::vector<Point>::iterator p;
		//for (p = v.begin(); p < v.end()-1; p++)
		//{ 
		//	cout << *p << endl;
		//}



	}
	break;
	case EVENT_LBUTTONDOWN:
	{
		g_bDrawingBox = true;
		//printf("x=%d\ty=%d\n", x, y);

	}
	break;

	default:
		break;

	}
}