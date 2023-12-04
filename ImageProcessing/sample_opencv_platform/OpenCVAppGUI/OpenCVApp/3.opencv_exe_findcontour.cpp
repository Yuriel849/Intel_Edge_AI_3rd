
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

using namespace cv;
using namespace std;
Mat src_gray;
int thresh = 100;
RNG rng(12345);
void thresh_callback(int, void*);

void thresh_callback(int, void*)
{
    Mat canny_output;
    Canny(src_gray, canny_output, thresh, thresh * 2);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
    }
    
    imshow("Contours", drawing);
}
int main()
{
    cout << "Hello OpenCV World!\n";
    //string fileName = "FindingContours.png";
    string fileName = "jetson.bmp";
    
    Mat src = cv::imread(fileName);
    if (src.empty())
    {
        return -1;
    }
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));
    const char* source_window = "Source";
    namedWindow(source_window, WindowFlags::WINDOW_KEEPRATIO);
    resizeWindow(source_window, 640, 480);
    namedWindow("Contours", WindowFlags::WINDOW_KEEPRATIO);
    resizeWindow("Contours", 640, 480);

    imshow(source_window, src);
    const int max_thresh = 255;
    createTrackbar("Canny thresh:", source_window, &thresh, max_thresh, thresh_callback);
    thresh_callback(0, 0);
    waitKey();
    return 0;
}
