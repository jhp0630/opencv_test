/**
@file videocapture_basic.cpp
@brief A very basic sample for using VideoCapture and VideoWriter
@author PkLab.net
@date Aug 24, 2016
*/

/*
Visual Studio 2010 버전 이상부터는 MS의 Concurrency라는 이름의 멀티 쓰레드 기법이 기본으로 적용됩니다.
즉, 굳이 TBB를 깔지 않아도 Concurrency 기법을 통해 병렬 프로그래밍이 동작한다는 의미
*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>


using namespace cv;
using namespace std;
using namespace cv::ml;
using namespace cv::dnn;


//int main(int, char**)
//{
//	Mat frame;
//	//--- INITIALIZE VIDEOCAPTURE
//	VideoCapture cap;
//	// open the default camera using default API
//	cap.open(0);
//	// OR advance usage: select any API backend
//	int deviceID = 0;             // 0 = open default camera
//	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
//								  // open selected camera using selected API
//	cap.open(deviceID + apiID);
//	// check if we succeeded
//	if (!cap.isOpened()) {
//		cerr << "ERROR! Unable to open camera\n";
//		return -1;
//	}
//
//	//--- GRAB AND WRITE LOOP
//	cout << "Start grabbing" << endl
//		<< "Press any key to terminate" << endl;
//	for (;;)
//	{
//		// wait for a new frame from camera and store it into 'frame'
//		cap.read(frame);
//		// check if we succeeded
//		if (frame.empty()) {
//			cerr << "ERROR! blank frame grabbed\n";
//			break;
//		}
//		// show live and wait for a key with timeout long enough to show images
//		
//		//Sobel(frame, frame, frame.depth(), 1, 0);
//
//		imshow("Live", frame);
//		if (waitKey(5) >= 0)
//			break;
//	}
//	// the camera will be deinitialized automatically in VideoCapture destructor
//	return 0;
//}


/*
Mat and image load
*/

//int main(int, char)
//{
//	Mat img = imread("ss.jpg");
//	Mat img2 = img.clone();
//
//	//Sobel(img, img2, img.depth(), 1, 0);
//	bitwise_not(img2, img2);
//
//	Rect r(img.cols / 4, img.rows / 4, img.cols / 4 * 2, img.rows / 4 * 2);
//	cout << r << endl;
//
//	Mat cimg2;
//	img(r).copyTo(cimg2);
//
//	Mat roi(img, r);
//	bitwise_not(roi, roi);
//
//	imshow("img", img);
//	imshow("img2", img2);
//	imshow("cimg2", cimg2);
//	imshow("roi", roi);
//
//
//	waitKey(0);
//	
//	return 0;
//  
//}


/*
pixel access
*/

//int main(int, char)
//{
//	Mat img = imread("ss.jpg");
	

	///* using data */
	/// 
	//for (int i = img.rows / 10 * 7; i < img.rows / 10 * 8; i++) {
	//	for (int j = 0; j < img.cols; j++) {

	//		unsigned char r, g, b;

	//		b = img.data[i * img.step + j * img.elemSize() + 0];
	//		g = img.data[i * img.step + j * img.elemSize() + 1];
	//		r = img.data[i * img.step + j * img.elemSize() + 2];

	//		img.data[i * img.step + j * img.elemSize() + 0] = unsigned char(255 - b);
	//		img.data[i * img.step + j * img.elemSize() + 1] = unsigned char(255 - g);
	//		img.data[i * img.step + j * img.elemSize() + 2] = unsigned char(255 - r);


	//	}
	//}

	///* using at */

	//for (int i = img.rows / 10 * 2; i < img.rows / 10 * 3; i++) {
	//	for (int j = 0; j < img.cols; j++) {

	//		unsigned char r, g, b;

	//		b = img.at< cv::Vec3b>(i, j)[0];
	//		g = img.at< cv::Vec3b>(i, j)[1];
	//		r = img.at< cv::Vec3b>(i, j)[2];

	//		img.at< cv::Vec3b>(i, j)[0] = unsigned char(255 - b);
	//		img.at< cv::Vec3b>(i, j)[1] = unsigned char(255 - g);
	//		img.at< cv::Vec3b>(i, j)[2] = unsigned char(255 - r);


	//	}
	//}

	///* using ptr */

	//for (int i = img.rows / 10 * 2; i < img.rows / 10 * 3; i++) {

	//	cv::Vec3b* ptr = img.ptr< cv::Vec3b >(i);

	//	for (int j = 0; j < img.cols; j++) {

	//		unsigned char r1, g1, b1, r2, g2, b2;

	//		b1 = (ptr[j][0]);
	//		g1 = (ptr[j][1]);
	//		r1 = (ptr[j][2]);

	//		// or

	//		cv::Vec3b bgr = ptr[j];
	//		b2 = (bgr[0]);
	//		g2 = (bgr[1]);
	//		r2 = (bgr[2]);

	//		ptr[j] = cv::Vec3b(255 - b1, 255 - g1, 255 - r1);
	//	}
	//}


	///* using iteration */

	//cv::MatIterator_< cv::Vec3b> itd = img.begin< cv::Vec3b>(), itd_end = img.end< cv::Vec3b>();
	//for (int i = 0; itd != itd_end; ++itd,  ++i) {

	//	cv::Vec3b bgr = (*itd);

	//	(*itd)[0] = 255 - bgr[0];
	//	(*itd)[1] = 255 - bgr[1];
	//	(*itd)[2] = 255 - bgr[2];

	//}
	

//
//	imshow("img", img);
//	waitKey(0);
//	
//	return 0;
//  
//}





/*
DNN
*/

void on_mouse(int event, int x, int y, int flags, void* userdata);

int main()
{
	Net net = readNet("mnist_cnn.pb");

	if (net.empty()) {
		cerr << "Network load failed!" << endl;
		return -1;
	}

	Mat img = Mat::zeros(400, 400, CV_8UC1);

	imshow("img", img);
	setMouseCallback("img", on_mouse, (void*)&img);

	while (true) {
		int c = waitKey();

		if (c == 27) {
			break;
		}
		else if (c == ' ') {
			Mat blob = blobFromImage(img, 1 / 255.f, Size(28, 28));
			net.setInput(blob);
			Mat prob = net.forward();

			double maxVal;
			Point maxLoc;
			minMaxLoc(prob, NULL, &maxVal, NULL, &maxLoc);
			int digit = maxLoc.x;

			cout << digit << " (" << maxVal * 100 << "%)" << endl;

			img.setTo(0);
			imshow("img", img);
		}
	}

	return 0;
}

Point ptPrev(-1, -1);

void on_mouse(int event, int x, int y, int flags, void* userdata)
{
	Mat img = *(Mat*)userdata;

	if (event == EVENT_LBUTTONDOWN) {
		ptPrev = Point(x, y);
	}
	else if (event == EVENT_LBUTTONUP) {
		ptPrev = Point(-1, -1);
	}
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {
		line(img, ptPrev, Point(x, y), Scalar::all(255), 40, LINE_AA, 0);
		ptPrev = Point(x, y);

		imshow("img", img);
	}
}