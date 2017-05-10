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

/// ��������
void thresh_callback(int, void*);

/** @������ */
/*
int main(int argc, char** argv[])
{
	/// ����ԭͼ��, ����3ͨ��ͼ��
	src = imread("2244.jpg", 1);
	imshow("ԭͼ�������Լ���д��", src);
	/// ת���ɻҶ�ͼ�񲢽���ƽ��
	cvtColor(src, src_gray, CV_BGR2GRAY);
	blur(src_gray, src_gray, Size(3, 3));

	/// ��������
	char* source_window = "Contours";//�����Contoursԭ������Source������СС������
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	//***************************************************************************************************
	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// ʹ��Threshold����Ե
	threshold(src_gray, threshold_output, 245, 255, THRESH_BINARY);
	//Canny(src_gray,threshold_output,136,196,3);
	//imshow("��ֵͼ",threshold_output);

	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));//CHAIN_APPROX_NONEȫ��,CV_CHAIN_APPROX_SIMPLE,,,RETR_TREE

																									  /// ����αƽ����� + ��ȡ���κ�Բ�α߽��
	vector<vector<Point> > contours_poly(contours.size());


	for (int i = 0; i < contours.size(); i++)
	{
		if (i == 1)//�������ֻ����ڶ���������
		{
			approxPolyDP(Mat(contours[i]), contours_poly[i], 0, true);//�ƽ���������ߣ����ֱ�ʾ����εĽ��Ƴ̶�

		}
	}


	/// ����������� 
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(211, 55, 155);
		//if(contours.size()==2)
		drawContours(src, contours, i, color, 2, 8, vector<Vec4i>(), 0, Point());// ����� i ���� 1 �ͱ�ʾ������������������
	}

	printf("������%d\n", contours.size());

	imshow("Contours", src);



	waitKey(0);
	return(0);
}*/