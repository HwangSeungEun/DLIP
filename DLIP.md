# Deep Learning Image Processing

[TOC]



##  Digital Image Filtering

-  Spatial filtering and frequency filtering

image processing 에서는 Spatial filter를 주로 사용함



### 1. CNN

#### 1.1. Convolution

**convolution**: 사전적 정의는 합성곱

<img src="https://user-images.githubusercontent.com/91474647/225024197-2a1d3d7f-13f3-43d3-8609-900fd5fb2fb8.png" alt="image" style="zoom:67%;" />

노란색 kernel filter를 이동시키면서 분홍색 image를 채우게 된다.

윈도우는 홀수로 이루어 져있고 symmetric하다.



#### 1.2. 2D Convolution of Filter Window

<img src="https://user-images.githubusercontent.com/91474647/225025692-e0b784ea-6487-4a93-8e64-e6039c1d4a39.png" alt="image" style="zoom:50%;" />

**w(s,t): window**

**f(x,y): source image**

**g(x,y): result image**

<img src="https://user-images.githubusercontent.com/91474647/225026183-4670f4df-da2a-44bd-ac3a-44948ad7e175.png" alt="image" style="zoom:50%;" />

**normalize with filter**

<img src="https://user-images.githubusercontent.com/91474647/225027164-fdb3bbab-3845-4140-8c77-95d38b70a854.png" alt="image" style="zoom:50%;" />

<img src="https://user-images.githubusercontent.com/91474647/225027348-197781ee-64fa-4f8c-a7db-f59c5f326f4c.png" alt="image" style="zoom:80%;" />



#### 1.3. Padding

padding이 없이 convolution을 진행하면 이미지의 사이즈가 줄어들게 된다.



**No padding**

Image: WxH → WxH

Output: WxH → (W-m+1)x(H-n+1)

<img src="https://user-images.githubusercontent.com/91474647/225032605-ab37b177-ad94-4e75-a82a-39d901999038.png" alt="image" style="zoom:50%;" />

**Use padding**

Image: WxH → (W+m-1)x(H+n-1)

Output: WxH → WxH

<img src="https://user-images.githubusercontent.com/91474647/225032761-00b89c0b-116e-4d35-80c0-3b71c8a2638e.png" alt="image" style="zoom:45%;" />



만약 input과 output의 사이즈를 동일하게 할 때 kernel의 사이즈에 따라서 padding의 사이즈도 바뀌어야 한다.



<img src="https://user-images.githubusercontent.com/91474647/225029205-8aa83f1c-aaf9-4ce7-99dd-ba8f6023cce1.png" alt="image" style="zoom: 50%;" />

**source: **5x5x1

**kernel:** 3x3x1

**output:** 5x5x1





### 2. Filters

#### 2.1. Smoothing Filter

##### 2.1.1. box filter (Blur)

 average of the pixels in the neighborhood of the filter mask.

<img src="https://user-images.githubusercontent.com/91474647/225030502-6862c96e-7345-4752-8468-71df017da3b6.png" alt="image" style="zoom: 40%;" />

<img src="https://user-images.githubusercontent.com/91474647/225030671-a06f4969-e958-4a26-8ee2-dd6301f09538.png" alt="image" style="zoom:50%;" />

3x3 box filter

##### 2.1.2. Gaussian Spatial Filter

