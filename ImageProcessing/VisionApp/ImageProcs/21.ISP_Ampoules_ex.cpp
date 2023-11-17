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

	/* Process each rectangle in sequence
	 * Sum up pixel values of each row
	 * Compare two rows with each other
	 * Find two rows where the difference of sums is greatest
	 */ 
	contours.clear();
	hierarchy.clear();
	findContours(src_eqa, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	uchar* pEqData = src_eqa.data;
	vector<vector<int>> sumOfRows;
	for (size_t i = 1; i < contours.size()-1; i++) //꼭지점 사이즈만큼 i 반복
	{
		vector<int> sRow;
		RotatedRect rrt = minAreaRect(contours[i]);
		//drawContours(src_eqa, contours, (int)i, 25, 1, LINE_8, hierarchy, 0);
		//rectangle(src_eqa, rrt.boundingRect(), 255);
		Point2f pts[4];
		rrt.points(pts);
		int rrt_x = pts[1].x, rrt_y = pts[1].y;

		int max_y, max_x;
		if (rrt.size.height >= rrt.size.width)
		{
			max_y = rrt_y + rrt.size.height;
			max_x = rrt_x + rrt.size.width;
		}
		else // if rrt.size.height < rrt.size.width
		{
			max_y = rrt_y + rrt.size.width;
			max_x = rrt_x + rrt.size.height;
		}
		int cols = src_eqa.cols;

		for (size_t y = rrt_y; y < max_y; y++)
		{
			int sum = 0;
			for (size_t x = rrt_x; x < max_x; x++)
			{
				// Calculate index of OpenCV Mat via: (row + x) * cols + (col + y)
				int idx = y * cols + x;
				sum += pEqData[idx];
			}
			sRow.push_back(sum);
		}
		sumOfRows.push_back(sRow);
		int a = 0;
	}

	bool flag = 0;
	int target_idx = 0;
	int prev_row = 0;
	int cur_row = 0;
	int outer_size = sumOfRows.size(), inner_size;
	int target_diff = 0;
	vector<int> target;
	for (int out_idx = 0; out_idx < outer_size; out_idx++)
	{
		inner_size = sumOfRows.at(out_idx).size();
		for (int in_idx = 1; in_idx < inner_size; in_idx++)
		{
			int prev = in_idx - 1;
			if ((prev) <= inner_size)
			{
				int a = 0;
				int diff = abs((sumOfRows.at(out_idx).at(in_idx) - sumOfRows.at(out_idx).at(prev)));
				if (target_diff < diff)
				{
					target_diff = diff;
					target_idx = in_idx;
				}
			}
		}
		target.push_back(target_idx);
		target_diff = 0;
		target_idx = 0;
	}

	return 1;
}