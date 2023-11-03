// ISP = Image Signal Processing

#pragma once

#include "Common.h"

int main()
{
	std::string fileName = "../KCCImageNet/find_google_area.png";
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	uchar* pData = src.data;  // data array
	int length = src.total(); // data length

	// histrogram을 구하시오 (src 이미지 버퍼)

	/* 출력 예시
	 *	0	| ========== 10
	 *	1	| ===== 5
	 *	2	| ======== 8
	 *	...
	 *	255 | ============ 12
	 * 
	 */

	int counts[256] = { 0, };
	int cnt = 1;
	// value... -> ...index

	for (size_t i = 0; i < length; i++) { counts[*(pData+i)]++; }

	for (size_t i = 0; i < 256; i++)
	{
		cout << i << "\t| ";
		cnt = counts[i] / 100;
		for (size_t k = 0; k < cnt; k++) { cout << "="; }
		cout << " " << counts[i] << endl;
	}


	return 1;
}