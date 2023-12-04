
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
    // XML ���� ���
    std::string xmlFile = "metro_calibration_120deg.xml";

    // XML ���� �б�
    cv::FileStorage fs;
    fs.open(xmlFile, cv::FileStorage::READ);
    if (!fs.isOpened()) {
        std::cerr << "Failed to open XML file." << std::endl;
        return -1;
    }

    // metrology_calibration ��Ʈ ��� ����
    cv::FileNode rootNode = fs["metrology_calibration"];
    if (rootNode.empty()) {
        std::cerr << "Failed to access metrology_calibration." << std::endl;
        fs.release();
        return -1;
    }

    // format_version, format_version_minor, serial_number, revision �б�
    int formatVersion, formatVersionMinor, serialNumber;
    std::string revision;

    rootNode["format_version"] >> formatVersion;
    rootNode["format_version_minor"] >> formatVersionMinor;
    rootNode["serial_number"] >> serialNumber;
    rootNode["revision"] >> revision;

    // ���
    std::cout << "Format Version: " << formatVersion << std::endl;
    std::cout << "Format Version Minor: " << formatVersionMinor << std::endl;
    std::cout << "Serial Number: " << serialNumber << std::endl;
    std::cout << "Revision: " << revision << std::endl;

    // set ��� ����
    cv::FileNode setNode = rootNode["set"];
    if (setNode.empty()) {
        std::cerr << "Failed to access set node." << std::endl;
        fs.release();
        return -1;
    }

    // set ����� �Ӽ�(attribute) �б�
    std::string date, time;
    double temperature, humidity;

    date = setNode["date"];
    time = setNode["time"];
    setNode["temperature"] >> temperature;
    setNode["humidity"] >> humidity;

    // ���
    std::cout << "Date: " << date << std::endl;
    std::cout << "Time: " << time << std::endl;
    std::cout << "Temperature: " << temperature << std::endl;
    std::cout << "Humidity: " << humidity << std::endl;

    // camera ��� ����
    cv::FileNode cameraNode = setNode["camera"];
    if (cameraNode.empty()) {
        std::cerr << "Failed to access camera node." << std::endl;
        fs.release();
        return -1;
    }

    // camera ����� �Ӽ�(attribute) �б�
    int cameraName;
    cameraName = cameraNode["name"];

    // ���
    std::cout << "Camera Name: " << cameraName << std::endl;

    // ior ��� ����
    cv::FileNode iorNode = cameraNode["ior"];
    if (iorNode.empty()) {
        std::cerr << "Failed to access ior node." << std::endl;
        fs.release();
        return -1;
    }

    // ior ����� �Ӽ�(attribute) �б�
    int iorType;
    iorType = iorNode["type"];

    // ���
    std::cout << "IOR Type: " << iorType << std::endl;

    // projection ��� ����
    cv::FileNode projectionNode = iorNode["projection"];
    if (projectionNode.empty()) {
        std::cerr << "Failed to access projection node." << std::endl;
        fs.release();
        return -1;
    }

    // projection ����� ������ �б�
    double c;
    projectionNode["c"] >> c;

    // ���
    std::cout << "Projection C: " << c << std::endl;

    // distortion ��� ����
    cv::FileNode distortionNode = iorNode["distortion"];
    if (distortionNode.empty()) {
        std::cerr << "Failed to access distortion node." << std::endl;
        fs.release();
        return -1;
    }

    // distortion ����� ������ �б�
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

    // ���
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

    // sensor ��� ����
    cv::FileNode sensorNode = iorNode["sensor"];
    if (sensorNode.empty()) {
        std::cerr << "Failed to access sensor node." << std::endl;
        fs.release();
        return -1;
    }

    // sensor ����� ������ �б�
    double esx, esy;
    int ssx, ssy;

    sensorNode["esx"] >> esx;
    sensorNode["esy"] >> esy;
    sensorNode["ssx"] >> ssx;
    sensorNode["ssy"] >> ssy;

    // ���
    std::cout << "Sensor esx: " << esx << std::endl;
    std::cout << "Sensor esy: " << esy << std::endl;
    std::cout << "Sensor ssx: " << ssx << std::endl;
    std::cout << "Sensor ssy: " << ssy << std::endl;

    fs.release(); // ���� �ݱ�

    return 0;
}
