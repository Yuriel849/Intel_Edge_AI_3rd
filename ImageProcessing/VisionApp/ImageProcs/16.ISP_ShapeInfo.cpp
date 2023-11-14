#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../KCCImageNet/shapes.jpg";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	uchar* pData = src_gray.data;
	size_t width = src_gray.cols;
	size_t height = src_gray.rows;

	//int threshold = 200; // 0~255 사이의 값을 임계값으로 삼는다.
	
	// cv::Mat::zeros(SIZE, TYPE) -> 모든 값을 0으로 초기화
	cv::Mat src_bin = cv::Mat::zeros(cv::Size(width, height), CV_8UC1);
	cv::Mat src_obj = cv::Mat::zeros(cv::Size(width, height), CV_8UC1);
	uchar* pDataBin = src_bin.data;

	int threshold_min = 60;
	int threshold_max = 250;

	// 이진화 Binarization0
	//	 이진화란 Color 혹은 Grayscale 영상(image)을 흑백 영상으로 변환하는 것을 의미한다.
	//	 임계값 threshold를 기준으로 임계값보다 크거나 작은 값을 흑 혹은 백색으로 변환한다.
	//for (size_t row = 0; row < height; row++)
	//{
	//	for (size_t col = 0; col < width; col++)
	//	{
	//		int idx = row * width + col;
	//		int value = pData[idx];
	//		//if (value < threshold) { pDataBin[idx] = 255; }
	//		//else { pDataBin[idx] = 0; }
	//		if (value > threshold_min && value < threshold_max) { pDataBin[idx] = 255; }
	//	}
	//}

	for (size_t i = 0; i < width * height; i++)
	{
		int value = pData[i];
		(value > threshold_max) ? pDataBin[i] = 0 : pDataBin[i] = 255;
	}

	src_obj = src_bin & src_gray;

	RNG rng(12345);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(src_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat drawing = Mat::zeros(src_bin.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
	}

	// contours... vector[i].. n-th 개수를 출력하세요.
	for (size_t i = 0; i < contours.size(); i++)
	{
		std::cout << "Object[" << i + 1 << "] 개수는 " << contours[i].size() << " 입니다." << std::endl;
	}

	return 1;
}