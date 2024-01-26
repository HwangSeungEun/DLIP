/*------------------------------------------------------/
* Image Proccessing with Deep Learning
* OpenCV : Threshold using Trackbar Demo
* Created: 2023-Spring
------------------------------------------------------*/

#include <opencv.hpp>
#include <iostream>



using namespace std;
using namespace cv;

// Global variables for Threshold
int threshold_value = 0;
int threshold_type	= 0;
int morphology_type = 0;

int c				= 0;
int blockSize		= 0;

int const max_value = 255;
int const max_type	= 4;


int const max_binary_value = 255;

// Global variables for Morphology
int element_shape = MORPH_RECT;		// MORPH_RECT, MORPH_ELIPSE, MORPH_CROSS
int n = 3;
Mat element = getStructuringElement(element_shape, Size(n, n));

Mat src, src_gray, dst, dst_morph;

// Trackbar strings
String window_name		= "Threshold & Morphology Demo";

String trackbar_type	= "Thresh Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Invertd";
String trackbar_value	= "Thresh Value";
String trackbar_morph	= "Morph Type 0: None \n 1: erode \n 2: dilate \n 3: close \n 4: open";
String trackbar_blocksz = "block size: 3,5,7";
String trackbar_c		= "value of c";

// Function headers
void Threshold_Demo	(int, void*);
void Morphology_Demo(int, void*);

int main()
{
	// Load an image
	src = imread("../../../Image/Finger_print_gray.tif", IMREAD_COLOR);

	// Convert the image to Gray
	cvtColor(src, src_gray, COLOR_BGR2GRAY);

	// Create a window to display the results
	namedWindow(window_name, WINDOW_NORMAL);

	// Create trackbar to choose type of threshold
	createTrackbar(trackbar_type,	window_name, &threshold_type,	8,	Threshold_Demo);
	createTrackbar(trackbar_value,	window_name, &threshold_value,	max_value,	Threshold_Demo);


	createTrackbar(trackbar_morph,	window_name, &morphology_type,	max_type,	Morphology_Demo);
	createTrackbar(trackbar_blocksz,window_name, &blockSize,	5, Threshold_Demo);
	createTrackbar(trackbar_c,	window_name, &c, 10, Threshold_Demo);

	// Call the function to initialize
	Threshold_Demo(0, 0);
	Morphology_Demo(0, 0);

	// Wait until user finishes program
	while (true) {
		int c = waitKey(20);
		if (c == 27)
			break;
	}
}

void Threshold_Demo(int, void*)	// default form of callback function for trackbar
{
	/* 
	* 0: Binary
	* 1: Threshold Truncated
	* 2: Threshold to Zero
	* 3: Threshold to Zero Inverted
	* 4: Threshold to Zero Inverted
	* 8: otsu -> threshold°ªÀÌ ÀÚµ¿À¸·Î ¸ÂÃçÁü --> ÃÖÀûÈ­ µÊ
	*/
/*	if (threshold_type == 5) {

		threshold_type = 7;
	}else*/ 

	if (threshold_type == 6) {
		
		threshold_type = 8;

	}
	//else if (threshold_type == 7) {

	//	threshold_type = 16;

	//}
	
	blockSize = (blockSize + 1) * 2 + 1;

	/*
		0 --> 3    
		1 --> 5
		2 --> 7
		3 --> 9
		4 --> 11
	*/
	threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);

	if (threshold_type == 8) {

		adaptiveThreshold(src_gray, dst, max_binary_value, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, blockSize, c);

	}

	imshow(window_name, dst);
}

void Morphology_Demo(int, void*)  // default form of callback function for trackbar
{
	/*
	* 0: None
	* 1: Erode
	* 2: Dilate
	* 3: Close
	* 4: Open
	*/
	switch (morphology_type) {
	case 0: dst.copyTo(dst_morph);	break;
	case 1: erode(dst, dst_morph, element); break;
	case 2: dilate(dst, dst_morph, element); break;
	case 3: morphologyEx(dst, dst_morph, MORPH_OPEN, element); break;
	case 4: morphologyEx(dst, dst_morph, MORPH_CLOSE, element); break;
	}
	imshow(window_name, dst_morph);
}
