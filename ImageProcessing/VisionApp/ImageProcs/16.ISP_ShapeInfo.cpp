#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../KCCImageNet/shapes.jpg";
	cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);

	uchar* pData = src_gray.data;
	size_t width = src_gray.cols;
	size_t height = src_gray.rows;

	//int threshold = 200; // 0~255 ������ ���� �Ӱ谪���� ��´�.
	
	// cv::Mat::zeros(SIZE, TYPE) -> ��� ���� 0���� �ʱ�ȭ
	cv::Mat src_bin = cv::Mat::zeros(cv::Size(width, height), CV_8UC1);
	cv::Mat src_obj = cv::Mat::zeros(cv::Size(width, height), CV_8UC1);
	uchar* pDataBin = src_bin.data;

	int threshold_min = 60;
	int threshold_max = 200;

	// ����ȭ Binarization0
	//	 ����ȭ�� Color Ȥ�� Grayscale ����(image)�� ��� �������� ��ȯ�ϴ� ���� �ǹ��Ѵ�.
	//	 �Ӱ谪 threshold�� �������� �Ӱ谪���� ũ�ų� ���� ���� �� Ȥ�� ������� ��ȯ�Ѵ�.
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
		drawContours(drawing, contours, (int)i, color, 1, LINE_8, hierarchy, 0);
	}

	cv::Mat src_color;
	cv::cvtColor(src_gray, src_color, ColorConversionCodes::COLOR_GRAY2BGR);
	std::cout << contours.size() << std::endl;
	// contours... vector[i].. n-th ������ ����ϼ���.
	for (size_t i = 0; i < contours.size(); i++)
	{
		// Additional functionalities and data of contours
		double area = contourArea(contours[i]);
		RotatedRect rrt = minAreaRect(contours[i]);
		double arcLen = arcLength(contours[i], true);

		Point ptTxt = Point(rrt.boundingRect().x, rrt.boundingRect().y);
		string msg;
		msg = std::format("area = {:.1f}", area);
		putText(src_color, msg, Point(ptTxt.x, ptTxt.y + 30 * 0), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
		msg = std::format("x,y = {:.1f}, {:.1f}", rrt.center.x, rrt.center.y);
		putText(src_color, msg, Point(ptTxt.x, ptTxt.y + 30 * 1), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
		msg = std::format("length = {:.1f}", arcLen);
		putText(src_color, msg, Point(ptTxt.x, ptTxt.y + 30 * 2), FONT_HERSHEY_SIMPLEX, 0.8, CV_RGB(10, 0, 10), 1, 8);
		cv::rectangle(src_color, rrt.boundingRect2f().tl(), rrt.boundingRect2f().br(), CV_RGB(0, 0, 255));
		cv::drawMarker(src_color, rrt.center, CV_RGB(255, 0, 0));

		const int ptSz = 4;
		Point2f pt[ptSz];
		rrt.points(pt);

		for (size_t i = 0; i < ptSz; i++)
		{
			cv::line(src_color, pt[i % ptSz], pt[(i + 1) % ptSz], CV_RGB(255, 0, 255), 1);
		}

		continue;

		std::cout << "Object[" << i + 1 << "] ������ " << contours[i].size() << " �Դϴ�." << std::endl;
		int CoGx, CoGy; // CoG = Center of Gravity
		CoGx = CoGy = 0;
		int accX = 0, accY = 0;
		int length = contours[i].size();

		int x_min = width, x_max = 0, y_min = height, y_max = 0;
		for (size_t n = 0; n < length; n++)
		{
			accX += contours[i].at(n).x;
			accY += contours[i].at(n).y;
			if (x_min > contours[i].at(n).x) { x_min = contours[i].at(n).x; }
			if (x_max < contours[i].at(n).x) { x_max = contours[i].at(n).x; }
			if (y_min > contours[i].at(n).y) { y_min = contours[i].at(n).y; }
			if (y_max < contours[i].at(n).y) { y_max = contours[i].at(n).y; }
		}
		CoGx = accX / length;
		CoGy = accY / length;
		std::cout << "Object[" << i + 1 << "] CoG.x = " << CoGx << " CoG.y = " << CoGy << std::endl;

		cv::line(src_color, Point(CoGx - 10, CoGy - 10), Point(CoGx + 10, CoGy + 10), CV_RGB(255, 0, 0), 10);
		cv::line(src_color, Point(CoGx + 10, CoGy - 10), Point(CoGx - 10, CoGy + 10), CV_RGB(255, 0, 0), 10);
		
		//const int ptSz = 4;
		//Point pt[ptSz];
		//pt[0].x = x_min; pt[0].y = y_min; // �»�
		//pt[1].x = x_max; pt[1].y = y_min; // ���
		//pt[2].x = x_max; pt[2].y = y_max; // ����
		//pt[3].x = x_min; pt[3].y = y_max; // ����

		//for (size_t i = 0; i < ptSz; i++)
		//{
		//	cv::line(src_color, pt[i%ptSz], pt[(i+1)%ptSz], CV_RGB(0, 0, 255), 1);
		//}
	}

	// Draw a rectangle around each object, such that the object is entirely inside its rectangle while the rectangle is the smallest it can be
	//for (size_t i = 0; i < contours.size(); i++)
	//{
	//	Point pt[4];
	//	for (size_t m = 0; m < 4; m++)
	//	{
	//		pt[m].x = contours[i][0].x;
	//		pt[m].y = contours[i][0].y;
	//	}
	//	for (size_t k = 1; k < contours[i].size(); k++)
	//	{
	//		// x-min & y-min -> upper-left
	//		if (pt[0].x > contours[i][k].x) { pt[0].x = contours[i][k].x; }
	//		if (pt[0].y > contours[i][k].y) { pt[0].y = contours[i][k].y; }
	//		// x-min & y-max -> lower-left
	//		if (pt[1].x > contours[i][k].x) { pt[1].x = contours[i][k].x; }
	//		if (pt[1].y < contours[i][k].y) { pt[1].y = contours[i][k].y; }
	//		// x-max & y-max -> lower-right
	//		if (pt[2].x < contours[i][k].x) { pt[2].x = contours[i][k].x; }
	//		if (pt[2].y < contours[i][k].y) { pt[2].y = contours[i][k].y; }
	//		// x-max & y-min -> upper-right
	//		if (pt[3].x < contours[i][k].x) { pt[3].x = contours[i][k].x; }
	//		if (pt[3].y > contours[i][k].y) { pt[3].y = contours[i][k].y; }
	//	}
	//	for (size_t i = 0; i < 4; i++)
	//	{
	//		cv::line(src_color, pt[i], pt[((i+1) == 4) ? 0 : i+1], CV_RGB(0, 0, 255), 2);
	//	}
	//}

	return 1;
}