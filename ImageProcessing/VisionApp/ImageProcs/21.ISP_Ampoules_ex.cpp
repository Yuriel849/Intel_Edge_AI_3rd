#pragma once

#include "ISP.h"

int main()
{
	int ampoule_max = 95, ampoule_min = 135;

	std::string fileName = "../KCCImageNet/images/ampoules/ampoules_01.png";
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_ANYCOLOR);
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	// 이진화
	cv::Mat src_bin, src_open;
	cv::threshold(src_gray, src_bin, 210, 255, ThresholdTypes::THRESH_BINARY);
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

	cv::Mat src_masked = src_gray.clone();
	uchar* pMData = src_masked.data;
	for (size_t i = 0; i < contours.size(); i++) //꼭지점 사이즈만큼 i 반복
	{
		RotatedRect rrt = minAreaRect(contours[i]);
		int max_y = 60, min_y = 230;

		line(src_gray, Point(rrt.center.x+20, 0), Point(rrt.center.x+20, src_gray.rows), 0);
		line(src_gray, Point(rrt.center.x-20, 0), Point(rrt.center.x-20, src_gray.rows), 0);
		line(src_gray, Point(0, max_y), Point(src_gray.cols, max_y), 0);
		line(src_gray, Point(0, min_y), Point(src_gray.cols, min_y), 0);

		uchar* pData = src_gray.data;

		// Calculate index of OpenCV Mat via: (row + x) * cols + (col + y)
		for (size_t ix = 0; ix < src_gray.cols; ix++)
		{
			for (size_t iy = 0; iy < src_gray.rows; iy++)
			{
				int index = iy * src_gray.cols + ix;
				if ((rrt.center.x - 20 < ix) && (ix < rrt.center.x + 20))
				{
					pMData[index] = 0;
				}
				else if (iy < max_y || min_y < iy)
				{
					pMData[index] = 0;
				}
				else if(pMData[index] != 0)
				{
					pMData[index] = pData[index];
				}
			}
		}
		int a = 0; // Anchor to set breakpoint
	}

	Mat src_eqa = src_masked.clone();
	contours.clear();
	hierarchy.clear();
	findContours(src_masked, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < contours.size()-1; i++)
	{
		RotatedRect rrt = minAreaRect(contours[i]);
		Mat subROIimg = src_masked(rrt.boundingRect());
		if (rrt.size.height >= 34)
		{
			Mat subROIimgEq;
			equalizeHist(subROIimg, subROIimgEq);
			subROIimgEq.copyTo(src_eqa(rrt.boundingRect()));
		}
		int a = 0; // Anchor to set breakpoint
	}

	contours.clear();
	hierarchy.clear();
	findContours(src_eqa, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < contours.size(); i++) //꼭지점 사이즈만큼 i 반복
	{
		RotatedRect rrt = minAreaRect(contours[i]);
		//rectangle(src_eqa, rrt.boundingRect(), 255);
		Point2f pts[4];
		rrt.points(pts);
		int rrt_x = pts[1].x, rrt_y = pts[1].y;

		uchar* pData = src_eqa.data;

		int flag = 0;
		for (size_t w = rrt_x; w < rrt.size.width + rrt_x; w++)
		{
			for (size_t h = rrt_y; h < rrt.size.height + rrt_y; h++)
			{
				// Calculate index of OpenCV Mat via: (row + x) * cols + (col + y)
				int index = h * rrt.size.width + w;
				if (pData[index] > 140)
				{
					flag = 1;
					line(src_gray, Point(rrt_x, h), Point(rrt_x + rrt.size.width, h), 255);
					int a = 0;
					break;
				}
			}
			if (flag == 1) { break; }
		}
	}

	return 1;
}