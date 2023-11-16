#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../KCCImageNet/brake_disk/brake_disk_part_01.png";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	// 이진화
	cv::Mat src_bin, src_open;
	cv::threshold(src_gray, src_bin, 240, 255, ThresholdTypes::THRESH_BINARY);
	//inRange(src_gray, Scalar(240), Scalar(255), src_bin);

	// 형태학적 처리 (노이즈 제거)
	{
		int kernelSz = 2;
		int shape = MorphShapes::MORPH_ELLIPSE;
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
	Mat drawing;
	
	if (src_gray.channels() == 3) { drawing = src_gray.clone(); }
	else { cvtColor(src_gray, drawing, COLOR_GRAY2BGR); }

	for (size_t i = 0; i < contours.size(); i++) //꼭지점 사이즈만큼 i 반복
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, FILLED);
	}

	return 1;
}