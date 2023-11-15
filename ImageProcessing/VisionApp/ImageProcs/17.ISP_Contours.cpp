#pragma once

#include "ISP.h"

int main()
{
	std::string fileName = "../KCCImageNet/stop_img.png";
	cv::Mat src_color = cv::imread(fileName, cv::ImreadModes::IMREAD_COLOR);

	const int max_value_H = 360 / 2;
	const int max_value = 255;
	int low_H = 126, low_S = 138, low_V = 120; //������� ��ȯ�ϴ� ��ġ 160. 130
	int high_H = max_value_H, high_S = max_value, high_V = max_value;

	cv::Mat src_hsv, src_hsv_bin;
	cvtColor(src_color, src_hsv, COLOR_BGR2HSV);
	// Detect the object based on HSV Range Values
	inRange(src_hsv, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), src_hsv_bin);

    RNG rng(12345);
    vector<vector<Point>> contours; //�� ������ ���� ���͹迭�� ����
    vector<Vec4i> hierarchy;
    findContours(src_hsv_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    Mat drawing = src_color.clone(); // Mat::zeros(src_color.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++) //������ �����ŭ i �ݺ�
    {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int)i, color, 1, LINE_8, hierarchy, 0);
    }

    double max_area = 0; //���� 0���� ����
    int max_area_index = -1; //���� 0���� ����
    for (size_t i = 0; i < contours.size(); i++) // contours.size() �����ŭ i�� �ݺ��ؼ� 
    {
        double area = contourArea(contours[i]); //��ü ������
        if (max_area < area)
        {
            max_area = area;
            max_area_index = i;
        }
    }
    if (max_area_index >= 0) //���� �ε����� 0�� ���ų� Ŭ��
    {
        drawContours(drawing, contours, (int)max_area_index, CV_RGB(255, 0, 0), CV_FILLED); // �׷��ְ���. ������, ���� ��ü �� �ε���, cv_rgb(255,0,0)(����������) ,ä���ְڴ�. 

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