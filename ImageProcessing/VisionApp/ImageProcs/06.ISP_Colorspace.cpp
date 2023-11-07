#pragma once
#include "Common.h"
using namespace std;

int i, cou;
string curNum;

int main()
{
    std::string flieName = "../thirdparty/opencv_480/sources/samples/data/lena.jpg";
    cv::Mat src = cv::imread(flieName, cv::ImreadModes::IMREAD_ANYCOLOR);

    uchar* pData = src.data; //data array
    int length = src.total(); //data length
    int channels = src.channels();   //채널 5개

    cv::Mat src_Y = cv::Mat(src.rows, src.cols, CV_8UC1); //행 열 /의 값을 받아옴 
    cv::Mat src_Cb = cv::Mat(src.rows, src.cols, CV_8UC1);
    cv::Mat src_Cr = cv::Mat(src.rows, src.cols, CV_8UC1);

    cv::Mat src_New = cv::Mat(src.rows, src.cols, CV_8UC3);
    //
    for (size_t row = 0; row < src.rows; row++)
    {
        for (size_t col = 0; col < src.cols; col++)
        {
            int index = (row)*src.cols + (col);//

            if (channels == 3) //컬러 이미지는 3개의 채널을 가지며 흑백은 1개의 채널을 가짐 
            {                 //이미지가 컬러이미지인지 확인하는 조건
                int index_B = index * channels + 0; //(row)*src.cols * 3 + (col + 0);3개의 채널을 나타내기 위한 픽셀내 위치값 0
                int index_G = index * channels + 1; //(row)*src.cols * 3 + (col + 1);3개의 채널을 나타내기 위한 픽셀내 위치값 0
                int index_R = index * channels + 2; //(row)*src.cols * 3 + (col + 2);3개의 채널을 나타내기 위한 픽셀내 위치값 0
                int val_B = pData[index_B];
                int val_G = pData[index_G];
                int val_R = pData[index_R];

                int val_Y = 0.299 * val_R + 0.587 * val_G + 0.114 * val_B;//
                int val_Cb = -0.169 * val_R - 0.331 * val_G + 0.500 * val_B;//
                int val_Cr = 0.500 * val_R - 0.419 * val_G - 0.0813 * val_B;//

                int val__R = 1.000 * val_Y + 1.402 * val_Cr + 0.0000 * val_Cb;
                int val__G = 1.000 * val_Y - 0.714 * val_Cr - 0.344 * val_Cb;
                int val__B = 1.000 * val_Y + 0.000 * val_Cr + 1.772 * val_Cb;

                src_Y.data[index] = (uchar)val_Y;



                src_Cb.data[index] = (uchar)val_Cb;
                src_Cr.data[index] = (uchar)val_Cr;


                src_New.data[index_B] = (uchar)val__B;
                src_New.data[index_G] = (uchar)val__G;
                src_New.data[index_R] = (uchar)val__R;
            }
            else
            {
                src_Y.data[index] = src.data[index];
                src_Cb.data[index] = src.data[index];
                src_Cr.data[index] = src.data[index];
            }
        }
    }
    return 1;