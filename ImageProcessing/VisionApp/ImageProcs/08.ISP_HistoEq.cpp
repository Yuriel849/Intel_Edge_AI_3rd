#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../thirdparty/opencv_480/sources/samples/data/lena.jpg";
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_ANYCOLOR); // Reads this file and saves to matrix (Mat class)

	uchar* pData = src.data; //color pointer; src.data is data of src, 512 * 512 * 3 elements array
	int length = src.total(); //data length; src.total() is total length of src.data
	int channels = src.channels(); // 3, for R G B color values

	ISP _isp;

	//origin_image
	cv::Mat gray = cv::Mat(src.rows, src.cols, CV_8UC1);
	//enhance_image using HistoEq
	cv::Mat gray_Eq = cv::Mat(src.rows, src.cols, CV_8UC1);

	_isp.Convert_BGR2GRAY(src.data, src.cols, src.rows, gray.data);
	_isp.Enhance_HistogramEq(
		gray.data,
		gray.cols,
		gray.rows,
		gray_Eq.data
	);


	//library OpenCV
	//check correlation
	{
		Mat gray_cv;
		Mat gray_Eq_cv;
		cvtColor(src, gray_cv, COLOR_BGR2GRAY);
		cv::equalizeHist(gray_cv, gray_Eq_cv);

		Mat diff = gray_Eq - gray_Eq_cv;
		double error = cv::sum(diff)[0];
		int a = 0;

	}


	return 1;
}