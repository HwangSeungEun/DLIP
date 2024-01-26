#include <opencv.hpp>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

using namespace cv;

int main()
{

	Mat src, src_gray, dst, dst_morph;
	src = cv::imread("../../../Image/coin.jpg", 0);

	if (src.empty())					// Load image check
	{

		std::cout << "File Read Failed : src is empty" << std::endl;
		waitKey(0);
	}
	// Create a window to display results
	namedWindow("DemoWIndow", WINDOW_AUTOSIZE); //CV_WINDOW_AUTOSIZE(1) :Fixed Window, 0: Unfixed window
	if (!src.empty())imshow("DemoWIndow", src); // Show image

	int threshold_value = 0;
	int threshold_type = 8;

	int const max_value = 255;
	int const max_type = 4;
	int const max_BINARY_value = 255;
	
	/* threshold_type
	0: Binary
	1: Binary Inverted
	2: Threshold Truncated
	3: Threshold to Zero
	4: Threshold to Zero Inverted
	8: otsu -> threshold∞™¿Ã ¿⁄µø¿∏∑Œ ∏¬√Á¡¸ --> √÷¿˚»≠ µ 
	*/

	threshold(src, dst, threshold_value, max_BINARY_value, threshold_type);

	namedWindow("ThreshWIndow", WINDOW_AUTOSIZE); //CV_WINDOW_AUTOSIZE(1) :Fixed Window, 0: Unfixed window
	imshow("ThreshWIndow", dst); // Show image

	waitKey(0);//Pause the program


	return 0;
}
