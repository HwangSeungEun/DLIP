//#include <opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
////* @function main
//int main()
//{
//Mat src;
//
//src = imread("testImage.jpg", 1);/// Load an image
//
//if (src.empty())/// Load image check
//{
//cout << "File Read Failed : src is empty" << endl;
//waitKey(0);
//}
//
///// Create a window to display results
//namedWindow("DemoWIndow", WINDOW_AUTOSIZE); //CV_WINDOW_AUTOSIZE(1) :Fixed Window, 0: Unfixed window
//
//if (!src.empty())imshow("DemoWIndow", src); // Show image
//
//waitKey(0);//Pause the program
//return 0;
//}


//#include "opencv.hpp"
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main(int argc, char* argv[])
//{
//    VideoCapture cap(0); // open the video camera no. 0
//
//    if (!cap.isOpened())  // if not success, exit program
//    {
//        cout << "Cannot open the video cam" << endl;
//        return -1;
//    }
//    namedWindow("MyVideo", WINDOW_AUTOSIZE); //create a window called "MyVideo"
//
//    while (1)
//    {
//        Mat frame;
//        bool bSuccess = cap.read(frame); // read a new frame from video
//        if (!bSuccess) //if not success, break loop
//        {
//            cout << "Cannot read a frame from video stream" << endl;
//            break;
//        }
//        imshow("MyVideo", frame); //show the frame in "MyVideo" window
//
//        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
//        {
//            cout << "esc key is pressed by user" << endl;
//            break;
//        }
//    }
//    return 0;
//}