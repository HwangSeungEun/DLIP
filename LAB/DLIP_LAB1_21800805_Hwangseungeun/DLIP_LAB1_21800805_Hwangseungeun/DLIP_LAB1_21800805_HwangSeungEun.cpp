#include "myFunc.h"

#define M6_bolt		0
#define M5_bolt		1
#define M6_Nut		2
#define M5_Nut		3
#define M5_rect		4

Mat  src, dst, dst_gray, dst_filt, dst_thres, dst_morph, dst_cont, combine, dst_stack, dst_equal;

void Img_read(void);

void IMG_processing(void);

void Filter_Process(Mat& _input, Mat& _output, int _filter, int _kernel);

void Threshold_Process(Mat& _input, Mat& _output, int _value);

void Morphology_Process(Mat& _input, Mat& _output);

void Contour_Processing(Mat& _input, vector<vector<Point>>& _contour, vector<Vec4i>& _hierarchy);

void print_result(void);

int kernel = 5;
int thresh_value = 180;

Scalar colors[5] = {
	Scalar(255, 0, 0),  // ÆÄ¶û»ö
	Scalar(0, 0, 255),  // »¡°­»ö
	Scalar(0, 255, 255),  // ³ë¶û»ö
	Scalar(0, 255, 0),  // ³ì»ö
	Scalar(255, 255, 0)  // ÇÏ´Ã»ö
};

vector<vector<Point>> contours;
vector<Vec4i>	hierarchy;

vector <string> name = { "M6_bolt", "M5_bolt", "M6_Nut", "M5_Nut", "M5_rect" };
vector <int> count_obj = { 0, 0, 0, 0 ,0 };

int main() {

	// image processing
	IMG_processing();

	// print result
	print_result();

	// Wait until user finishes program
	while (true) {
		int c = waitKey(20);
		if (c == 27)
			break;
	}

	return 0;
}


void Img_read(void) {

	// img load
	src = imread("Lab_GrayScale_TestImage.jpg", 3);
	//src = imread("test_img.png", 3);

	// cvtColor BGR2GRAY
	cvtColor(src, dst_gray, COLOR_RGB2GRAY);

	namedWindow("raw imgae", WINDOW_FREERATIO);
	resizeWindow("raw imgae", Size(800, 800));
	imshow("raw imgae", src);

	// Load image check
	if (src.empty())
	{
		cout << "File Read Failed : src is empty" << endl;
		waitKey(0);
	}
}


void Filter_Process(Mat& _input, Mat& _output, int _filter, int _kernel) {

	if (_filter == BLUR) {

		blur(_input, _output, Size(_kernel, _kernel), Point(-1, -1));

	}
	else if (_filter == GAUSSIAN) {

		GaussianBlur(_input, _output, Size(_kernel, _kernel), 0);
		//text = "MODE: GAUSSIAN";
	}
	else if (_filter == MEDIAN) {

		medianBlur(_input, _output, _kernel);

	}
	//else if (_filter == ) {

	//bilateralFilter(_input, _output, _kernel);
	//}

	namedWindow("Filter imgae", WINDOW_FREERATIO);
	resizeWindow("Filter imgae", Size(800, 800));
	imshow("Filter imgae", _output);
}

void Threshold_Process(Mat& _input, Mat& _output, int _value) {

	/*
	* THRESH_BINARY     = 0
	* THRESH_BINARY_INV = 1
	* THRESH_TRUNC      = 2
	* THRESH_TOZERO     = 3
	* THRESH_TOZERO_INV = 4
	*/

	int _type = 0;

	if (_type == 8) {

		adaptiveThreshold(_input, _output, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);
		_output = 255 - _output;
	}
	else {

		threshold(_input, _output, _value, 255, _type);

	}
	namedWindow("Thresh imgae", WINDOW_FREERATIO);
	resizeWindow("Thresh imgae", Size(800, 800));
	imshow("Thresh imgae", _output);
}


void Morphology_Process(Mat& _input, Mat& _output) {

	int element_shape = MORPH_ELLIPSE;		// MORPH_RECT, MORPH_ELLIPSE, MORPH_CROSS
	int n = 3;
	Mat element = getStructuringElement(element_shape, Size(n, n));

	/*
		* 0: None
		* 1: Erode
		* 2: Dilate
		* 3: Close: dilate --> erosion
		* 4: Open: erosion --> dilate
	*/

	// NoGaDA
	dilate(_input, _output, element, Point(-1, -1), 15);
	erode(_output, _output, element, Point(-1, -1), 24);
	dilate(_output, _output, element, Point(-1, -1), 2);
	morphologyEx(_output, _output, MORPH_OPEN, element, Point(-1, -1), 1);
	dilate(_output, _output, element, Point(-1, -1), 1);

	namedWindow("Morph imgae", WINDOW_FREERATIO);
	resizeWindow("Morph imgae", Size(800, 800));
	imshow("Morph imgae", _output); 
}

