#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv/cxcore.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;

int erodeSize = 3;
int dilateSize = 6;

void DetectContour(Mat img) {
	Mat drawing = Mat::zeros(img.size(), CV_8UC3);
	vector<vector<Point> > contours;
	//vector<vector<Point> > bigContours;
	vector<Vec4i> hierarchy;
	cv::findContours(img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE), cv::Point(0, 0);
	for (int i = 0; i < contours.size(); i++) {
		if (contourArea(contours[i]) >= 500) {
			std::vector<std::vector<cv::Point> > tcontours;
			std::vector<std::vector<cv::Point> > hulls(1);
			std::vector<std::vector<int> > hullsI(1);
			tcontours.push_back(contours[i]);
			cv::drawContours(drawing, tcontours, -1, cv::Scalar(0, 0, 255), 2);
			cv::convexHull(cv::Mat(tcontours[0]), hulls[0], false, true);
			cv::convexHull(cv::Mat(tcontours[0]), hullsI[0], false, true);
			cv::drawContours(drawing, hulls, -1, cv::Scalar(0, 255, 0), 1);
			cv::RotatedRect rect = cv::minAreaRect(cv::Mat(tcontours[0]));
			std::vector<std::vector<cv::Vec4i>>convDef(contours.size());
			cv::convexityDefects(tcontours[0], hullsI[0], convDef[i]);
			for (int k = 0; k < hullsI[0].size(); k++) {
				for (int j = 0; j < convDef[i].size(); j++) {
					if (convDef[i][j][3] > 20 * 256) //filter defects by depth 
					{
						int ind_0 = convDef[i][j][0];//start point
						int ind_1 = convDef[i][j][1];//end point
						int ind_2 = convDef[i][j][2];//defect point
					//	cv::circle(drawing, contours[i][ind_0], 5, cv::Scalar(0, 0, 255), -1);
					//	cv::circle(drawing, contours[i][ind_1], 5, cv::Scalar(255, 0, 0), -1);
					//	cv::circle(drawing, contours[i][ind_2], 5, cv::Scalar(0, 255, 0), -1);
					//	cv::line(drawing, contours[i][ind_2], contours[i][ind_0], cv::Scalar(0, 255, 255), 1);
					//	cv::line(drawing, contours[i][ind_2], contours[i][ind_1], cv::Scalar(0, 255, 255), 1);
					}
				}
			}
		}
	}
	imshow("Hull demo", drawing);
}

/*
void DetectContour(Mat img) {
	Mat drawing = Mat::zeros(img.size(), CV_8UC3);
	vector<vector<Point> > contours;
	vector<vector<Point> > bigContours;
	vector<Vec4i> hierarchy;
	findContours(img, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE, Point());
	if (contours.size() > 0) {
		vector<vector<int> >hull(contours.size());
		vector<vector<Vec4i> > convDef(contours.size());
		vector<vector<Point> > hull_points(contours.size());
		vector<vector<Point> > defect_points(contours.size());
		for (int i = 0; i < contours.size(); i++) {
			if (contourArea(contours[i]) > 5000) {
				convexHull(contours[i], hull[i], false);
				convexityDefects(contours[i], hull[i], convDef[i]);
				for (int k = 0; k < hull[i].size(); k++) {
					int ind = hull[i][k];
					hull_points[i].push_back(contours[i][ind]);
				}
				for (int k = 0; k<convDef[i].size(); k++) {
					if (convDef[i][k][3] > 20 * 256) { // filter defects by depth
						int ind_0 = convDef[i][k][0];
						int ind_1 = convDef[i][k][1];
						int ind_2 = convDef[i][k][2];
						defect_points[i].push_back(contours[i][ind_2]);
						circle(drawing, contours[i][ind_0], 5, Scalar(0, 255, 0), -1);
						circle(drawing, contours[i][ind_1], 5, Scalar(0, 255, 0), -1);
						circle(drawing, contours[i][ind_2], 5, Scalar(0, 0, 255), -1);
						line(drawing, contours[i][ind_2], contours[i][ind_0], Scalar(0, 0, 255), 1);
						line(drawing, contours[i][ind_2], contours[i][ind_1], Scalar(0, 0, 255), 1);
					}
				}
				drawContours(drawing, contours, i, Scalar(0, 255, 0), 1, 8, vector<Vec4i>(), 0, Point());
				drawContours(drawing, hull_points, i, Scalar(255, 0, 0), 1, 8, vector<Vec4i>(), 0, Point());
			}
		}
	}
	imshow("Hull demo", drawing);
}
*/
void morphOps(Mat &thresh) {

	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle
	try {
		Mat erodeElement = getStructuringElement(MORPH_RECT, Size(erodeSize, erodeSize));

		erode(thresh, thresh, erodeElement);
	//	erode(thresh, thresh, erodeElement);
	}
	catch (Exception $e) {
		system("cls");
		cout << "Exeption in eroding was catched! \n\n\n\n\n\n\n\n\n";
	}
	//dilate with larger element so make sure object is nicely visible
	try {
		Mat dilateElement = getStructuringElement(MORPH_RECT, Size(dilateSize, dilateSize));

		dilate(thresh, thresh, dilateElement);
		//dilate(thresh, thresh, dilateElement);

	}
	catch (Exception $e) {
		system("cls");
		cout << "Exeption in dilating was catched! \n\n\n\n\n\n\n\n\n";
	}

}

int main(void) {
	int lh = 0;
	int hh = 15;
	int ls = 61;
	int hs = 218;
	int lv = 0;
	int hv = 100;
	namedWindow("HSV", CV_WINDOW_NORMAL);
	createTrackbar("LH", "HSV", &lh, 179);
	createTrackbar("HH", "HSV", &hh, 179);
	createTrackbar("LS", "HSV", &ls, 255);
	createTrackbar("HS", "HSV", &hs, 255);
	createTrackbar("LV", "HSV", &lv, 255);
	createTrackbar("HV", "HSV", &hv, 255);
	createTrackbar("erodeSize", "HSV", &erodeSize, 20);
	createTrackbar("dilateSize", "HSV", &dilateSize, 20);
	Mat img;
	VideoCapture cap(0);
	int th = 100;
	while (cap.read(img)) {
		Mat frame;
		cvtColor(img, frame, CV_BGR2HSV);
		inRange(frame, Scalar(lh, ls, lv), Scalar(hh, hs, hv), frame);
		threshold(frame, frame, th, 2 * th + 55, THRESH_OTSU);
		imshow("threshold_no_morphops", frame);
		morphOps(frame);
		imshow("threshold", frame);
		DetectContour(frame);
		if (waitKey(5) == 27)
			break;
	}
	return 0;
}