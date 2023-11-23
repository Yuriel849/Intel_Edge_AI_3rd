#include "Common.h"

int main()
{
	// File path to original wafer image
	std::string filePath = "./res/img/wafer_original.png";

	cv::Mat src = cv::imread(filePath, cv::ImreadModes::IMREAD_GRAYSCALE); // Grayscale image

	// Check image is properly loaded
	if (src.empty())
	{
		std::cout << "Error opening image : " << filePath << std::endl;
		return EXIT_FAILURE;
	}

	cv::Mat src_bin = cv::Mat::zeros(src.size(), CV_8UC1);	// Empty matrix for binarization

	// Mask y-axis 157 - 719
	cv::Mat mask = cv::Mat::zeros(src.size(), CV_8UC1);
	uchar* srcData = src.data;
	uchar* maskData = mask.data;
	for (size_t row = 0; row < src.rows; row++)
	{
		for (size_t col = 0; col < src.cols; col++)
		{
			int index = row * src.cols + col;
			if (157 < row && row < 719) { maskData[index] = 0; }
			else { maskData[index] = srcData[index]; }
		}
	}

	// Binarization
	int thres = 125;
	cv::threshold(mask, src_bin, thres, 255, ThresholdTypes::THRESH_BINARY);

	// Morphology opening
	int kernelSz = 10;
	int shape = MorphShapes::MORPH_ELLIPSE;
	cv::Size sz = Size(2 * kernelSz + 1, 2 * kernelSz + 1);
	Mat SE = cv::getStructuringElement(shape, sz);

	Mat src_opening;
	int type = MorphTypes::MORPH_OPEN;
	cv::morphologyEx(src_bin, src_opening, type, SE);
	Mat diff_closing = src_bin - src_opening;

	int a = 0; // Anchor for breakpoint

	// Find contours
	RNG rng(12345);
	vector<vector<Point>> contours; //각 꼭지점 갯수 벡터배열에 저장
	vector<Vec4i> hierarchy;
	findContours(src_opening, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	Mat drawing = src.clone(); // Mat::zeros(src_color.size(), CV_3.8UC3);
	cvtColor(drawing, drawing, COLOR_GRAY2RGB);
	for (size_t i = 0; i < contours.size(); i++) //꼭지점 사이즈만큼 i 반복
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);

		RotatedRect rrt = minAreaRect(contours[i]);
		cv::rectangle(drawing, rrt.boundingRect2f().tl(), rrt.boundingRect2f().br(), CV_RGB(0, 255, 255), 4, LINE_8);

	}

	// Identify squares with bounding rectangle

	int b = 0; // Anchor for breakpoint
}