// ISP = Image Signal Processing

#pragma once

#include "Common.h"

#if 0
int main()
{
	std::string fileName = "../KCCImageNet/find_google_area.png";
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_COLOR);

	cv::resize(src, src, cv::Size(src.cols * 2, src.rows * 2));

	// GRAYSCALE uses only one value per pixel
	// COLOR uses channels or bands to describe the three colors (RGB) per pixel.

	uchar* pData = src.data;  // data array ... start[0, 1, 2, 3, 4, 5]
	int length = src.total(); // data length
	int channels = src.channels(); // channels = 1 for GRAYSCALE, channels = 3 for COLOR

	// histrogram을 구하시오 (src 이미지 버퍼)

	/* 출력 예시
	 *	0	| ========== 10
	 *	1	| ===== 5
	 *	2	| ======== 8
	 *	...
	 *	255 | ============ 12
	 * 
	 */

	const int histoSz = 256;
	int counts[histoSz] = { 0, };
	//int* pHisto = new int[length]; // 동적 메모리 할당
	int cnt = 1;
	// value... -> ...index

	for (size_t i = 0; i < length; i++) { counts[*(pData+i)]++; }

	int size = src.rows * src.cols;
	auto result = std::minmax_element(pData, pData + length);
	double mean_brightness = cv::mean(src)[0];
	auto _minmax = std::minmax_element(counts, counts + histoSz);
	int _min_value = *_minmax.first;
	int _max_value = *_minmax.second;

	for (size_t i = 0; i < 256; i++)
	{
		cout << i << "\t| ";
		//cnt = counts[i] / 100;
		cnt = (counts[i] * 1.0 / _max_value) * 100;
		for (size_t k = 0; k < cnt; k++) { cout << "="; }
		cout << " " << counts[i] << endl;
	}

	cv::Mat draw = src.clone();
	cvtColor(draw, draw, ColorConversionCodes::COLOR_GRAY2BGR);
	for (size_t row = 0; row < histoSz; row+=2)
	{
		int scaled_cols = (counts[row] * 1.0 / _max_value) * src.cols;
		cv::Point st = Point(0, row * 2.7);
		cv::Point ed = Point(scaled_cols, row * 2.7);
		cv::line(draw, st, ed, CV_RGB(255, 255, 0));
	}

	return 1;
}
#endif