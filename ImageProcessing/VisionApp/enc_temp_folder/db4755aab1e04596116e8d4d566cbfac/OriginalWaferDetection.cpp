#include "Common.h"

int main()
{
	// File path to original wafer image
	std::string filePath = "./res/img/wafer_original.png";

	// Original image is in grayscale, so use as src
	cv::Mat src = cv::imread(filePath, cv::ImreadModes::IMREAD_GRAYSCALE); // Grayscale image

	// Check image is properly loaded
	if (src.empty())
	{
		std::cout << "Error opening image : " << filePath << std::endl;
		return EXIT_FAILURE;
	}

	cv::Mat src_bin = cv::Mat::zeros(src.size(), CV_8UC1);			   // Empty matrix for binarization
	cv::Mat src_dx = cv::Mat::zeros(src.size(), CV_8UC1);
	cv::Mat src_dy = cv::Mat::zeros(src.size(), CV_8UC1);
	cv::Mat src_sobel = cv::Mat::zeros(src.size(), CV_8UC1);
	cv::Mat src_sobel_f = cv::Mat::zeros(src.size(), CV_8UC1);

	// Mask y-axis 157 - 719
	cv::Mat mask = cv::Mat::zeros(src.size(), CV_8UC1);
	uchar* srcData = src.data;
	uchar* maskData = mask.data;
	for (size_t row = 0; row < src.rows; row++)
	{
		for (size_t col = 0; col < src.cols; col++)
		{
			int index = row * src.cols + col;
			if (157 < row && row < 719)
			{
				maskData[index] = 0;
			}
			else
			{
				maskData[index] = srcData[index];
			}
		}
	}

	// Binarization
	int thres = 125;
	cv::threshold(mask, src_bin, thres, 255, ThresholdTypes::THRESH_BINARY);

	int kernelSz = 10;
	int shape = MorphShapes::MORPH_ELLIPSE;
	cv::Size sz = Size(2 * kernelSz + 1, 2 * kernelSz + 1);
	Mat SE = cv::getStructuringElement(shape, sz);

	Mat src_closing;
	int type = MorphTypes::MORPH_OPEN;
	cv::morphologyEx(src_bin, src_closing, type, SE);
	Mat diff_closing = src_bin - src_closing;

	int a = 0;

	// Sobel operator filtering
	Scharr(src, src_dx, CV_16S, 1, 0);
	Scharr(src, src_dy, CV_16S, 0, 1);
	Canny(src_dx, src_dy, src_sobel, 1, 3);
	src_bin.copyTo(src_sobel_f, src_sobel);




	int b = 0; // Anchor for breakpoint
}