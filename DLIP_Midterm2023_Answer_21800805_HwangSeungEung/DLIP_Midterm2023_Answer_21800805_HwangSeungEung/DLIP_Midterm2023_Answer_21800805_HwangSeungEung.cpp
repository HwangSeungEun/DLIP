
/* 

	DLIP MIDTERM 2023-1  Submission


	NAME:Hwang SeungEun

*/

#include "myFunc.h"

using namespace std;
using namespace cv;


cv::Mat dst, dst_gray, dst_equ, dst_filt, dst_mask, dst_thr, dst_inran,
dst_hsv, dst_morph, dst_ChannelV, mask, mask_V;


int Threshold_val = 146;


void Threshold_img(int, void*);


int main()
{
	Mat src = imread("midterm_brick1.jpg");
	int width = src.cols;
	int height = src.rows;
	int width_pri = width / 2;
	int height_pri = height / 2;

	if (src.empty())					// Load image check
	{
		cout << "File Read Failed : src is empty" << endl;
		waitKey(0);
	}

	//printImg("src", src, width_pri, height_pri);

	src.copyTo(dst);
	// ------------------------- convert to Gray -------------------------
	cvtColor(src, dst_gray, COLOR_BGR2GRAY);
	//printImg("gray", dst_gray, width_pri, height_pri);
	//plotHist(dst_gray, "hist", 500, 500);


	// ------------------------- equalize Histogram -------------------------
	equalizeHist(dst_gray, dst_equ);
	//plotHist(dst_equ, "hist equal", 500, 500);
	//printImg("hist_equal", dst_equ, width_pri, height_pri);

	// ------------------------- filter -------------------------
	int kernel = 5;
	//medianBlur(dst_gray, dst_filt, kernel);
	GaussianBlur(dst_equ, dst_filt, Size(kernel, kernel), 0);
	//printImg("dst_filt", dst_filt, width_pri, height_pri);

	// ------------------------- Threshold -------------------------
	namedWindow("Thresh", WINDOW_AUTOSIZE);
	createTrackbar("THreshold", "Thresh", &Threshold_val, 255, Threshold_img);

	// ------------------------- Morphology -------------------------
	int element_shape = MORPH_RECT;		// MORPH_RECT, MORPH_ELLIPSE, MORPH_CROSS
	int n = 3;
	Mat element = getStructuringElement(element_shape, Size(n, n));

	erode(dst_thr, dst_morph, element, Point(-1, -1), 2);
	dilate(dst_morph, dst_morph, element, Point(-1, -1), 2);
	//morphologyEx(dst_thr, dst_morph, MORPH_OPEN, element, Point(-1, -1), 4);
	morphologyEx(dst_morph, dst_morph, MORPH_CLOSE, element, Point(-1, -1), 8);
	


	
	printImg("morphology", dst_morph, width_pri, height_pri);

	// ------------------------- contour -------------------------
	vector<vector<Point>> contours;
	findContours(dst_morph, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	
	int brick_size_pixel[4][2] = { 0 , };
	double  brick_size_cm[4][2] = { 0.0 , };
	double  Area[4] = { 0, };


	int number_birc = 0;
	for (size_t i = 0; i < contours.size(); i++) {

		int area = contourArea(contours[i]);
		Rect box = boundingRect(contours[i]);
		Point org = Point(box.br().x, box.tl().y);


		if (area > 500) {
			
			//rectangle(src, box, Scalar(0, 0, 255), 2, LINE_AA);
			cv::drawContours(src, contours, static_cast<int>(i), cv::Scalar(0, 0, 255), cv::FILLED);

			// 이건 숫자 위치 확인용
			//putText(src, to_string(number_birc), Point(box.br().x, box.tl().y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 3, LINE_AA);

			// 지금 막힌거 숫자를 출력해야한다.
			// box.width box.height를가 있기 때문에 픽셀의 크기는 다 안다. 숫자로 변환해야함

			brick_size_pixel[number_birc][0] = box.width;
			brick_size_pixel[number_birc][1] = box.height;
			
			brick_size_cm[number_birc][0] = double (box.width) / 73 * 5 ;
			brick_size_cm[number_birc][1] = double (box.height) / 71 * 5;

			Area[number_birc] = brick_size_cm[number_birc][0] * brick_size_cm[number_birc][1];

			number_birc++;

			//cout << "-------------------------------------------------------------------" << endl;
			//cout << "area:" << area << endl;
			//cout << "-------------------------------------------------------------------" << endl;

		}
	}
	
	//for (int i = 0; i < 2; i ++) {
	//	// pixel swap
	//	int temp = 0;
	//	temp = brick_size_pixel[1][i];
	//	brick_size_pixel[1][i] = brick_size_pixel[3][i];
	//	brick_size_pixel[3][i] = temp;

	//	// cm swap
	//	temp = 0;
	//	temp = brick_size_cm[1][i];
	//	brick_size_cm[1][i] = brick_size_cm[3][i];
	//	brick_size_cm[3][i] = temp;


	//}
	//// area swap
	//int temp = 0;
	//temp = Area[1];
	//Area[1] = Area[3];
	//Area[3] = temp;

	cout << "-------------------------------------------------------------------" << endl;
	cout << "Box No." << "\t"<< "Pixel(W x H)" << "\t" << "Size(W[cm] x H[cm]) = \t Area[cm2]"  << endl;

	for (int i = 0; i < 4; i++) {

		cout << "-------------------------------------------------------------------" << endl;
		printf("Box %d \t %d X %d \t %0.1lf X %0.1lf \t\t = %0.1lf \n", i + 1, brick_size_pixel[i][0], brick_size_pixel[i][1], brick_size_cm[i][0], brick_size_cm[i][1], Area[i]);
		//cout << "Box " << i << "\t" << brick_size_pixel[i][0] << " X " << brick_size_pixel[i][1]<< "\t\t\t" << brick_size_cm[i][0] << " X " << brick_size_cm[i][1] << endl;

	}
	cout << "-------------------------------------------------------------------" << endl;

	printImg("output_1", src, width_pri, height_pri);


	
	waitKey(0);
	return 0;
}



void Threshold_img(int, void*) {
/*
* THRESH_BINARY     = 0
* THRESH_BINARY_INV = 1
* THRESH_TRUNC      = 2
* THRESH_TOZERO     = 3
* THRESH_TOZERO_INV = 4
*/

	threshold(dst_filt, dst_thr, Threshold_val, 255, THRESH_BINARY);
	//printImg("Threshold_img", dst_thr, width_pri, height_pri);

}