#pragma once

#include "ISP.h"

int main()
{

	std::string fileName = "../KCCImageNet/images/circle_plate.png";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	cv::Mat src_bin;
	cv::threshold(src_gray, src_bin, 150, 255, ThresholdTypes::THRESH_BINARY);

	uchar* pData = src_bin.data;
	size_t width = src_gray.cols;
	size_t height = src_gray.rows;


	Mat src_erosion = Mat::zeros(height, width, CV_8UC1);
	Mat src_dilation = Mat::zeros(height, width, CV_8UC1);

	//Ä§½Ä(erosion)
	const int SE_sz = 3; int SE_half_sz = SE_sz / 2;
	int SE_Cross[SE_sz * SE_sz] = {
		0,255,0,
		255,255,255,
		0,255,0 };
	int SE_Rect[SE_sz * SE_sz] = {
		255,255,255,
		255,255,255,
		255,255,255 };

	//const int SE_sz = 5; int SE_half_sz = SE_sz/2;
	//int SE_Cross[SE_sz * SE_sz] = {
	//	000,000,255,000,000,
	//	000,000,255,000,000,
	//	255,255,255,255,255,
	//	000,000,255,000,000,
	//	000,000,255,000,000 };
	//int SE_Rect[SE_sz * SE_sz] = {
	//	255,255,255,255,255,
	//	255,255,255,255,255,
	//	255,255,255,255,255,
	//	255,255,255,255,255,
	//	255,255,255,255,255};

	//erosion
	uchar* pDst = src_erosion.data;
	for (size_t row = SE_half_sz; row < height - SE_half_sz; row++) {
		for (size_t col = SE_half_sz; col < width - SE_half_sz; col++) {
			//struct element
			bool allone = true;
			for (int h = -SE_half_sz; h <= SE_half_sz; h++) {
				for (int w = -SE_half_sz; w <= SE_half_sz; w++) {
					int index = (row + h) * width + (col + w);
					int index_SE = (h + SE_half_sz) * SE_sz + (w + SE_half_sz);
					uchar input = pData[index];
					//input == 0 : background
					bool condition = (input == 0 && SE_Cross[index_SE] == 255);
					if (condition == true)
					{
						allone = false;
						break;
					}
				}
				if (!allone) break;
			}
			if (allone)
				pDst[row * width + col] = 255;
			else
				pDst[row * width + col] = 0;
		}
	}


	//dilation
	uchar* pErosion = pDst;
	uchar* pDilation = src_dilation.data;
	for (size_t row = SE_half_sz; row < height - SE_half_sz; row++) {
		for (size_t col = SE_half_sz; col < width - SE_half_sz; col++) {

			bool condition = false;
			for (int h = -SE_half_sz; h <= SE_half_sz; h++) {
				for (int w = -SE_half_sz; w <= SE_half_sz; w++) {
					int index = (row + h) * width + (col + w);
					int index_SE = (h + SE_half_sz) * SE_sz + (w + SE_half_sz);
					uchar input = pErosion[index];
					//input == 0 : background
					condition = (input == 255 && SE_Cross[index_SE] == 255);
					if (condition == true)
					{
						break;
					}
				}
				if (condition == true)
				{
					break;
				}
			}
			if (condition == true)
			{
				for (int h = -SE_half_sz; h <= SE_half_sz; h++) {
					for (int w = -SE_half_sz; w <= SE_half_sz; w++) {
						int index = (row + h) * width + (col + w);
						int index_SE = (h + SE_half_sz) * SE_sz + (w + SE_half_sz);
						if (SE_Cross[index_SE] == 255)
							pDilation[index] = 255;
					}
				}
			}
		}
	}
	return 1;
}