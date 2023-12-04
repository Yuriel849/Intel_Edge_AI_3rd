
#include <iostream>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#pragma comment(lib,"opencv_world481d.lib")
#else	//RELEASE
#pragma comment(lib,"opencv_world481.lib")
#endif
using namespace std;
using namespace cv;
//void main()
int main()
{
    cout << "Hello OpenCV World!\n";
    string fileName = "jetson.bmp";
    Mat img = cv::imread(fileName, IMREAD_GRAYSCALE);
    int width = img.cols;
    int height = img.rows;
    uchar* pData = img.data;
    
    int threshold = 100;

    Mat thrImg;
    cv::threshold(img, thrImg, threshold, 255, THRESH_BINARY);
    //threshold processing
    
    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            int index = row * width + col;
            (pData[index] > threshold) ? pData[index] = 255 : pData[index] = 0;
        }
    }

    return 0;//int ¹ÝÈ¯
}
