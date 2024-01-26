#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;

// Declare the output variables
Mat dst, cdst, cdstP;
Mat src, src_gray, gray, dst_equ, dst_gau, dst_med;
Mat detected_edges;

int edgeThresh = 1;
int lowThreshold = 70;
int const max_lowThreshold = 255;
int kernel_size = 3;
const char* window_name = "canny";

int threshold_line = 88;
int thresholdMax	= 200;

int minLineLength = 73;
int minLineLengthMax = 300;

int maxLineGap = 58;
int maxLineGapMax = 300;




vector<Vec4i> linesP;

const char* window_name1 = "line";

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
	imshow(window_name, dst);
}



void HoughLinesPThreshild(int, void*) {
	Mat srcCopy = src.clone();

	HoughLinesP(detected_edges, linesP, 1, CV_PI / 180, threshold_line, minLineLength, maxLineGap);

	// Draw the lines
	for (size_t i = 0; i < linesP.size(); i++) {
		Vec4i l = linesP[i];
		line(srcCopy, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}

	// ... (rest of the function)

	imshow("Detected Lines (in red) - Probabilistic Line Transform", srcCopy);
}

int main(int argc, char** argv)
{


	// Loads an image
	const char* filename = "track_gray.JPG";
	src = imread(filename, 1);

	/// Create a matrix of the same type and size as src (for dst)
	dst.create(src.size(), src.type());

	/// Convert the image to grayscale
	cvtColor(src, gray, COLOR_BGR2GRAY);

	// Check if image is loaded fine
	if (src.empty()) {
		printf(" Error opening image\n");
		return -1;
	}


	/* smooth it, otherwise a lot of false circles may be detected */
	//GaussianBlur(gray, dst_gau, Size(9, 9), 2, 2);
	medianBlur(gray, dst_med, 9);
	equalizeHist(dst_med, dst_equ);


	namedWindow(window_name, WINDOW_AUTOSIZE);
	/// Create a Trackbar for user to enter threshold
	createTrackbar("canny:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

	/// Show the image
	CannyThreshold(0, 0);



	namedWindow(window_name1, WINDOW_AUTOSIZE);
	createTrackbar("Threshold", window_name1, &threshold_line, thresholdMax, HoughLinesPThreshild);
	createTrackbar("Min Line Length", window_name1, &minLineLength, minLineLengthMax, HoughLinesPThreshild);
	createTrackbar("Max Line Gap", window_name1, &maxLineGap, maxLineGapMax, HoughLinesPThreshild);

	HoughLinesPThreshild(0, 0);



	// Wait and Exit
	waitKey();
	return 0;
}