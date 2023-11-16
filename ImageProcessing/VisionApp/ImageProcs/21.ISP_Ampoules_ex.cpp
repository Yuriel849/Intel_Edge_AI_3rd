#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../KCCImageNet/images/ampoules/ampoules_01.png";
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_ANYCOLOR);
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	// 이진화
	cv::Mat src_bin, src_open;
	cv::threshold(src_gray, src_bin, 220, 255, ThresholdTypes::THRESH_BINARY);
	//inRange(src_gray, Scalar(240), Scalar(255), src_bin);

	// 형태학적 처리 (노이즈 제거)
	{
		int kernelSz = 10;
		int shape = MorphShapes::MORPH_RECT;
		cv::Size sz = Size(2 * kernelSz + 1, 2 * kernelSz + 1);
		Mat SE = cv::getStructuringElement(shape, sz);

		int type = MorphTypes::MORPH_OPEN;
		cv::morphologyEx(src_bin, src_open, type, SE);
		Mat diff_open = src_bin - src_open;
		int a = 0; // Anchor to set breakpoint
	}

	// contours 잡기

	RNG rng(12345);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(src_open, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	//Mat drawing;

	//if (src_gray.channels() == 3) { drawing = src_gray.clone(); }
	//else { cvtColor(src_gray, drawing, COLOR_GRAY2BGR); }

	cv::Mat src_masked = cv::Mat::zeros(src_gray.size(), CV_8UC1);
	uchar* pMData = src_masked.data;
	for (size_t i = 0; i < contours.size(); i++) //꼭지점 사이즈만큼 i 반복
	{

		//Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		//drawContours(drawing, contours, (int)i, color, FILLED);
		RotatedRect rrt = minAreaRect(contours[i]);
		int max_y = 60, min_y = 230;
		line(src_gray, Point(rrt.center.x+20, 0), Point(rrt.center.x+20, src_gray.rows), CV_RGB(0, 0, 255));
		line(src_gray, Point(rrt.center.x-20, 0), Point(rrt.center.x-20, src_gray.rows), CV_RGB(255, 0, 0));
		line(src_gray, Point(0, max_y), Point(src_gray.cols, max_y), CV_RGB(0, 255, 255));
		line(src_gray, Point(0, min_y), Point(src_gray.cols, min_y), CV_RGB(255, 0, 255));

		uchar* pData = src_gray.data;

		// Calculate index of OpenCV Mat via: (row + x) * cols + (col + y)
		for (size_t ix = 0; ix < src_gray.cols; ix++)
		{
			for (size_t iy = 0; iy < src_gray.rows; iy++)
			{
				int index = iy * src_gray.cols + ix;
				if ((ix < rrt.center.x + 20 || rrt.center.x - 20 < ix) && (iy < max_y || min_y < iy))
				{
					pMData[index] = 0;
				}
				else
				{
					pMData[index] = pData[index];
				}
			}
		}
		int a = 0;
	}

	return 1;
}