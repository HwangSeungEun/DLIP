/*------------------------------------------------------/
* Image Proccessing with Deep Learning
* OpenCV Tutorial: Image read/write/display
* Created: 2021-Spring
------------------------------------------------------*/

#include <iostream>
#include <opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	/*  read image  */
	String filename1 = "../../../Image/image.jpg";
	Mat img = imread(filename1);
	Mat img_gray = imread(filename1, 0);  // read in grayscale

	/*  write image  */
	String filename2 = "../../../Image/writeTest.jpg";
	imwrite(filename2, img_gray);

	/*  display image  */
	//namedWindow("image", WINDOW_AUTOSIZE);
	imshow("image", img);

	//namedWindow("image_gray", WINDOW_AUTOSIZE);
	imshow("image_gray", img_gray);

	waitKey(0);
	
	return 0;
}