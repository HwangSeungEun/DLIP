#include "myFunc.h"

Mat src, srcGray, srcHSV, srcROI, dstBlur, dstThresh, dstMorph, dstHSV, dstConcat;

using namespace cv;
using namespace std;

Point origin;
Rect selection;
bool selectObject = false;
bool trackObject = false;
int hmin = 0, hmax = 179, smin = 0, smax = 255, vmin = 144, vmax = 255;


void main() {

    vector<vector<Point>> contours;

    // TrackBar setting
    namedWindow("Source", 0);
    createTrackbar("Hmin", "Source", &hmin, 179, 0);
    createTrackbar("Hmax", "Source", &hmax, 179, 0);
    createTrackbar("Smin", "Source", &smin, 255, 0);
    createTrackbar("Smax", "Source", &smax, 255, 0);
    createTrackbar("Vmin", "Source", &vmin, 255, 0);
    createTrackbar("Vmax", "Source", &vmax, 255, 0);

    src = imread("test1.png", IMREAD_COLOR);

    int width = 500;
    int height = 500;


    cv::Size size = src.size();

    cvtColor(src, srcHSV, COLOR_BGR2HSV);

    // print HSV image
    printImg("Org", src, width, height);
    printImg("HSV image", srcHSV, width, height);

    while (true) {

        Scalar rangeMin = Scalar(MIN(hmin, hmax), MIN(smin, smax), MIN(vmin, vmax));
        Scalar rangeMax = Scalar(MAX(hmin, hmax), MAX(smin, smax), MAX(vmin, vmax));

        inRange(srcHSV, rangeMin, rangeMax, dstHSV);

        printImg("Source", dstHSV, width, height);

        dilate(dstHSV, dstMorph, Mat::ones(Size(3, 3), CV_8UC1), Point(-1, -1), 2);

        printImg("Dilation", dstMorph, width, height);


        char c = (char)waitKey(10);
        if (c == 27)
            break;

    }

}