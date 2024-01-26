#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat src, src_gray, gray, dst_equ, dst_gau;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold = 177;
int const max_lowThreshold =255;
int ratio = 3;
int kernel_size = 3;
const char* window_name1 = "Edge Map";
// ---------------------------------------------
int minDist = 55;
int maxDist = 1000;

int minRadius = 184;
int const maxRadius = 300;
int param1 = 114;
int param2 = 145;

int const maxparam1 = 300;
int const maxparam2 = 300;

const char* window_name2 = "Circle find";
// ---------------------------------------------


void find_HoughCircles(int, void*)
{
	/// Create a matrix of the same type and size as src (for dst)
	src.copyTo(dst);
	vector<Vec3f> circles;
	if (minDist < 1) {
		minDist = 1;
	}
	if (minRadius < 10) {
		minRadius = 10;
	}
	HoughCircles(detected_edges, circles, HOUGH_GRADIENT, 2, minDist, param1, param2, minRadius);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		/* draw the circle center */
		circle(dst, center, 3, Scalar(0, 255, 0), -1, 8, 0);

		/* draw the circle outline */
		circle(dst, center, radius, Scalar(255, 0, 0), 3, 8, 0);
	}

	namedWindow("circles", 1);
	imshow("circles", dst);

}


/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{

	/// Canny detector
	Canny(dst_equ, detected_edges, lowThreshold, lowThreshold * 3, kernel_size);

	/// Using Canny's output as a mask, we display our result
	dst = Scalar::all(0);

	src.copyTo(dst, detected_edges);
	imshow(window_name1, dst);
}


/** @function main */
int main(int argc, char** argv)
{
	/// Load an image
	//const char* filename = "../images/pillsetc.png";
	const char* filename = "TrafficSign1.png";
	//const char* filename = "../images/TrafficSign1.png";

	/// Read the image
	src = imread(filename, 1);

	if (!src.data)
	{
		return -1;
	}

	/// Create a matrix of the same type and size as src (for dst)
	dst.create(src.size(), src.type());

	/// Convert the image to grayscale
	cvtColor(src, gray, COLOR_BGR2GRAY);
	/* smooth it, otherwise a lot of false circles may be detected */
	GaussianBlur(gray, dst_gau, Size(9, 9), 2, 2);

	equalizeHist(dst_gau, dst_equ);
	/// Create a window
	namedWindow(window_name1, WINDOW_AUTOSIZE);

	/// Create a Trackbar for user to enter threshold
	createTrackbar("Min Threshold:", window_name1, &lowThreshold, max_lowThreshold, CannyThreshold);

	namedWindow(window_name2, WINDOW_AUTOSIZE);

	/// Create a Trackbar for user to enter threshold
	createTrackbar("Min Dist", window_name2, &minDist, gray.rows, find_HoughCircles);
	createTrackbar("param1", window_name2, &param1, maxparam1, find_HoughCircles);
	createTrackbar("param2", window_name2, &param2, maxparam2, find_HoughCircles);
	createTrackbar("Max radius", window_name2, &minRadius, maxRadius, find_HoughCircles);


	/// Show the image
	CannyThreshold(0, 0);

	/// Show the image
	find_HoughCircles(0, 0);

	/// Wait until user exit program by pressing a key
	waitKey(0);

	return 0;
}