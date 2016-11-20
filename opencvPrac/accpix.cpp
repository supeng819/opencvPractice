#include <opencv2/opencv.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include "accpix.h"
using namespace cv;
using namespace std;
void colorReducePoint(Mat& inputImage, Mat &outputImage, int div)
{
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int lineNumber = outputImage.cols*outputImage.channels();
	for (int i = 0; i < rowNumber; i++)
	{
		uchar *data = outputImage.ptr<uchar>(i);
		for (int j = 0; j < lineNumber; j++)
		{
			data[j] = data[j] / div*div + div / 2;
		}
	}
}
void colorReduceSTL(Mat& inputImage, Mat &outputImage, int div)
{
	outputImage = inputImage.clone();
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();//��ʼλ�õ�����
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();//��ֹλ�õ�����
	for (; it != itend; it++)
	{
		(*it)[0] = (*it)[0] / div*div + div / 2;
		(*it)[1] = (*it)[1] / div*div + div / 2;
		(*it)[2] = (*it)[2] / div*div + div / 2;
	}
}
void colorReduce_at(Mat& inputImage, Mat &outputImage, int div)
{
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div*div + div / 2;//��ɫͨ��
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div*div + div / 2;//��ɫͨ��
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div*div + div / 2;//��ɫͨ��
		}
	}
}


