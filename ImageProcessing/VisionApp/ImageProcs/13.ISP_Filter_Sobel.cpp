#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../thirdparty/opencv_481/sources/samples/data/lena.jpg";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);
	cv::Mat src_gray_sobel = src_gray.clone();
	src_gray_sobel = 255;

	// Low-pass filter
	const int filter_sz = 3;
	int half_kernelSize = filter_sz / 2;
	float hori_filter[] = {
		-1, -2, -1,
		0, 0, 0,
		1, 2, 1
	};
	float ver_filter[] = {
		1, 0, -1,
		2, 0, -2,
		1, 0, -1
	};

	double threshold = 128;
	// Calculate index of OpenCV Mat via: (row + x) * cols + (col + y)
	for (size_t row = half_kernelSize; row < src_gray.rows - half_kernelSize; row++)
	{
		for (size_t col = half_kernelSize; col < src_gray.rows - half_kernelSize; col++)
		{
			double ver_grad = 0;
			double hori_grad = 0;
			for (int f_row = -half_kernelSize; f_row <= half_kernelSize; f_row++)
			{
				for (int f_col = -half_kernelSize; f_col <= half_kernelSize; f_col++)
				{
					int f_index = (f_row + half_kernelSize) * filter_sz + (f_col + half_kernelSize);
					hori_grad += hori_filter[f_index] * src_gray.data[(row + f_row) * src_gray.cols + (col + f_col)];
					ver_grad += ver_filter[f_index] * src_gray.data[(row + f_row) * src_gray.cols + (col + f_col)];

				}
			}
			if ((abs(hori_grad) + abs(ver_grad)) > threshold)
			{
				src_gray_sobel.data[(row)*src_gray.cols + (col)] = 255;
			}
			else
			{
				src_gray_sobel.data[(row)*src_gray.cols + (col)] = 0;
			}
		}
	}

	return 1;
}