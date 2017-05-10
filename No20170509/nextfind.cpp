/*
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
int main()
{
	using namespace cv;

	Mat image = imread("F://10086.jpg");
	cvtColor(image, image, CV_BGR2GRAY);
	vector<vector<Point>> contours;
	// find
	findContours(image, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	

	// draw
	Mat result(image.size(), CV_8U, Scalar(0));
	drawContours(result, contours, -1, Scalar(255), 2);
	namedWindow("contours");
	imshow("contours", result);
	waitKey();
	return 0;
}

*/
