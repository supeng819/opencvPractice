#include <opencv2/opencv.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "camera.h"
using namespace cv;
using namespace std;
int plus2(int a, int b)
{
	return (a + b);
}

//读摄像头 0 电脑自带的摄像头    -1 随机选一个摄像头    1 usb摄像头
void camera_show(int usb_port)
{
	VideoCapture capture(usb_port);
	namedWindow("real_image");
	while (1)
	{
		Mat frame;
		capture >> frame;
		imshow("real_image", frame);
		waitKey(10);
	}
}
void camera_cutpart(int usb_port,int x,int y,int col,int row)
{
	VideoCapture capture(usb_port);
	namedWindow("real_image");
	Mat frame1;
	capture >> frame1;
	
	cout << frame1.size();
	while (1)
	{
		Mat frame;
		capture >> frame;
		imshow("real_image", frame);
		Mat imim;
		imim = frame(Rect(x, y, col, row));//220*147
		imshow("ss", imim);
		waitKey(10);
	}
}
/********************************************************************
*Copyright(C)  2002-2016, 东北大学ACTION机器人团队
*FileName：	   move.h
*Author：      Su Peng
*Date：        2016/11/18
*Description：
*		       读取一张图片是否成功
*			   传入一张图片的地址，如果在本路径下，传入文件名
*              如果获取成功会返回 Mat数据 否则输出-1
*Version：     debug version
*
********************************************************************/
Mat Get_image(const String& filename, int flags = IMREAD_COLOR)
{
	Mat image0;
	image0 = imread(filename);
	if (!image0.data)
	{
		printf("%s读取失败，确认是否存在\n", filename);
	}
	return image0;
}




const int g_nMaxAlphaValue = 100;
int g_nAlphaValueSlider;
double g_dAlphaValue;
double g_dBetaValue;
Mat image0, image1, image_all;
void on_Trackbar(int, void*)
{
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
	g_dBetaValue = 1.0 - g_dAlphaValue;
	addWeighted(image0, g_dAlphaValue, image1, g_dBetaValue, 0.0, image_all);
	imshow("线型混合", image_all);
}

