/*此代码主要用于利用颜色进行二值化，从而寻找特定颜色图像的轮廓*/
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include"opencv2/imgproc/imgproc.hpp"
#include <vector>
using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("F://test123.jpg");
	imshow("原画", img);
	//waitKey(0);
	/*	Mat out;
	bilateralFilter(img, out, 25, 25 * 2, 25 / 2);//进行双边滤波，去燥保边
	//medianBlur(img, out, 7);
	imshow("原画2", out);
	img = out;
	*/

	/*
	Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	Mat out;
	//进行膨胀操作
	dilate(img, out, element);

	imshow("原画2", out);
	img = out;
	*/
	/*
	Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	Mat out;
	//进行腐蚀操作
	erode(img, out, element);

	imshow("原画2", out);
	img = out;
	*/
	/*
	Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	//进行形态学操作
	morphologyEx(img, img, MORPH_CLOSE, element);//闭运算

	imshow("原画2", img);
	*/

	Mat bilateralFilter_img, img_gray, dst, abs_dst;
	bilateralFilter(img, bilateralFilter_img, 25, 25 * 2, 25 / 2);//进行双边滤波，去燥保边
	Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	//进行形态学操作
	morphologyEx(bilateralFilter_img, bilateralFilter_img, MORPH_CLOSE, element);//闭运算
	img = bilateralFilter_img;

	for (int row = 0; row < img.rows; row++)
	{
		for (int col = 0; col < img.cols; col++)
		{
			if (((img.at<Vec3b>(row, col)[1] - img.at<Vec3b>(row, col)[0] > 8))
				&& ((img.at<Vec3b>(row, col)[1] - img.at<Vec3b>(row, col)[2] >8)))
				//if(img.at<Vec3b>(row, col)[0]==0&& img.at<Vec3b>(row, col)[2]==0)
			{
				//img.at<Vec3b>(row, col) = Vec3b(0, 0, 0);
			}
			else {
				//img.at<Vec3b>(row, col) = Vec3b(0, 0, 0);
				img.at<Vec3b>(row, col) = Vec3b(255, 255, 255);
			}
		}
	}

	imshow("新图x", img);

	//【4】转换为灰度图
	cvtColor(img, img_gray, CV_RGB2GRAY);

	//【5】使用Laplace函数
	Laplacian(img_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

	//【6】计算绝对值，并将结果转换成8位
	convertScaleAbs(dst, abs_dst);
	imshow("新图", abs_dst);

	Mat mergeImg;//合并后的图像
				 //用来存储各通道图片的向量
	vector<Mat> splitBGR(img.channels());
	//分割通道，存储到splitBGR中
	split(img, splitBGR);
	//对各个通道分别进行直方图均衡化
	for (int i = 0; i<img.channels(); i++)
		equalizeHist(splitBGR[i], splitBGR[i]);
	//合并通道
	merge(splitBGR, mergeImg);

	namedWindow("equalizeHist");
	imshow("equalizeHist", mergeImg);

	//【4】转换为灰度图
	cvtColor(mergeImg, img_gray, CV_RGB2GRAY);

	//【5】使用Laplace函数
	Laplacian(img_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

	//【6】计算绝对值，并将结果转换成8位
	convertScaleAbs(dst, abs_dst);
	imshow("新图", abs_dst);
	imwrite("10086.jpg", abs_dst);
	waitKey();
	return 0;
}
