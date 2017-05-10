/*�˴�����Ҫ����������ɫ���ж�ֵ�����Ӷ�Ѱ���ض���ɫͼ�������*/
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
	imshow("ԭ��", img);
	//waitKey(0);
	/*	Mat out;
	bilateralFilter(img, out, 25, 25 * 2, 25 / 2);//����˫���˲���ȥ�ﱣ��
	//medianBlur(img, out, 7);
	imshow("ԭ��2", out);
	img = out;
	*/

	/*
	Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	Mat out;
	//�������Ͳ���
	dilate(img, out, element);

	imshow("ԭ��2", out);
	img = out;
	*/
	/*
	Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	Mat out;
	//���и�ʴ����
	erode(img, out, element);

	imshow("ԭ��2", out);
	img = out;
	*/
	/*
	Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	//������̬ѧ����
	morphologyEx(img, img, MORPH_CLOSE, element);//������

	imshow("ԭ��2", img);
	*/

	Mat bilateralFilter_img, img_gray, dst, abs_dst;
	bilateralFilter(img, bilateralFilter_img, 25, 25 * 2, 25 / 2);//����˫���˲���ȥ�ﱣ��
	Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));
	//������̬ѧ����
	morphologyEx(bilateralFilter_img, bilateralFilter_img, MORPH_CLOSE, element);//������
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

	imshow("��ͼx", img);

	//��4��ת��Ϊ�Ҷ�ͼ
	cvtColor(img, img_gray, CV_RGB2GRAY);

	//��5��ʹ��Laplace����
	Laplacian(img_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

	//��6���������ֵ���������ת����8λ
	convertScaleAbs(dst, abs_dst);
	imshow("��ͼ", abs_dst);

	Mat mergeImg;//�ϲ����ͼ��
				 //�����洢��ͨ��ͼƬ������
	vector<Mat> splitBGR(img.channels());
	//�ָ�ͨ�����洢��splitBGR��
	split(img, splitBGR);
	//�Ը���ͨ���ֱ����ֱ��ͼ���⻯
	for (int i = 0; i<img.channels(); i++)
		equalizeHist(splitBGR[i], splitBGR[i]);
	//�ϲ�ͨ��
	merge(splitBGR, mergeImg);

	namedWindow("equalizeHist");
	imshow("equalizeHist", mergeImg);

	//��4��ת��Ϊ�Ҷ�ͼ
	cvtColor(mergeImg, img_gray, CV_RGB2GRAY);

	//��5��ʹ��Laplace����
	Laplacian(img_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

	//��6���������ֵ���������ת����8λ
	convertScaleAbs(dst, abs_dst);
	imshow("��ͼ", abs_dst);
	imwrite("10086.jpg", abs_dst);
	waitKey();
	return 0;
}
