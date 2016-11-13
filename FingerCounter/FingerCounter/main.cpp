#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include<iostream>

#include "helpfile.hpp"

using namespace std;
using namespace cv;

int DW = 256, DH = 192, gaussS = 3;

void morphOps(Mat &thresh) {

	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle

	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(1, 1));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(3, 3));

	erode(thresh, thresh, erodeElement);
	erode(thresh, thresh, erodeElement);


	dilate(thresh, thresh, dilateElement);
	dilate(thresh, thresh, dilateElement);

}

/*void handShapeDetection(Mat original)
{
	Mat binary;
	inRange(original, Scalar(0, 0, 48), Scalar(178, 110, 81), binary);	
	morphOps(binary);
	imshow("binary", binary);
	Mat thresh;
	original.copyTo(thresh);
	subtract(thresh, binary, thresh);
	threshold()

	vector<vector<Point>> contours;
	findContours(thresh, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	drawContours(thresh, contours, 5, Scalar(0, 155, 255), 2);
	imshow("thresh", thresh);
}*/

int main(int argc, char** argv)
{

	Mat src, gray, original;

	CascadeClassifier cascadeHand;
	assert(cascadeHand.load("D:\\VS_projects\\FingerCounter\\x64\\Debug\\cascade_13_stages.xml"));
	
	namedWindow("trackbars");

	createTrackbar("DW=", "trackbars", &DW, 640);
//	createTrackbar("DH=", "trackbars", &DH, 480);
	createTrackbar("gaussS=", "trackbars", &gaussS, 200);

	vector<cv::Rect> hands;
	namedWindow("Результат");
	namedWindow("hand_detected");
	if (argc > 1) // принять адрес картинки через командную строку
	{
		src = imread(argv[1]);
		//cout << "something";
		if (src.empty())assert(-1 || "image was not loaded");
		//resize(src, src, Size(150, 100));
		cvtColor(src, gray, CV_BGR2GRAY);
		cascadeHand.detectMultiScale(gray, hands);

		for (Rect i : hands)
		{			
			float k = 640 / DW;
			i.width *= k;
			i.height *= k;
			i.x *= k;
			i.y *= k;
			rectangle(src, i, Scalar(0, 0, 255), 3);

			cout << "hand detected in " << i << endl;
		}

		imshow("Результат", src);
		waitKey(0);
	}
	else
	{	
		setMouseCallback("Результат", onMouse);
		VideoCapture cam;
		assert(cam.open("D:\\Windows\\Images\\Camera Roll\\video.mp4"));

		for (;;)
		{
			cam >> src;
			if (src.empty()) 
			{
				cam.open("D:\\Windows\\Images\\Camera Roll\\video.mp4");
				cam >> src;
			}
			/*
			Gdiplus::takescreenshot();
			src = imread("D:\\VS_projects\\FingerCounter\\x64\\Debug\\screen.png");
			resize(src, src, Size(1920, 1080));
			*/
			flip(src, src, 1);
			src.copyTo(original);

			cvtColor(src, gray, CV_BGR2GRAY);
			
			resize(gray, gray, Size(DW, (float)DW*((float)src.rows / (float)src.cols)));
			
			GaussianBlur(gray, gray, Size(2*gaussS+1, 2*gaussS+1), 2);			
			
			cascadeHand.detectMultiScale(gray, hands);

			for (Rect i : hands)
			{
				//rectangle(src, i, Scalar(0, 0, 255), 3);
				//
				//rectangle(src, Rect((int)(i.x*(DW/640)), (int)(i.y*(DW/640)), (int)(i.width*(DW/640)), (int)(i.height*(DW/640))), Scalar(0, 0, 255), 3);
				imshow("hand_detected_gray", gray(i));
				rectangle(gray, i, Scalar(0, 0, 255), 3);
				float k = (float)640/DW;
				i.width *= k;
				i.height *= k;
				i.x *= k;
				i.y *= k;
				rectangle(src, i, Scalar(0, 0, 255), 3);
				
				imshow("hand_detected", original(i));
				cout << "hand detected in " << i << endl;

				//handShapeDetection(original(i));

			}

			////mouse interaction
			if (state == 2)
			{
				rectangle(src, Point(mouserectx, mouserecty), Point(mouserectx + rectw, mouserecty + recth), Scalar(255, 255, 0), 5);
				circle(src, Point(mouserectx, mouserecty), 5, Scalar(0, 0, 255), 5);
				circle(src, Point(mouserectx + rectw, mouserecty + recth), 5, Scalar(0, 255, 0), 5);
			}			
			imshow("Что видит классификатор", gray);
			imshow("Результат", src);
			if (waitKey(1) == 27)break; /// выход с escape
		}


	}
	cout << "Closing.";
	return(0);
}
