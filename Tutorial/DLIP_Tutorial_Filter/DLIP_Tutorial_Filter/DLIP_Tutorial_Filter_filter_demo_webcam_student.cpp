/*------------------------------------------------------/
* Image Proccessing with Deep Learning
* OpenCV : Filter Demo - Video
* Created: 2021-Spring
------------------------------------------------------*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

#define		NONE		0
#define		BLUR		1
#define		GAUSSIAN	2
#define		LAPLASIAN	3

#define		UP			72
#define		DOWN		80

using namespace std;
using namespace cv;

int main()
{
	/*  open the video camera no.0  */
	VideoCapture cap(0);

	if (!cap.isOpened())	// if not success, exit the programm
	{
		cout << "Cannot open the video cam\n";
		return -1;
	}

	namedWindow("MyVideo", WINDOW_AUTOSIZE);

	int key = 0;
	int kernel_size = 7;
	int filter_type = 0;
	int arrow = 0;

	String text = "MODE: NONE"; // ³ÖÀ» ±Û¾¾
	Point org(50, 100); // ±Û¾¾ÀÇ ½ÃÀÛ À§Ä¡
	int fontFace = FONT_HERSHEY_SIMPLEX; // ±Û¾¾ÀÇ ÆùÆ®
	double fontScale = 1; // ±Û¾¾ÀÇ Å©±â ºñÀ²
	Scalar color(255, 255, 255); // ±Û¾¾ÀÇ »ö»ó (»¡°£»ö)
	int thickness = 3; // ±Û¾¾ÀÇ ±½±â
	int lineType = LINE_AA; // ±Û¾¾ÀÇ ¼± Å¸ÀÔ

	while (1)
	{
		Mat src, dst;

		/*  read a new frame from video  */
		bool bSuccess = cap.read(src);

		if (!bSuccess)	// if not success, break loop
		{
			cout << "Cannot find a frame from  video stream\n";
			break;
		}
		key = waitKeyEx(30);

		if (key == 27) // wait for 'ESC' press for 30ms. If 'ESC' is pressed, break loop
		{
			cout << "ESC key is pressed by user\n";
			break;
		}
		else if (key == 'n' || key == 'N') {

			filter_type = NONE;	// blur
			cout << "NONE" << endl;
		}

		else if (key == 'b' || key == 'B')
		{
			filter_type = BLUR;
			cout << "BLUR" << endl;
		}
		else if (key == 'g' || key == 'G') {

			filter_type = GAUSSIAN;
			cout << "GAUSSIAN" << endl;
		}
		else if (key == 'l' || key == 'L') {

			filter_type = LAPLASIAN;
			cout << "LAPLASIAN" << endl;
		}
	
		else if (key == 0x260000) {

			cout << "Up" << endl;
			kernel_size += 2;

		}
		else if (key == 0x280000) {

			cout << "DOWN" << endl;
			kernel_size -= 2;
			if (kernel_size < 1) {
				kernel_size = 1;
			}
		}

		if (filter_type == NONE){
				
			dst = src;
			text = "MODE: NONE";
		}
		else if (filter_type == BLUR) {

			blur(src, dst, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));
			text = "MODE: BLUR";

		}
		else if (filter_type == GAUSSIAN) {

			cv::GaussianBlur(src, dst, cv::Size(kernel_size, kernel_size), 0);
			text = "MODE: GAUSSIAN";

		}
			
		else if (filter_type == LAPLASIAN){
		
			cv::Laplacian(src, dst, CV_16S, kernel_size, 1, 0, cv::BORDER_DEFAULT);
			src.convertTo(src, CV_16S);
			cv::Mat result_laplcaian = src - dst;
			text = "MODE: LAPLASIAN";

		}
		putText(dst, text, org, fontFace, fontScale, color, thickness, lineType); // ¿µ»ó¿¡ ±Û¾¾ ³Ö±â
		imshow("MyVideo", dst);
	}
	return 0;
}