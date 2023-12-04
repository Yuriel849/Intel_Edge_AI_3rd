
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
    int channel = img.channels();
    //mask processing
    int mask_width = 50; int mask_height = 50;
    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            int index = row * width + col;
            if (channel == 3) index *= 3;
            if (row >= 0 && row < mask_height) {
                if (col >= 0 && col < mask_width) {
                    pData[index] = 255;
                    if (channel == 3) 
                        pData[index+1] = pData[index+2] = 255;
                }
            }

            if (row >= 0 && row < mask_height) {
                if (col >= width-mask_width && col < width) {
                    pData[index] = 255;
                    if (channel == 3) pData[index + 1] = pData[index + 2] = 255;
                }
            }

            if (row >= height - mask_height && row < height) {
                if (col >= 0 && col < mask_width) {
                    pData[index] = 255;
                    if (channel == 3) pData[index + 1] = pData[index + 2] = 255;
                }
            }

            if (row >= height-mask_height && row < height) {
                if (col >= width - mask_width && col < width) {
                    pData[index] = 255;
                    if (channel == 3) pData[index + 1] = pData[index + 2] = 255;
                }
            }
            
        }
    }
    return 0;//int ¹ÝÈ¯
}
