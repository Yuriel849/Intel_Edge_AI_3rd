#pragma once

#include <algorithm>    // std::sort

#include "ISP.h"

int main()
{
	// 노이즈가 없는 대표 신호 값을 정하시오. 정렬 후 중간값을 구하라 (신호처리에 매우 효과적이면서도 매우 간단한 알고리즘이다. 단점은 반복 사용시 시간이 오래걸린다.).
	int datas[] = { 6,4,2,5,9,8,4,5,2,1,5,3,6,5,2,1,1,4,5,2,23,3,6,6,1248,2,56,6,105,112 };
	int length = sizeof(datas) / sizeof(datas[0]); // 30
	sort(datas, datas + length);

	// vector 사용
	std::vector<int> vDatas(datas, datas + length);
	std::sort(vDatas.begin(), vDatas.end());

	int major = datas[length / 2];
	int vMajor = vDatas[length / 2];

	cout << major << endl;
	cout << vMajor << endl;

	std::string fileName = "../thirdparty/opencv_480/sources/samples/data/lena.jpg";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	cv::Mat src_gray_blur = src_gray.clone();
	src_gray_blur = 255;

	// filter 3x3 ... 1/9
	const int filter_sz = 3;
	float blur[] = {
		1.0 / 9, 1.0 / 9, 1.0 / 9,
		1.0 / 9, 1.0 / 9, 1.0 / 9,
		1.0 / 9, 1.0 / 9, 1.0 / 9,
	};

	int half_kernelSize = filter_sz / 2;
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
					sum += src_gray.data[index] * blur[f_index];
				}
			}
			int index = (row)*src_gray.cols + (col);
			src_gray_blur.data[index] = static_cast<uchar>(sum);
		}
	}

	// copy col + 1 to col, col[1] => col[0], left
	// copy col to col + 1, col[98] => col[99], right
	// copy row + 1 to row, row[1] => row[0], top
	// copy row to row + 1, row[98] => row[99], bottom
	// corner[4]... ex) 좌상, (col[1] + row[1]) / 2

	// left and right edges
	for (size_t row = 0; row < src_gray_blur.rows; row++)
	{
		int index_0 = row * src_gray_blur.cols + 0;
		int index_1 = row * src_gray_blur.cols + 1;

		int index_2 = row * src_gray_blur.cols + (src_gray_blur.cols - 2);
		int index_3 = row * src_gray_blur.cols + (src_gray_blur.cols - 1);

		src_gray_blur.data[index_0] = src_gray_blur.data[index_1];
		src_gray_blur.data[index_3] = src_gray_blur.data[index_2];
	}

	// top and bottom edges
	for (size_t col = 1; col < src_gray_blur.cols - 1; col++)
	{
		int index_0 = col;
		int index_1 = (src_gray_blur.cols) + col;

		int index_2 = (src_gray_blur.rows - 2) * (src_gray_blur.cols) + col;
		int index_3 = (src_gray_blur.rows - 1) * (src_gray_blur.cols) + col;

		src_gray_blur.data[index_0] = src_gray_blur.data[index_1];
		src_gray_blur.data[index_3] = src_gray_blur.data[index_2];
	}

	// top-left corner
	src_gray_blur.data[0] = (src_gray_blur.data[1] + src_gray_blur.data[src_gray_blur.cols]) / 2;
	// top-right corner
	src_gray_blur.data[src_gray_blur.cols-1] = (src_gray_blur.data[src_gray_blur.cols - 2] + src_gray_blur.data[src_gray_blur.cols + src_gray_blur.cols - 1]) / 2;
	// bottom-left corner
	int target = (src_gray_blur.rows - 1) * src_gray_blur.cols;
	int top = (src_gray_blur.rows - 2) * src_gray_blur.cols;
	int side = (src_gray_blur.rows - 1) * src_gray_blur.cols + 1;
	src_gray_blur.data[target] = (src_gray_blur.data[top] + src_gray_blur.data[side]) / 2;
	// bottom-right corner
	target = src_gray_blur.rows * src_gray_blur.cols - 1;
	top = (src_gray_blur.rows - 1) * src_gray_blur.cols - 1;
	side = src_gray_blur.rows * src_gray_blur.cols - 2;
	src_gray_blur.data[target] = (src_gray_blur.data[top] + src_gray_blur.data[side]) / 2;

	return 1;
}
