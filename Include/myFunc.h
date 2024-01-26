#pragma once
#include <iostream>
#include <opencv.hpp>
#include <vector>

// filter type
#define		NONE		0
#define		BLUR		1
#define		GAUSSIAN	2
#define		MEDIAN		3
#define		LAPLASIAN	4

// morph type
#define		NONE		0		  
#define		ERODE		1
#define		DILATE		2
#define		CLOSE		3 
#define		OPEN		4 

		

using namespace cv;
using namespace std;

void plotHist(Mat src, string plotname, int width, int height);



