void Contour_Processing(Mat& _input, vector<vector<Point>>& _contour, vector<Vec4i>& _hierarchy) {

	findContours(_input, _contour, _hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < _contour.size(); i++) {

		int area = contourArea(_contour[i]);

		int len = arcLength(_contour[i], true);
		Rect box = boundingRect(_contour[i]);
		Point org = Point(box.br().x, box.tl().y);
		Point org1 = Point(box.br().x, box.tl().y - 30);

		if (len > 500) {

			count_obj[M6_bolt]++;
			rectangle(src, box, colors[M6_bolt], 2, LINE_AA);
			//drawContours(src, _contour, i, colors[M6_bolt], 2, LINE_8, _hierarchy);
			putText(src, name[M6_bolt], org, FONT_HERSHEY_SIMPLEX, 1, colors[M6_bolt], 2, LINE_AA);

		}
		else if (len > 350 && len < 420) {

			count_obj[M5_bolt]++;
			rectangle(src, box, colors[M5_bolt], 2, LINE_AA);
			//drawContours(src, _contour, i, colors[M5_bolt], 2, LINE_8, _hierarchy);
			putText(src, name[M5_bolt], org, FONT_HERSHEY_SIMPLEX, 1, colors[M5_bolt], 2, LINE_AA);

		}
		else if (len > 220 && len < 250) {

			count_obj[M6_Nut]++;
			rectangle(src, box, colors[M6_Nut], 2, LINE_AA);
			//drawContours(src, _contour, i, colors[M6_Nut], 2, LINE_8, _hierarchy);
			putText(src, name[M6_Nut], org, FONT_HERSHEY_SIMPLEX, 1, colors[M6_Nut], 2, LINE_AA);

		}
		else if (len > 180 && len < 220) {

			count_obj[M5_rect]++;
			rectangle(src, box, colors[M5_rect], 2, LINE_AA);
			//drawContours(src, _contour, i, colors[M5_rect], 2, LINE_8, _hierarchy);
			putText(src, name[M5_rect], org, FONT_HERSHEY_SIMPLEX, 1, colors[M5_rect], 2, LINE_AA);

		}
		else if (len > 150 && len < 180) {

			count_obj[M5_Nut]++;
			rectangle(src, box, colors[M5_Nut], 2, LINE_AA);
			//drawContours(src, _contour, i, colors[M5_Nut], 2, LINE_8, _hierarchy);
			putText(src, name[M5_Nut], org, FONT_HERSHEY_SIMPLEX, 1, colors[M5_rect], 2, LINE_AA);
		}
	}
	namedWindow("Output image", WINDOW_FREERATIO);
	resizeWindow("Output image", Size(800, 800));
	imshow("Output image", src);
}


void equaleHist(Mat& _input, Mat& _output) {

	cv::equalizeHist(_input, _output);

	namedWindow("Output image", WINDOW_FREERATIO);
	resizeWindow("Output image", Size(800, 800));
	imshow("Output image", src);

}



void print_result(void) {

	printf("M6_bolt: %d \n", count_obj[M6_bolt]);
	printf("M5_bolt: %d \n", count_obj[M5_bolt]);
	printf("M6_Nut : %d \n", count_obj[M6_Nut]);
	printf("M5_Nut : %d \n", count_obj[M5_Nut]);
	printf("M5_rect: %d \n\n", count_obj[M5_rect]);

	int total = count_obj[M6_bolt] + count_obj[M5_bolt] + count_obj[M6_Nut] + count_obj[M5_Nut] + count_obj[M5_rect];
	printf("Total : %d \n\n", total);
}





void IMG_processing(void) {

	// Image read
	Img_read();

	// plot histogram
	plotHist(dst_gray, "histogram", 500, 500);

	// filter
	Filter_Process(dst_gray, dst_filt, MEDIAN, kernel);

	// estogram equalization 
	equaleHist(dst_filt, dst_equal);

	// plot histogram
	plotHist(dst_equal, "histogram", 500, 500);

	// threshold
	Threshold_Process(dst_equal, dst_thres, thresh_value);

	// morphlogy
	Morphology_Process(dst_thres, dst_morph);

	// Find contours
	Contour_Processing(dst_morph, contours, hierarchy);
}