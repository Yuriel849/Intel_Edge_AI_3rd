// ISP = Image Signal Processing

#pragma once

#include "Common.h"

int main()
{
	std::string fileName = "../KCCImageNet/stop_img.png";
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_ANYCOLOR);


	return 1;
}