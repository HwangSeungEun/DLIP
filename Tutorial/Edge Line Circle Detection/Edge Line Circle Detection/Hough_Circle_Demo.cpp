#include <opencv2/opencv.hpp>
#include "myFunc.h"


using namespace cv;
using namespace std;


Mat src, gray, dst_equ, dst_gau;
Mat dst, detected_edges;

int edgeThresh = 1;
int minDist = 26;
int maxDist = 1000;

int minRadius = 14;
int const maxRadius = 300;
int param1 = 100;
int param2 = 116;

int const maxparam1 = 300;
int const maxparam2 = 300;

int ratio = 3;
int kernel_size = 3;
const char* window_name = "Circle find";

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
	HoughCircles(dst_equ, circles, HOUGH_GRADIENT, 2, minDist, param1, param2 , minRadius );
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		/* draw the circle center */
		circle(dst, center, 3, Scalar(0, 255, 0), -1, 8, 0);

		/* draw the circle outline */
		circle(dst, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}

	namedWindow("circles", 1);
	imshow("circles", dst);

}



int main(int argc, char** argv)
{
	//String filename = "coins.png";
	String filename = "eyepupil.png";

	/* Read the image */
	src = imread(filename, 1);

	if (!src.data)
	{
		printf(" Error opening image\n");
		return -1;
	}

	cvtColor(src, gray, COLOR_BGR2GRAY);

	plotHist(gray, "gray", 500, 500);

	/* smooth it, otherwise a lot of false circles may be detected */
	GaussianBlur(gray, dst_gau, Size(9, 9), 2, 2);

	equalizeHist(dst_gau, dst_equ);
	plotHist(dst_equ, "dst_equ", 500, 500);


	minDist = gray.rows / 4;
	/// Create a window
	namedWindow(window_name, WINDOW_AUTOSIZE);

	/// Create a Trackbar for user to enter threshold
	createTrackbar("Min Dist", window_name, &minDist, gray.rows, find_HoughCircles);
	createTrackbar("param1", window_name, &param1, maxparam1, find_HoughCircles);
	createTrackbar("param2", window_name, &param2, maxparam2, find_HoughCircles);
	createTrackbar("Max radius", window_name, &minRadius, maxRadius, find_HoughCircles);

	/// Show the image
	find_HoughCircles(0, 0);

	/* Wait and Exit */
	waitKey(0);
	return 0;
}