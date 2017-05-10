/*此为测试代码，对整体无作用*/
/*
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// 函数声明
void thresh_callback(int, void*);

/** @主函数 */
/*
int main(int argc, char** argv[])
{
	/// 载入原图像, 返回3通道图像
	src = imread("2244.jpg", 1);
	imshow("原图，这是自己改写的", src);
	/// 转化成灰度图像并进行平滑
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	/// 创建窗口
	char* source_window = "Contours";//这里的Contours原来都是Source，被我小小改了下
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	//***************************************************************************************************
	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// 使用Threshold检测边缘
	threshold(src_gray, threshold_output, 245, 255, THRESH_BINARY);
	//Canny(src_gray,threshold_output,136,196,3);
	//imshow("阈值图",threshold_output);

	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));//CHAIN_APPROX_NONE全体,CV_CHAIN_APPROX_SIMPLE,,,RETR_TREE

																									  /// 多边形逼近轮廓 + 获取矩形和圆形边界框
	vector<vector<Point> > contours_poly(contours.size());


	for (int i = 0; i < contours.size(); i++)
	{
		if (i == 1)//这里控制只输出第二层轮廓，
		{
			approxPolyDP(Mat(contours[i]), contours_poly[i], 0, true);//逼近多边形曲线，数字表示多边形的近似程度

		}
	}


	/// 画多边形轮廓 
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(211, 55, 155);
		//if(contours.size()==2)
		drawContours(src, contours, i, color, 2, 8, vector<Vec4i>(), 0, Point());// 这里的 i 换成 1 就表示不画出最外层矩形轮廓
	}

	printf("轮廓数%d\n", contours.size());

	imshow("Contours", src);



	waitKey(0);
	return(0);
}*/