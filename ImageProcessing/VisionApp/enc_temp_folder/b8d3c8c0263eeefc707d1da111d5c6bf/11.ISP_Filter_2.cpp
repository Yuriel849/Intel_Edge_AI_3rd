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


	// left and right edges
	//for (size_t row = 0; row < src_gray_blur.rows; row++)
	//{
	//	int index_0 = row * src_gray_blur.cols + 0;
	//	int index_1 = row * src_gray_blur.cols + 1;

	//	int index_2 = row * src_gray_blur.cols + (src_gray_blur.cols - 2);
	//	int index_3 = row * src_gray_blur.cols + (src_gray_blur.cols - 1);

	//	src_gray_blur.data[index_0] = src_gray_blur.data[index_1];
	//	src_gray_blur.data[index_3] = src_gray_blur.data[index_2];
	//}

	// top and bottom edges
	//for (size_t col = 1; col < src_gray_blur.cols - 1; col++)
	//{
	//	int index_0 = col;
	//	int index_1 = (src_gray_blur.cols) + col;

	//	int index_2 = (src_gray_blur.rows - 2) * (src_gray_blur.cols) + col;
	//	int index_3 = (src_gray_blur.rows - 1) * (src_gray_blur.cols) + col;

	//	src_gray_blur.data[index_0] = src_gray_blur.data[index_1];
	//	src_gray_blur.data[index_3] = src_gray_blur.data[index_2];
	//}

	// top-left corner
	//src_gray_blur.data[0] = (src_gray_blur.data[1] + src_gray_blur.data[src_gray_blur.cols]) / 2;
	// top-right corner
	//src_gray_blur.data[src_gray_blur.cols - 1] = (src_gray_blur.data[src_gray_blur.cols - 2] + src_gray_blur.data[src_gray_blur.cols + src_gray_blur.cols - 1]) / 2;
	// bottom-left corner
	//int target = (src_gray_blur.rows - 1) * src_gray_blur.cols;
	//int top = (src_gray_blur.rows - 2) * src_gray_blur.cols;
	//int side = (src_gray_blur.rows - 1) * src_gray_blur.cols + 1;
	//src_gray_blur.data[target] = (src_gray_blur.data[top] + src_gray_blur.data[side]) / 2;
	// bottom-right corner
	//target = src_gray_blur.rows * src_gray_blur.cols - 1;
	//top = (src_gray_blur.rows - 1) * src_gray_blur.cols - 1;
	//side = src_gray_blur.rows * src_gray_blur.cols - 2;
	//src_gray_blur.data[target] = (src_gray_blur.data[top] + src_gray_blur.data[side]) / 2;

	return 1;
}