#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../thirdparty/opencv_481/sources/samples/data/lena.jpg";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);
	cv::Mat src_gray_filtered = src_gray.clone();
	src_gray_filtered = 255;

	const int filter_sz = 5;
	int half_kernelSize = filter_sz / 2;

	std::vector<float> gaussian;
	//float gaussian[filter_sz * filter_sz] = { 0, };
	float sig = 0.8;
	for (int y = -half_kernelSize; y <= half_kernelSize; y++)
	{
		for (int x = -half_kernelSize; x <= half_kernelSize; x++)
		{
			//int index = y * filter_sz + x;
			//float tmp = 1.0 / (2 * 3.141592 * sig * sig) * exp(0-((x * x) + (y * y)) / (2 * sig * sig));
			//gaussian[index] = tmp;
			gaussian.push_back(1.0 / (2 * CV_PI * sig * sig * exp((x*x + y*y) / (2 * sig * sig))));
		}
	}

	for (size_t row = half_kernelSize; row < src_gray.rows - half_kernelSize; row++)
	{
		for (size_t col = half_kernelSize; col < src_gray.cols - half_kernelSize; col++)
		{
			int sum = 0;
			for (int f_row = -half_kernelSize; f_row <= half_kernelSize; f_row++)
			{
				for (int f_col = -half_kernelSize; f_col <= half_kernelSize; f_col++)
				{
					int index = (row + f_row) * src_gray.cols + (col + f_col);
					int f_index = (f_row + half_kernelSize) * filter_sz + (f_col + half_kernelSize);
					sum += src_gray.data[index] * gaussian[f_index];
				}
			}
			int index = (row)*src_gray.cols + (col);
			src_gray_filtered.data[index] = static_cast<uchar>(sum);
		}
	}

	return 1;
}