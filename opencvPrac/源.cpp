#include <opencv2/opencv.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include  <opencv2/highgui/highgui.hpp>
#include <cassert>
#include "camera.h"
#include "accpix.h"
#include "camboder.h"
using namespace cv;
using namespace std;

int main()
{
	int res = 0;
	camera_show(1);  //打开相机

	camera_cutpart(0, 300, 300, 150, 150);//640*480


	Mat image0;
	image0 = imread("10.jpg");
	uchar value = image0.at<uchar>(3, 4);
	cout << value<<endl;

	cout << image0.size() << endl;

	Mat imim;
	imim = image0(Rect(50, 50, 50, 50));//220*147
	imshow("ss", imim);

	//imshow("10_image", image0);
	//res=fix_two();   //对两张图片进行叠加
	//res = mouse_scan();
	//res = mouse_scan_image();
	
	//res = mouse_scan_camera();


	//vector<int> v_textvec(10);
	//v_textvec.push_back(10);
	//v_textvec.push_back(12);

	//cout << v_textvec.size();


	
	waitKey(0);

	return 0;
}