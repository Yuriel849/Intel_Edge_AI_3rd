
#include <iostream>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#pragma comment(lib,"opencv_world481d.lib")
#else	//RELEASE
#pragma comment(lib,"opencv_world481.lib")
#endif
using namespace std;
using namespace cv;

int main() {
    // XML 파일 경로
    std::string xmlFile = "metro_calibration_120deg.xml";

    // XML 파일 읽기
    cv::FileStorage fs;
    fs.open(xmlFile, cv::FileStorage::READ);
    if (!fs.isOpened()) {
        std::cerr << "Failed to open XML file." << std::endl;
        return -1;
    }

    // metrology_calibration 루트 노드 접근
    cv::FileNode rootNode = fs["metrology_calibration"];
    if (rootNode.empty()) {
        std::cerr << "Failed to access metrology_calibration." << std::endl;
        fs.release();
        return -1;
    }

    // format_version, format_version_minor, serial_number, revision 읽기
    int formatVersion, formatVersionMinor, serialNumber;
    std::string revision;

    rootNode["format_version"] >> formatVersion;
    rootNode["format_version_minor"] >> formatVersionMinor;
    rootNode["serial_number"] >> serialNumber;
    rootNode["revision"] >> revision;

    // 출력
    std::cout << "Format Version: " << formatVersion << std::endl;
    std::cout << "Format Version Minor: " << formatVersionMinor << std::endl;
    std::cout << "Serial Number: " << serialNumber << std::endl;
    std::cout << "Revision: " << revision << std::endl;

    // set 노드 접근
    cv::FileNode setNode = rootNode["set"];
    if (setNode.empty()) {
        std::cerr << "Failed to access set node." << std::endl;
        fs.release();
        return -1;
    }

    // set 노드의 속성(attribute) 읽기
    std::string date, time;
    double temperature, humidity;

    date = setNode["date"];
    time = setNode["time"];
    setNode["temperature"] >> temperature;
    setNode["humidity"] >> humidity;

    // 출력
    std::cout << "Date: " << date << std::endl;
    std::cout << "Time: " << time << std::endl;
    std::cout << "Temperature: " << temperature << std::endl;
    std::cout << "Humidity: " << humidity << std::endl;

    // camera 노드 접근
    cv::FileNode cameraNode = setNode["camera"];
    if (cameraNode.empty()) {
        std::cerr << "Failed to access camera node." << std::endl;
        fs.release();
        return -1;
    }

    // camera 노드의 속성(attribute) 읽기
    int cameraName;
    cameraName = cameraNode["name"];

    // 출력
    std::cout << "Camera Name: " << cameraName << std::endl;

    // ior 노드 접근
    cv::FileNode iorNode = cameraNode["ior"];
    if (iorNode.empty()) {
        std::cerr << "Failed to access ior node." << std::endl;
        fs.release();
        return -1;
    }

    // ior 노드의 속성(attribute) 읽기
    int iorType;
    iorType = iorNode["type"];

    // 출력
    std::cout << "IOR Type: " << iorType << std::endl;

    // projection 노드 접근
    cv::FileNode projectionNode = iorNode["projection"];
    if (projectionNode.empty()) {
        std::cerr << "Failed to access projection node." << std::endl;
        fs.release();
        return -1;
    }

    // projection 노드의 데이터 읽기
    double c;
    projectionNode["c"] >> c;

    // 출력
    std::cout << "Projection C: " << c << std::endl;

    // distortion 노드 접근
    cv::FileNode distortionNode = iorNode["distortion"];
    if (distortionNode.empty()) {
        std::cerr << "Failed to access distortion node." << std::endl;
        fs.release();
        return -1;
    }

    // distortion 노드의 데이터 읽기
    double a1, a2, a3, b1, b2, c1, c2;
    double ppx, ppy, r0;

    distortionNode["a1"] >> a1;
    distortionNode["a2"] >> a2;
    distortionNode["a3"] >> a3;
    distortionNode["b1"] >> b1;
    distortionNode["b2"] >> b2;
    distortionNode["c1"] >> c1;
    distortionNode["c2"] >> c2;
    distortionNode["ppx"] >> ppx;
    distortionNode["ppy"] >> ppy;
    distortionNode["r0"] >> r0;

    // 출력
    std::cout << "Distortion a1: " << a1 << std::endl;
    std::cout << "Distortion a2: " << a2 << std::endl;
    std::cout << "Distortion a3: " << a3 << std::endl;
    std::cout << "Distortion b1: " << b1 << std::endl;
    std::cout << "Distortion b2: " << b2 << std::endl;
    std::cout << "Distortion c1: " << c1 << std::endl;
    std::cout << "Distortion c2: " << c2 << std::endl;
    std::cout << "Distortion ppx: " << ppx << std::endl;
    std::cout << "Distortion ppy: " << ppy << std::endl;
    std::cout << "Distortion r0: " << r0 << std::endl;

    // sensor 노드 접근
    cv::FileNode sensorNode = iorNode["sensor"];
    if (sensorNode.empty()) {
        std::cerr << "Failed to access sensor node." << std::endl;
        fs.release();
        return -1;
    }

    // sensor 노드의 데이터 읽기
    double esx, esy;
    int ssx, ssy;

    sensorNode["esx"] >> esx;
    sensorNode["esy"] >> esy;
    sensorNode["ssx"] >> ssx;
    sensorNode["ssy"] >> ssy;

    // 출력
    std::cout << "Sensor esx: " << esx << std::endl;
    std::cout << "Sensor esy: " << esy << std::endl;
    std::cout << "Sensor ssx: " << ssx << std::endl;
    std::cout << "Sensor ssy: " << ssy << std::endl;

    fs.release(); // 파일 닫기

    return 0;
}
