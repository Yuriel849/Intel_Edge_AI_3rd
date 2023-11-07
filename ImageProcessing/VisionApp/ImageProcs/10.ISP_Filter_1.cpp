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
	src_gray_blur = 0;

	// filter 3x3 ... 1/9
	const int filter_sz = 3;
	float blur[] = {
		1.0 / 9, 1.0 / 9, 1.0 / 9,
		1.0 / 9, 1.0 / 9, 1.0 / 9,
		1.0 / 9, 1.0 / 9, 1.0 / 9,
	};

	for (size_t row = 0; row < src_gray.rows - filter_sz; row++)
	{
		for (size_t col = 0; col < src_gray.cols - filter_sz; col++)
		{
			int sum = 0;
			for (size_t f_row = 0; f_row < filter_sz; f_row++)
			{
				for (size_t f_col = 0; f_col < filter_sz; f_col++)
				{
					int index = (row + f_row) * src_gray.cols + (col + f_col);
					int f_index = (f_row)*filter_sz + (f_col);
					sum = src_gray.data[index] + blur[f_index];
				}
			}
			int index = (row)*src_gray.cols + (col);
			src_gray_blur.data[index] = static_cast<uchar>(sum);
		}
	}

	return 1;
}
