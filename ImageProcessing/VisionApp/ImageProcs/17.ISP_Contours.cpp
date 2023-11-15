#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../KCCImageNet/stop_img.png";
	cv::Mat src_color = cv::imread(fileName, cv::ImreadModes::IMREAD_COLOR);

	const int max_value_H = 360 / 2;
	const int max_value = 255;
	int low_H = 126, low_S = 138, low_V = 120; //흑백으로 변환하는 수치 160. 130
	int high_H = max_value_H, high_S = max_value, high_V = max_value;

	cv::Mat src_hsv, src_hsv_bin;
	cvtColor(src_color, src_hsv, COLOR_BGR2HSV);
	// Detect the object based on HSV Range Values
	inRange(src_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), src_hsv_bin);

    RNG rng(12345);
    vector<vector<Point>> contours; //각 꼭지점 갯수 벡터배열에 저장
    vector<Vec4i> hierarchy;
    findContours(src_hsv_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    Mat drawing = src_color.clone(); // Mat::zeros(src_color.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++) //꼭지점 사이즈만큼 i 반복
    {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int)i, color, 1, LINE_8, hierarchy, 0);
    }

    double max_area = 0; //면적 0부터 시작
    int max_area_index = -1; //면적 0부터 시작
    for (size_t i = 0; i < contours.size(); i++) // contours.size() 사이즈만큼 i번 반복해서 
    {
        double area = contourArea(contours[i]); //전체 면적값
        if (max_area < area)
        {
            max_area = area;
            max_area_index = i;
        }
    }
    if (max_area_index >= 0) //면적 인덱스가 0과 같거나 클시
    {
        drawContours(drawing, contours, (int)max_area_index, CV_RGB(255, 0, 0), CV_FILLED); // 그려주갰다. 꼭지점, 면적 전체 수 인덱스, cv_rgb(255,0,0)(빨간색으로) ,채워넣겠다. 

        double area = contourArea(contours[max_area_index]);
        RotatedRect rrt = minAreaRect(contours[max_area_index]);
        double arcLen = arcLength(contours[max_area_index], true);

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

    }

	return 1;
}