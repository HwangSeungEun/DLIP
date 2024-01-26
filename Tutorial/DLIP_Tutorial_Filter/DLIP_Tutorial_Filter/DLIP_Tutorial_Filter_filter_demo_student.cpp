/* ------------------------------------------------------ /
*Image Proccessing with Deep Learning
* OpenCV : Filter Demo
* Created : 2021 - Spring
------------------------------------------------------ */

#include <opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void main()
{
	cv::Mat src, dst;
	src = cv::imread("../../../Image/blurry_moon.tif", 0);

	int i = 3;
	Size kernelSize = cv::Size(i, i);

	/* Blur */
	cv::blur(src, dst, cv::Size(i, i), cv::Point(-1, -1));
	namedWindow("Blur", WINDOW_AUTOSIZE);
	imshow("Blur", dst);

	/*filter2D*/
	cv::filter2D(src, dst, CV_8U, 5, cv::Point(-1, -1));
	namedWindow("filter2D", WINDOW_AUTOSIZE);
	imshow("filter2D", dst);

	/* Gaussian Filter */
	cv::GaussianBlur(src, dst, cv::Size(i, i), 0);
	namedWindow("Gaussian", WINDOW_AUTOSIZE);
	imshow("Gaussian", dst);

	/* Median Filter */
	cv::medianBlur(src, dst, 7); // kernal size는 1이 아닌 홀수
	namedWindow("Median", WINDOW_AUTOSIZE);
	imshow("Median", dst);

	int i = 3;
	cv::bilateralFilter(src, dst, i, i * 2, i / 2);
	namedWindow("bilateralFilter", WINDOW_AUTOSIZE);
	cv::imshow("bilateralFilter", dst);

	/* Laplacian Filter */
	int kernel_size = 3;
	int scale		= 1;
	int delta		= 0;
	int ddepth		= CV_16S;

	cv::Laplacian(src, dst, ddepth, kernel_size, scale, delta, cv::BORDER_DEFAULT);
	src.convertTo(src, CV_16S);
	cv::Mat result_laplcaian = src - dst;
	result_laplcaian.convertTo(result_laplcaian, CV_8U);
	namedWindow("Laplacian", WINDOW_AUTOSIZE);
	cv::imshow("Laplacian", result_laplcaian);


	cv::waitKey(0);
}


