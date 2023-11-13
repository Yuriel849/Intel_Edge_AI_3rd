#pragma once

#include <algorithm>    // std::sort

#include "ISP.h"

int main()
{
	std::string fileName = "../thirdparty/opencv_481/sources/samples/data/lena_gray.jpg";
	std::string fileName_cmp = "../thirdparty/opencv_481/sources/samples/data/lena_gray.jpg";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);
	cv::Mat src_gray_cmp = cv::imread(fileName_cmp, cv::ImreadModes::IMREAD_GRAYSCALE);

	// Calculate index of OpenCV Mat via: (row + x) * cols + (col + y)
	int index, top, right, bottom, left;
	for (size_t row = 0; row < src_gray.rows; row++)
	{
		for (size_t col = 0; col < src_gray.cols; col++)
		{
			index = row * src_gray.cols + col;
			if ((src_gray.data[index] < 10) || (250 < src_gray.data[index]))
			{
				top = src_gray.data[index - src_gray.cols];
				right = src_gray.data[index + 1];
				bottom = src_gray.data[index + src_gray.cols];
				left = src_gray.data[index - 1];
				src_gray.data[index] = int(std::round((top + right + bottom + left) / 4.0));
			}
		}
	}

	return 1;
}