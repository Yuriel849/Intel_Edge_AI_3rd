#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../thirdparty/opencv_480/sources/samples/data/lena.jpg";
	cv::Mat src = cv::imread(fileName, cv::ImreadModes::IMREAD_ANYCOLOR);

	uchar* pData = src.data;//color pointer
	int length = src.total();//data length
	int channels = src.channels();

	//cv::Mat gray_cv = cv::Mat(src.rows, src.cols, CV_8UC1);
	cv::Mat gray = cv::Mat(src.rows, src.cols, CV_8UC1);

	//cv::cvtColor(src, gray_cv, ColorConversionCodes::COLOR_BGR2GRAY);

	ISP _isp;
	_isp.Convert_BGR2GRAY(src.data, src.cols, src.rows, gray.data);

	//Mat diff = gray_cv - gray;

	const int histoSz = 256;
	int histo[histoSz] = { 0, };
	_isp.Get_Histogram(gray.data, gray.cols, gray.rows, histo, histoSz);

	////확률밀도함수
	//int acc[histoSz] = { 0, };
	////acc[0] = histo[0]+ histo[1]
	//acc[0] = histo[0];
	//for (size_t i = 1; i < histoSz; i++)
	//{
	//	acc[i] = acc[i - 1]/*histo[i-1]*/ + histo[i];
	//}

	////new Look Up Table ... 영상의 각 화소 값들을 새로운 대응값으로 맵핑
	//int new_Gray[histoSz] = { 0, };
	//for (size_t i = 0; i < histoSz; i++)
	//{
	//	new_Gray[i] = static_cast<int>(1.0 * acc[i] * 255 / length);
	//}

	////assign new Gray value using LUT
	//cv::Mat gray_Eq = cv::Mat(src.rows, src.cols, CV_8UC1);
	//for (size_t i = 0; i < length; i++)
	//{
	//	gray_Eq.data[i] = new_Gray[gray.data[i]];
	//}

	cv::Mat gray_Eq = cv::Mat(src.rows, src.cols, CV_8UC1);

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