![image](https://user-images.githubusercontent.com/91474647/225031071-ec4d920d-6233-44a5-ad82-e3dd3f09f343.png)

<img src="https://user-images.githubusercontent.com/91474647/225031221-e70d6417-be67-4cae-83c7-8f82ac828ae8.png" alt="image" style="zoom:70%;" />



filter의 값이 가우스 함수의 형태를 띔

<img src="https://user-images.githubusercontent.com/91474647/225031581-9f968ffd-8098-4700-9ec1-e373189c0c0a.png" alt="image" style="zoom:50%;" />



이 외에도 

- **Median filter**
- **Max/min filter**
- **Geometric mean filter**
- **Harmonic mean filter**

등이 있다



#### 2.2 Sharpening Filters

- Highlight transitions in intensity, such as edges intensity가 변하는 곳을 찾는다
- Usually based on 1st, 2nd differentiation, 주로 1,2차 편미분
- Used to highlight letters, shapes, texture, and boundaries 글씨나 모양을 찾는데 주로 사용한다
- Opposite to smoothing filter, and can amplify noises 노이즈를 증폭시킬 수도 있다

<img src="https://user-images.githubusercontent.com/91474647/225220161-40a6a414-a1b3-4aa6-988b-73020e50fd42.png" alt="image" style="zoom:70%;" />



**1st derivative (velocity)** Nonzero at step, ramp edge Nonzero along for ramp edge

- ‘0’ for constant intensity 
- Nonzero along for ramp edge  
- Nonzero at step, ramp edge

<img src="https://user-images.githubusercontent.com/91474647/225218211-cfa97207-9068-4f76-bc3f-72c0a6185715.png" alt="image" style="zoom:60%;" />

**Roberts**

![image](https://user-images.githubusercontent.com/91474647/225222487-7073658d-553b-4a5e-a073-f0863eab75c8.png)

**Prewitt**

<img src="https://user-images.githubusercontent.com/91474647/225222683-2e4b4fe6-f4b3-418e-8f3e-2319a8254aef.png" alt="image" style="zoom:50%;" />

**Sobel**

<img src="https://user-images.githubusercontent.com/91474647/225222791-3da777aa-bd86-461e-8d45-957f6d584301.png" alt="image" style="zoom:50%;" />









 **2nd derivative (acceleration)** derivative Nonzero at start and end point of step, ramp edge

- ‘0’ for constant intensity 
- ‘0’ along ramps of constant slope 
- Nonzero at start and end point of step, ramp edge

<img src="https://user-images.githubusercontent.com/91474647/225218360-17ac0cbe-feb8-467f-a757-a5b5bc94722e.png" alt="image" style="zoom:67%;" />

 **Laplacian : 2nd derivative, linear isotropic operator**

<img src="https://user-images.githubusercontent.com/91474647/225223954-c595c73c-5503-46e0-8adb-ac73bc067d44.png" alt="image" style="zoom:67%;" />

<img src="https://user-images.githubusercontent.com/91474647/225224007-2da282d9-eec1-4e90-b9af-fbe5c59abdd6.png" alt="image" style="zoom: 60%;" />

<img src="https://user-images.githubusercontent.com/91474647/225224129-09a617af-7234-4ee8-8ac5-3afba7b61cb5.png" alt="image" style="zoom:67%;" />

<img src="https://user-images.githubusercontent.com/91474647/225224672-bc58db38-b75e-4dca-813c-83ba9b8b06ad.png" alt="image" style="zoom:90%;" />

<img src="https://user-images.githubusercontent.com/91474647/225224305-61b4ee37-37e8-4568-9547-1dfc00cf36f8.png" alt="image" style="zoom:67%;" />



**Edges of a lane**

![image](https://user-images.githubusercontent.com/91474647/225220973-39f9b0d2-dfd1-41af-8f39-8fdd97d35af3.png)

<img src="https://user-images.githubusercontent.com/91474647/225221095-0a45fa2e-7430-43ed-b34e-22df47bd0af1.png" alt="image" style="zoom: 80%;" />

<img src="https://user-images.githubusercontent.com/91474647/225221197-5f4b412b-43bd-41b6-b6ef-b54586d48464.png" alt="image" style="zoom:80%;" />





#### 2.3. example code



```c++
// DLIP_Tutorial_Filter_filter_demo_student.cpp

#include <opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void main()
{
	cv::Mat src, dst;
	src = cv::imread("../../../Image/blurry_moon.tif", 0);

	int i = 3;
	Size kernelSize = cv::Size(i, i);

	/* Blur */
	cv::blur(src, dst, cv::Size(i, i), cv::Point(-1, -1));
	namedWindow("Blur", WINDOW_AUTOSIZE);
	imshow("Blur", dst);

	/*filter2D*/
	cv::filter2D(src, dst, CV_8U, 5, cv::Point(-1, -1));
	namedWindow("filter2D", WINDOW_AUTOSIZE);
	imshow("filter2D", dst);

	/* Gaussian Filter */
	cv::GaussianBlur(src, dst, cv::Size(i, i), 0);
	namedWindow("Gaussian", WINDOW_AUTOSIZE);
	imshow("Gaussian", dst);

	/* Median Filter */
	cv::medianBlur(src, dst, 7); // kernal size는 1이 아닌 홀수
	namedWindow("Median", WINDOW_AUTOSIZE);
	imshow("Median", dst);

	int i = 3;
	cv::bilateralFilter(src, dst, i, i * 2, i / 2);
	namedWindow("bilateralFilter", WINDOW_AUTOSIZE);
	cv::imshow("bilateralFilter", dst);

	/* Laplacian Filter */
	int kernel_size = 3;
	int scale		= 1;
	int delta		= 0;
	int ddepth		= CV_16S;

	cv::Laplacian(src, dst, ddepth, kernel_size, scale, delta, cv::BORDER_DEFAULT);
	src.convertTo(src, CV_16S);
	cv::Mat result_laplcaian = src - dst;
	result_laplcaian.convertTo(result_laplcaian, CV_8U);
	namedWindow("Laplacian", WINDOW_AUTOSIZE);
	cv::imshow("Laplacian", result_laplcaian);


	cv::waitKey(0);
}
```



```c++
// DLIP_Tutorial_Filter_filter_demo_webcam_student.cpp

#include <opencv2/opencv.hpp>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

#define		NONE		0
#define		BLUR		1
#define		GAUSSIAN	2
#define		LAPLASIAN	3

#define		UP			72
#define		DOWN		80

using namespace std;
using namespace cv;

int main()
{
	/*  open the video camera no.0  */
	VideoCapture cap(0);

	if (!cap.isOpened())	// if not success, exit the programm
	{
		cout << "Cannot open the video cam\n";
		return -1;
	}

	namedWindow("MyVideo", WINDOW_AUTOSIZE);

	int key = 0;
	int kernel_size = 7;
	int filter_type = 0;
	int arrow = 0;

	String text = "MODE: NONE"; // 넣을 글씨
	Point org(50, 100); // 글씨의 시작 위치
	int fontFace = FONT_HERSHEY_SIMPLEX; // 글씨의 폰트
	double fontScale = 1; // 글씨의 크기 비율
	Scalar color(255, 255, 255); // 글씨의 색상 (빨간색)
	int thickness = 3; // 글씨의 굵기
	int lineType = LINE_AA; // 글씨의 선 타입

	while (1)
	{
		Mat src, dst;

		/*  read a new frame from video  */
		bool bSuccess = cap.read(src);

		if (!bSuccess)	// if not success, break loop
		{
			cout << "Cannot find a frame from  video stream\n";
			break;
		}
		key = waitKeyEx(30);

		if (key == 27) // wait for 'ESC' press for 30ms. If 'ESC' is pressed, break loop
		{
			cout << "ESC key is pressed by user\n";
			break;
		}
		else if (key == 'n' || key == 'N') {

			filter_type = NONE;	// blur
			cout << "NONE" << endl;
		}

		else if (key == 'b' || key == 'B')
		{
			filter_type = BLUR;
			cout << "BLUR" << endl;
		}
		else if (key == 'g' || key == 'G') {

			filter_type = GAUSSIAN;
			cout << "GAUSSIAN" << endl;
		}
		else if (key == 'l' || key == 'L') {

			filter_type = LAPLASIAN;
			cout << "LAPLASIAN" << endl;
		}
	
		else if (key == 0x260000) {

			cout << "Up" << endl;
			kernel_size += 2;

		}
		else if (key == 0x280000) {

			cout << "DOWN" << endl;
			kernel_size -= 2;
			if (kernel_size < 1) {
				kernel_size = 1;
			}
		}

		if (filter_type == NONE){
				
			dst = src;
			text = "MODE: NONE";
		}
		else if (filter_type == BLUR) {

			blur(src, dst, cv::Size(kernel_size, kernel_size), cv::Point(-1, -1));
			text = "MODE: BLUR";

		}
		else if (filter_type == GAUSSIAN) {

			cv::GaussianBlur(src, dst, cv::Size(kernel_size, kernel_size), 0);
			text = "MODE: GAUSSIAN";

		}
			
		else if (filter_type == LAPLASIAN){
		
			cv::Laplacian(src, dst, CV_16S, kernel_size, 1, 0, cv::BORDER_DEFAULT);
			src.convertTo(src, CV_16S);
			cv::Mat result_laplcaian = src - dst;
			text = "MODE: LAPLASIAN";

		}
		putText(dst, text, org, fontFace, fontScale, color, thickness, lineType); // 영상에 글씨 넣기
		imshow("MyVideo", dst);
	}
	return 0;
}
```



### 3. Intensity Transformation

A simple transform operation: T(r)
$$
s(i,j) = T(r(i,j))
$$
Changes the intensity of individual pixels, from level r (input) to s (output)
$$
r = input pixel intensity \\

s = output pixel intensity
$$
<img src="https://user-images.githubusercontent.com/91474647/225228016-9a6bcec1-03f0-4c4a-aa53-c1f9ede4af11.png" alt="image" style="zoom: 120%;" />



![image](https://user-images.githubusercontent.com/91474647/225229044-aae9dc69-af75-43bd-859d-791235d8f0f6.png)

































