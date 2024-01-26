#include "myFunc.h"

cv::Mat dst, dst_gray, dst_equ ,dst_filt, dst_mask, dst_thr, dst_inran,
		dst_hsv, dst_morph, dst_ChannelV, mask, mask_V;

int thresh_val = 140;
int thresh_max = 255;


int hmin = 5, hmax = 13, smin = 50, smax = 100, vmin = 122, vmax = 225;

// ------------------------- img load -------------------------
Mat src = imread("last_test.jpg");
int width = src.cols;
int height = src.rows;
int width_pri = width / 2;
int height_pri = height / 2;


void inrangeThreshold(int, void*);


int main(void) {

	// 얼굴 detect 순서

	if (src.empty()) {
		std::cout << "Error loading image" << std::endl;
		return -1;
	}

	src.copyTo(dst);

	//printImg("src", src, width_pri, height_pri);

	// ------------------------- convert to hsv -------------------------
	cvtColor(src, dst_hsv, COLOR_BGR2HSV);
	//plotHist(dst_gray, "gray hist", 500, 500);
	//printImg("gray", dst_gray, width_pri, height_pri);

	// ------------------------- filter -------------------------
	int kernel_gau = 5;
	int sigam_gau = 0;
	GaussianBlur(dst_hsv, dst_filt, Size(kernel_gau, kernel_gau), sigam_gau);
	//printImg("gaussain filter", dst_filt, width_pri, height_pri);


	// ------------------------- inrange (threshold) -------------------------
		// TrackBar 설정
	namedWindow("Inrange", WINDOW_AUTOSIZE);
	createTrackbar("Hmin", "Inrange", &hmin, 179, inrangeThreshold);
	createTrackbar("Hmax", "Inrange", &hmax, 179, inrangeThreshold);
	createTrackbar("Smin", "Inrange", &smin, 255, inrangeThreshold);
	createTrackbar("Smax", "Inrange", &smax, 255, inrangeThreshold);
	createTrackbar("Vmin", "Inrange", &vmin, 255, inrangeThreshold);
	createTrackbar("Vmax", "Inrange", &vmax, 255, inrangeThreshold);

	// ------------------------- morphology -------------------------
	int element_shape = MORPH_RECT;		// MORPH_RECT, MORPH_ELLIPSE, MORPH_CROSS
	int n = 3;
	Mat element = getStructuringElement(element_shape, Size(n, n));


	dilate(dst_inran, dst_morph, element, Point(-1, -1), 3, BORDER_DEFAULT);
	morphologyEx(dst_morph, dst_morph, MORPH_OPEN, element, Point(-1, -1), 5);
	//dilate(dst_morph, dst_morph, element, Point(-1, -1), 4, BORDER_DEFAULT);
	erode(dst_morph, dst_morph, element, Point(-1, -1), 2, BORDER_DEFAULT);
		
	printImg("morphology", dst_morph, width_pri, height_pri);
		
	
	// ------------------------- contour -------------------------
	vector<vector<Point>> contours;
	findContours(dst_morph, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

	int num_people = 0;
	for (size_t i = 0; i < contours.size(); i++) {

		int area = contourArea(contours[i]);
		Rect box = boundingRect(contours[i]);
		Point org = Point(box.br().x, box.tl().y);


		if (area > 5000) {

			rectangle(src, box, Scalar(0, 0, 255), 2, LINE_AA);
			// Mosaic effect
			int mosaicFactor = 10;
			Mat roiImg = src(box);
			Mat smallRoi, mosaicRoi;
			resize(roiImg, smallRoi, cv::Size(box.width / mosaicFactor, box.height / mosaicFactor), 0, 0, cv::INTER_LINEAR);
			resize(smallRoi, mosaicRoi, roiImg.size(), 0, 0, cv::INTER_NEAREST);
			mosaicRoi.copyTo(roiImg);
			num_people++;
		}


	}
	// Put the number of people on the image
	stringstream ss;
	ss << num_people;
	putText(src, "People: " + ss.str(), Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2, LINE_AA);
	printImg("output", src, width_pri, height_pri);

	waitKey(0);


	/*
	// ------------------------- Define the 5 points of the ROI (집모양) -------------------------
	std::vector<cv::Point> roiPoints;
	roiPoints.push_back(cv::Point(width / 2, height / 2.5));         // Top center
	roiPoints.push_back(cv::Point(0, height / 2));        // Left center
	roiPoints.push_back(cv::Point(0, height - 1));        // Left bottom
	roiPoints.push_back(cv::Point(width - 1, height - 1)); // Right bottom
	roiPoints.push_back(cv::Point(width - 1, height / 2)); // Right center

	// Create an empty mask with the same size as the input image
	Mat mask = Mat::zeros(src.size(), CV_8UC1);

	// Draw a filled polygon with the defined points on the mask
	const cv::Point* ppt[1] = { &roiPoints[0] };
	int npt[] = { 5 };
	cv::fillPoly(mask, ppt, npt, 1, cv::Scalar(255));

	// Apply the mask to the input image
	cv::Mat maskedImage;
	src.copyTo(maskedImage, mask);
	//printImg("mask", mask, width_pri, height_pri);

	// ------------------------- beatwise and -------------------------
	bitwise_and(mask, dst_filt, dst_mask);
	//printImg("dst_mask", dst_mask, width_pri, height_pri);
	*/


	return 0;
}



void inrangeThreshold(int, void*)
{

	inRange(dst_filt, Scalar(MIN(hmin, hmax), MIN(smin, smax), MIN(vmin, vmax)),
		Scalar(MAX(hmin, hmax), MAX(smin, smax), MAX(vmin, vmax)), dst_inran);
	printImg("inrange hsv", dst_inran, width_pri, height_pri);
}

