#include <stdio.h>
#include <iostream>


#include <opencv2/opencv.hpp>
#include <stdlib.h>


using namespace std;
using namespace cv;



int main()
{

    namedWindow("Original", WINDOW_FREERATIO);
    namedWindow("test", WINDOW_FREERATIO);

    namedWindow("Result", WINDOW_FREERATIO);

    CascadeClassifier face_classifier;
    face_classifier.load("C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml");
   // face_classifier.load("C:/opencv-3.4.13/sources/data/haarcascades/haarcascade_frontalface_alt2.xml");

    Mat frame, grayframe;
    frame = imread("C:/Users/erich/source/repos/DLIP/Image/face1.jpg");

    cvtColor(frame, grayframe, COLOR_BGR2GRAY);
    equalizeHist(grayframe, grayframe);


    imshow("test", grayframe);
    vector<Rect> faces;


    face_classifier.detectMultiScale(grayframe, faces,
        
        // 얼마나 더 확대해서 쪼갤꺼냐 한번에 많은 영역을 본다
        1.1, // increase search scale by 10% each pass. 작아지면 더 오진 감소.

        // 주변의 있는 것을 같이 봐서 숫자가 높아지면 깐깐해짐
        3  // merge groups of three detections. 올라가면 더 오진 감소

    );


    Mat img_mosaic;
    Mat frame_original;
    frame.copyTo(frame_original);

    for (int i = 0; i < faces.size(); i++) {

        Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
        Point tr(faces[i].x, faces[i].y);

        // lb tr
        img_mosaic = frame(Rect(lb, tr));
        Mat img_temp;

        resize(img_mosaic, img_temp, Size(img_mosaic.rows / 8, img_mosaic.cols / 8));
        resize(img_temp, img_mosaic, Size(img_mosaic.rows, img_mosaic.cols));

        rectangle(frame, lb, tr, Scalar(255, 0, 0), 3, 4, 0);
        rectangle(frame_original, lb, tr, Scalar(255, 0, 0), 3, 4, 0);

    }

    imshow("Result", frame);
    imshow("Original", frame_original);


    waitKey(0);

    return 0;
}