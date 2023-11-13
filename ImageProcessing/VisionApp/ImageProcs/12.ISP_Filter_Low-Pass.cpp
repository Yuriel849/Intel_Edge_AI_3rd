#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../thirdparty/opencv_480/sources/samples/data/lena.jpg";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	cv::Mat src_gray_blur = src_gray.clone();
	cv::Mat src_gray_blur2 = src_gray.clone();
	cv::Mat src_gray_blur3 = src_gray.clone();
	src_gray_blur = 255;
	src_gray_blur2 = 255;
	src_gray_blur3 = 255;

	// Low-pass filter
	const int filter_sz = 3;
	float blur[] = {
		1.0 / 9, 1.0 / 9, 1.0 / 9,
		1.0 / 9, 1.0 / 9, 1.0 / 9,
		1.0 / 9, 1.0 / 9, 1.0 / 9,
	};
	float blur2[] = {
		1.0 / 16, 2.0 / 16, 1.0 / 16,
		2.0 / 16, 4.0 / 16, 2.0 / 16,
		1.0 / 16, 2.0 / 16, 1.0 / 16,
	};
	float blur3[] = {
		2.0 / 25, 3.0 / 25, 2.0 / 25,
		3.0 / 25, 5.0 / 25, 3.0 / 25,
		2.0 / 25, 3.0 / 25, 2.0 / 25,
	};

	int half_kernelSize = filter_sz / 2;
	for (size_t row = half_kernelSize; row < src_gray.rows - half_kernelSize; row++)
	{
		for (size_t col = half_kernelSize; col < src_gray.cols - half_kernelSize; col++)
		{
			int sum = 0;
			int sum2 = 0;
			int sum3 = 0;
			for (int f_row = -half_kernelSize; f_row <= half_kernelSize; f_row++)
			{
				for (int f_col = -half_kernelSize; f_col <= half_kernelSize; f_col++)
				{
					int index = (row + f_row) * src_gray.cols + (col + f_col);
					int f_index = (f_row + half_kernelSize) * filter_sz + (f_col + half_kernelSize);
					sum += src_gray.data[index] * blur[f_index];
					sum2 += src_gray.data[index] * blur2[f_index];
					sum3 += src_gray.data[index] * blur3[f_index];
				}
			}
			int index = (row)*src_gray.cols + (col);
			src_gray_blur.data[index] = static_cast<uchar>(sum);
			src_gray_blur2.data[index] = static_cast<uchar>(sum2);
			src_gray_blur3.data[index] = static_cast<uchar>(sum3);
		}
	}

	return 1;
}