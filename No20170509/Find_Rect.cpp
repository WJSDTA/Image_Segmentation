/*寻找外接矩形代码可用*/

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

int main(int argc, char** argv)
{
	/// 载入原图像, 返回3通道图像
	src = imread("F:\\10086.jpg");

	/// 转化成灰度图像并进行平滑
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	/// 创建窗口
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	createTrackbar(" Threshold:", "Source", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

/** @thresh_callback 函数 */

void thresh_callback(int, void*)
{
	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// 使用Threshold检测边缘
	threshold(src_gray, threshold_output, thresh, 255, THRESH_BINARY);//进行二值化处理
	/// 找到轮廓
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));//寻找轮廓

	/// 多边形逼近轮廓 + 获取矩形和圆形边界框
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
		minEnclosingCircle(contours_poly[i], center[i], radius[i]);
	}

	Mat image = imread("F://test1.jpg");;
	/// 画多边形轮廓 + 包围的矩形框 + 圆形框
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));//得到轮廓外接矩形数据结构   
	//	circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);

	
		// image = drawing;

		if (boundRect[i].area()>1000) //有些轮廓就是一个点，要舍去    
		{

			cout << i << endl;
			cv::Mat imageROI = image(boundRect[i]);//根据轮廓外接矩形信息进行截取RIO感兴趣部分图像    
		std::stringstream ss;//int转换为string    
			std::string str;
			ss << i;
			ss >> str;
		//string tempname = pathWrite + "\\" + str + "result.jpg"; <span style = "font-family: Arial, Helvetica, sans-serif;">//pathWrite变量是文件夹路径   
			//	imwrite(tempname.c_str(), imageROI);//存储图像至指定文件夹 */   
													//cout<<tempname<<endl;   
			  //   namedWindow("Contours %d", CV_WINDOW_AUTOSIZE);
									imshow(str,imageROI);   
													//cvResetImageROI(imageROI);
		}
	}

	/// 显示在一个窗口
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}
