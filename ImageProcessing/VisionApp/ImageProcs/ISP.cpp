#include "ISP.h"

ISP::ISP()
{
	std::cout << "ISP::Ctor" << std::endl;
}

ISP::~ISP()
{
	std::cout << "ISP::Dtor" << std::endl;
}

bool ISP::Convert_BGR2GRAY(uchar* pBGR, int width, int height, uchar* pGray)
{
	if (pBGR == nullptr || pGray == nullptr) { return false; }

#if 1
	Mat src = Mat(width, height, CV_8UC3, pGray);
	Mat gray_cv = Mat(width, height, CV_8UC1, pGray);
	cvtColor(src, gray_cv, COLOR_BGR2GRAY);
#else // Code above gives better performance
	for (size_t row = 0; row < width; row++)
	{
		for (size_t col = 0; col < height; col++)
		{
			int index = (row) * height + (col);
			int index_B = index * 3 + 0;
			int index_G = index * 3 + 1;
			int index_R = index * 3 + 2;
			int val_B = pBGR[index_B];
			int val_G = pBGR[index_G];
			int val_R = pBGR[index_R];

			int val_Y = 0.299 * val_R + 0.587 * val_G + 0.114 * val_B;
			pGray[index] = (uchar)(val_Y + 0.5);
		}
	}
#endif
	return true;
}

bool ISP::Get_Histogram(uchar* pGray, int cols, int rows, int* pHisto, int histoSz)
{
	if (pGray == nullptr || pHisto == nullptr) { return false; }

	for (size_t i = 0; i < cols * rows; i++)
	{
		if (pGray[i] >= histoSz) continue; // size 256
		pHisto[pGray[i]]++;
	}

	return true;
}

bool ISP::Enhance_HistogramEq(uchar* pGray, int cols, int rows, uchar* pGrayEq)
{
	const int histoSz = 256;
	//확률밀도함수
	int acc[histoSz] = { 0, };
	int histo[histoSz] = { 0, };
	//acc[0] = histo[0]+ histo[1]
	acc[0] = histo[0];
	for (size_t i = 1; i < histoSz; i++)
	{
		acc[i] = acc[i - 1]/*histo[i-1]*/ + histo[i];
	}

	//new Look Up Table ... 영상의 각 화소 값들을 새로운 대응값으로 맵핑
	int new_Gray[histoSz] = { 0, };
	for (size_t i = 0; i < histoSz; i++)
	{
		new_Gray[i] = static_cast<int>(1.0 * acc[i] * 255 / (rows*cols));
	}

	//assign new Gray value using LUT
	cv::Mat gray_Eq = cv::Mat(rows, cols, CV_8UC1);
	for (size_t i = 0; i < (rows*cols); i++)
	{
		gray_Eq.data[i] = new_Gray[pGray[i]];
	}

	int histo_new[histoSz] = { 0, };
	Get_Histogram(pGrayEq, cols, rows, histo_new, histoSz);

	std::ofstream ofile("histogram_eq.csv");
	std::string str = "brightness, histo, histo_eq";
	ofile << str << "\n";
	if (ofile.is_open()) {
		for (size_t i = 0; i < histoSz; i++)
		{
			str = std::format("{}, {}, {}\n", i, histo[i], histo_new[i]);
			ofile << str;
		}
		ofile.close();
	}

	return true;
}
