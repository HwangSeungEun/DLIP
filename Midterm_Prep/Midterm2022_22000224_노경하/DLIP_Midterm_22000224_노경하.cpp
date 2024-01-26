/*

	DLIP MIDTERM 2022  Submission


	NAME:노경하

*/


#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
int element_shape = MORPH_RECT;		// MORPH_RECT, MORPH_ELIPSE, MORPH_CROSS
int n = 3;
Mat element = getStructuringElement(element_shape, Size(n, n));
Mat src, hsv, dstSegment,Bimage, tempIMG, img_disp, rect_src,rect_segment;
int H, S, V = 0;
int faceCount = 0;
String text1 = "Number of faces=";
 
void selectMorph();

int main()
{
	
	src = imread("groupimage_crop.jpg");
	namedWindow("src", 1);
	imshow("src", src);
	Mat drawing(src.size(), CV_8UC3, Scalar(0, 0, 0));
	Mat face(src.size(), CV_8UC3, Scalar(0, 0, 0));
	vector<vector<Point> > contours;

	

	/******** Segmatation of Facial Area  ********/
	//  Segmentatation result is in B/W image, with white for facial area
	//
	// dstSegment=_____________
	cvtColor(src, hsv, CV_BGR2HSV);
	inRange(hsv, Scalar(0, 30, 60), Scalar(20,150,255), dstSegment);
	
	src.copyTo(img_disp);
	src.copyTo(rect_src);
	src.copyTo(Bimage);

	erode(dstSegment, dstSegment, element, Point(-1, -1), 14, BORDER_DEFAULT);
	dilate(dstSegment, dstSegment, element, Point(-1, -1), 16, BORDER_DEFAULT);
	imshow("Segmented image", dstSegment);
	dstSegment.copyTo(rect_segment);

	double maxArea = 0;
	int maxArea_idx = 0;
	int contourA = 0;
	int face_idx = 0;
	findContours(dstSegment, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
	

	if (contours.size() > 0)
	{
		
		for (int i = 0; i < contours.size(); i++)
			if (contourArea(contours[i]) > maxArea) {
				maxArea = contourArea(contours[i]);
				maxArea_idx = i;
			}
		for (int i = 0; i < contours.size(); i++)
			if (contourArea(contours[i]) < maxArea && contourArea(contours[i]) > maxArea-7000) {
				
				face_idx = i;
				drawContours(drawing, contours, -1, cv::Scalar(255, 255, 255), 2, FILLED);
				contourA = contourArea(contours[face_idx]);


				/******** Draw Rectangles around Faces  ********/
	           // Show Tight Fit Rectangle on both  source image(src) and on (dstSegment)
				Rect boxPoint = boundingRect(contours[face_idx]);// 가장 큰 contour를 둘러싸는 사각형 그려줌
				rectangle(img_disp, boxPoint, Scalar(255, 0, 255), 3);
				rectangle(rect_src, boxPoint, Scalar(255, 0, 255), 3);
				rectangle(rect_segment, boxPoint, Scalar(255, 0, 255), 3);

				
				/******** Blur Faces  ********/
				// Show Blurred faces on  source image(src) 
				Mat roi_RGB(img_disp, boxPoint);
				GaussianBlur(roi_RGB, roi_RGB, Size(21,21), 0, 0);
				faceCount++;
			}


		/******** Count Number of Faces  ********/
        //  Print the text on source image
		text1 += to_string(faceCount);
		putText(img_disp, text1, Point(100, 100), FONT_HERSHEY_TRIPLEX, 1, Scalar(255), 1, LINE_4, false);
		putText(Bimage, text1, Point(100, 100), FONT_HERSHEY_TRIPLEX, 1, Scalar(255), 1, LINE_4, false);
		
	}
	imshow("image (b)", Bimage);
	imshow("Rectangle_src", rect_src);
	imshow("Rectangle_segmented", rect_segment);
	imshow("Final Image", img_disp);
	
	
	waitKey(0);
	return 0;
}

void selectMorph()//Morphology test
{
	int erod = 0;
	int dila = 0;

	while (1)
	{

		int key = waitKey(30);
		if (key == 'e')
		{
			erode(dstSegment, dstSegment, element, Point(-1, -1), 1, BORDER_DEFAULT);
			imshow("morph", dstSegment);
			
			erod++;
		}
		else if (key == 'd')
		{
			dilate(dstSegment, dstSegment, element, Point(-1, -1), 1, BORDER_DEFAULT);
			imshow("morph", dstSegment);
			
			dila++;
		}
		else if (key == 'o')
		{
			morphologyEx(dstSegment, dstSegment, MORPH_GRADIENT, element, Point(-1, -1), 1);
			imshow("morph", dstSegment);
			
		}

		else if (key == 'p')
		{
			morphologyEx(dstSegment, dstSegment, CV_MOP_CLOSE, element, Point(-1, -1), 5);
			
		}

		else if (key == 13) // wait for 'ESC' press for 30ms. If 'ESC' is pressed, break loop
		{
			cout << "enter key is pressed by user\n";
			break;
		}

	}


}

