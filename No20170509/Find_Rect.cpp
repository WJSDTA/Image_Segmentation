/*Ѱ����Ӿ��δ������*/

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

/// ��������
void thresh_callback(int, void*);

/** @������ */

int main(int argc, char** argv)
{
	/// ����ԭͼ��, ����3ͨ��ͼ��
	src = imread("F:\\10086.jpg");

	/// ת���ɻҶ�ͼ�񲢽���ƽ��
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	/// ��������
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	createTrackbar(" Threshold:", "Source", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

/** @thresh_callback ���� */

void thresh_callback(int, void*)
{
	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// ʹ��Threshold����Ե
	threshold(src_gray, threshold_output, thresh, 255, THRESH_BINARY);//���ж�ֵ������
	/// �ҵ�����
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));//Ѱ������

	/// ����αƽ����� + ��ȡ���κ�Բ�α߽��
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
	/// ����������� + ��Χ�ľ��ο� + Բ�ο�
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));//�õ�������Ӿ������ݽṹ   
	//	circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);

	
		// image = drawing;

		if (boundRect[i].area()>1000) //��Щ��������һ���㣬Ҫ��ȥ    
		{

			cout << i << endl;
			cv::Mat imageROI = image(boundRect[i]);//����������Ӿ�����Ϣ���н�ȡRIO����Ȥ����ͼ��    
		std::stringstream ss;//intת��Ϊstring    
			std::string str;
			ss << i;
			ss >> str;
		//string tempname = pathWrite + "\\" + str + "result.jpg"; <span style = "font-family: Arial, Helvetica, sans-serif;">//pathWrite�������ļ���·��   
			//	imwrite(tempname.c_str(), imageROI);//�洢ͼ����ָ���ļ��� */   
													//cout<<tempname<<endl;   
			  //   namedWindow("Contours %d", CV_WINDOW_AUTOSIZE);
									imshow(str,imageROI);   
													//cvResetImageROI(imageROI);
		}
	}

	/// ��ʾ��һ������
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}
