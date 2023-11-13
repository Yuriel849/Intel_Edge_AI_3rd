#pragma once

#include <algorithm>    // std::sort

#include "ISP.h"

int main()
{
	std::string fileName = "../thirdparty/opencv_481/sources/samples/data/lena_gray.jpg";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	cv::Mat src_gray_org = src_gray.clone();

	// Calculate index of OpenCV Mat via: (row + x) * cols + (col + y)
	int index, top, right, bottom, left;
	for (size_t row = 1; row < src_gray.rows; row++)
	{
		for (size_t col = 1; col < src_gray.cols; col++)
		{
			index = row * src_gray.cols + col;
			if ((src_gray.data[index] < 5) || (250 < src_gray.data[index]))
			{
				// Calculate average of top, right, bottom, left pixels to fill empty spot
				//top = src_gray.data[index - src_gray.cols];	   // (row-1) * src_gray.cols + (col)
				//bottom = src_gray.data[index + src_gray.cols]; // (row+1) * src_gray.cols + (col)
				//left = src_gray.data[index - 1];			   // (row) * src_gray.cols + (col-1)
				//right = src_gray.data[index + 1];			   // (row) * src_gray.cols + (col+1)
				//src_gray.data[index] = static_cast<uchar>(std::round((top + right + bottom + left) / 4.0));

				// Calculate average using eight pixels surrounding target
				int v_NN = src_gray.data[(row - 1) * src_gray.cols + (col)];
				int v_SS = src_gray.data[(row + 1) * src_gray.cols + (col)];
				int v_LL = src_gray.data[(row)*src_gray.cols + (col - 1)];
				int v_RR = src_gray.data[(row)*src_gray.cols + (col + 1)];
				int v_NW = src_gray.data[(row - 1) * src_gray.cols + (col - 1)];
				int v_NE = src_gray.data[(row - 1) * src_gray.cols + (col + 1)];
				int v_SW = src_gray.data[(row + 1) * src_gray.cols + (col - 1)];
				int v_SE = src_gray.data[(row + 1) * src_gray.cols + (col + 1)];
				src_gray.data[index] = (v_NN + v_SS + v_LL + v_RR + v_NW + v_NE + v_SW + v_SE) / 8;
			}
		}
	}

	return 1;
}