/********************************************************************
*Copyright(C)  2002-2016, 东北大学ACTION机器人团队
*FileName：	   move.h
*Author：      Su Peng
*Date：        2016/11/18
*Description：
*		       对两张图片进行叠加
*			   通过滑动滑动条可以控制两张图片叠加的比率
*             
*Version：     debug version
*
********************************************************************/
int fix_two(void)
{
	//camera_show(1);
	//*****************   滑动条  ****************************************
	image0 = imread("10.jpg");
	image1 = imread("11.jpg");
	if (!image0.data)
	{
		printf("10.jpg读取失败，确认是否存在\n");
		return -1;
	}
	if (!image1.data)
	{
		printf("11.jpg读取失败，确认是否存在\n");
		return -1;
	}
	namedWindow("10_image");
	namedWindow("11_image");
	imshow("10_image", image0);
	imshow("11_image", image1);
	
	g_nAlphaValueSlider = 70;
	namedWindow("线型混合");
	char TrackbarName[50];
	sprintf(TrackbarName, "透明度%d", g_nMaxAlphaValue);

	createTrackbar(TrackbarName, "线型混合", &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	on_Trackbar(g_nAlphaValueSlider, 0);
	//****************************************

	return 0;
}

#define WINDOW_NAME "[鼠标窗口]"
void on_MouseHandle(int event, int x, int y, int flags, void *param);
void DrawRectangle(cv::Mat& img, cv::Rect box);
//void ShowHelpText();
static Rect g_rectangle;
static bool g_bDrawingBox = false;
RNG g_rng(12345);
int mouse_scan(void)
{
//Rect_类有些意思，成员变量x、y、width、height，分别为左上角点的坐标和矩形的宽和高。
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 800, CV_8UC3), tempImage;//Mat(int rows, int cols, int type);
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1, -1, 0, 0);
	srcImage = Scalar::all(0);
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME,on_MouseHandle,(void*)&srcImage);
	while (1)
	{
		srcImage.copyTo(tempImage);
		if (g_bDrawingBox) DrawRectangle(tempImage, g_rectangle);
		imshow(WINDOW_NAME, tempImage);
		if (waitKey(10) == 27)
			break;
	}
	return 0;
}
void on_MouseHandle(int event, int x, int y, int flags, void *param)
{
	Mat& image = *(cv::Mat*) param;
	switch (event)
	{
		case EVENT_MOUSEMOVE:
		{
			if (g_bDrawingBox)
			{
				g_rectangle.width = x - g_rectangle.x;
				g_rectangle.height = y - g_rectangle.y;
				printf("width=%d\theight=%d\n", g_rectangle.width, g_rectangle.height);
			}
		}
		break;
		case EVENT_LBUTTONDOWN:
		{
			g_bDrawingBox = true;
			g_rectangle = Rect(x, y, 0, 0);
			printf("x=%d\ty=%d\n", x,y);
			
		}
		break;
		case EVENT_LBUTTONUP:
		{
			g_bDrawingBox = false;
			if (g_rectangle.width < 0)
			{
				g_rectangle.x += g_rectangle.width;
				g_rectangle.width *= -1;
			}
			if (g_rectangle.height < 0)
			{
				g_rectangle.y += g_rectangle.height;
				g_rectangle.height *= -1;
			}
			DrawRectangle(image, g_rectangle);
		}
		break;

	}
}
void DrawRectangle(cv::Mat& img, cv::Rect box)
{
	rectangle(img,box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}

void Mat_Init_Assignment(void)   //Assignment赋值     Mat类赋值的一些方式
{
	Mat m1(5, 5, CV_32F);      //初始化
	m1.setTo(1.0);             //对所有元素赋值

	cout << endl << m1 << endl;

	Mat m2;
	m2 = m1.clone();              //clone赋值方式
	m2.setTo(2.0);
	cout << endl << m1 << endl;//改变m2的值看是否影响m1的值。


	m1.copyTo(m2);                  //copyTo赋值方式
	m2.setTo(2.0);
	cout << m1 << endl;

	m2 = m1;                     //‘=’赋值方式
	m2.setTo(2.0);
	cout << m1 << endl;
}






//#define WINDOW_NAME "[鼠标窗口]"
//void on_MouseHandle(int event, int x, int y, int flags, void *param);
//void DrawRectangle(cv::Mat& img, cv::Rect box);
////void ShowHelpText();
//Rect g_rectangle;
//bool g_bDrawingBox = false;
//RNG g_rng(12345);
int mouse_scan_image(void)
{
	Mat image0;
	image0 = imread("10.jpg");
	namedWindow("10_image");
	imshow("10_image", image0);

	Mat srcImage(image0.rows, image0.cols, image0.type());//Mat(int rows, int cols, int type);

	setMouseCallback("10_image", on_MouseHandle_image, (void*)&srcImage);
	while (1)
	{
		if (waitKey(10) == 27)
			break;
		
	}
	return 0;
}
void on_MouseHandle_image(int event, int x, int y, int flags, void *param)
{
	Mat& image = *(cv::Mat*) param;
	switch (event)
	{
	case EVENT_MOUSEMOVE:
	{
		if (g_bDrawingBox == true)
		{
			printf("x=%d\ty=%d\n", x, y);
		}
		
	}
	break;
	case EVENT_LBUTTONUP:
	{
		g_bDrawingBox = false;
	
	};
	break;
	case EVENT_LBUTTONDOWN:
	{
		g_bDrawingBox = true;
		//g_rectangle = Rect(x, y, 0, 0);
		printf("x=%d\ty=%d\n", x, y);
	}
	break;

	default :
		break;

	}
}




