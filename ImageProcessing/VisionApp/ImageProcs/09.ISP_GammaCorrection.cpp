#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../thirdparty/opencv_480/sources/samples/data/lena.jpg";
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_ANYCOLOR);

	ISP _isp;

	// Gray Input

	// Gamma Correction
	// double normalized_value = (double)pixels[i] / 255.0;
	// double corrected_value = pow(normalized_value, gamma) * 255.0;

	// Gray Output


	return 1;
}