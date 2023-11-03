/*
library include
library link
*/
#include "../Common/Common.h"
#include <filesystem>
namespace fs = std::filesystem;

Point find_loss_center(uchar* img, int loss_y, int w, int minX, int maxX)
{
	int distance = 0;
	int loss_x = 0;
	uchar min = 255;
	for (int x = minX; x <= maxX; x++)
	{
		int index = loss_y * w + x;
		if (img[index] <= min) { min = img[index];  loss_x = x; }
		
	}


	cout << "loss_x : " << loss_x << " loss_y : " << loss_y << endl;
	return Point(loss_x, loss_y);
}


int main()
{
	//image path
	string fileDir = "solar_cell";
	vector<string> filelist;
	int num = 0;

	for (const auto& entry : fs::directory_iterator(fileDir))
	{
		std::cout << entry.path().string() << std::endl;
		filelist.push_back(entry.path().string());
	}

	for (const std::string& filePath : filelist)
	{
		std::cout << filePath << std::endl;
		/*string img_path = "solar_cell/solar_cell_05.png";
		Mat input_img = cv::imread(img_path, cv::ImreadModes::IMREAD_ANYCOLOR);*/
		
		Mat input_img = cv::imread(filePath, cv::ImreadModes::IMREAD_ANYCOLOR);

		Mat grey_img;
		cvtColor(input_img, grey_img, ColorConversionCodes::COLOR_BGR2GRAY);
		uchar* img_data = grey_img.data;
		int w = grey_img.cols;
		int h = grey_img.rows;


		Mat thres_img;
		double thres_min = 180; //180
		double thres_max = 255;
		threshold(grey_img, thres_img, thres_min, thres_max, ThresholdTypes::THRESH_BINARY);


		
		Mat thres_img_inv = ~thres_img;

		/*uchar* img_data = thres_img_inv.data;
		int w = thres_img_inv.cols;
		int h = thres_img_inv.rows;*/

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(thres_img_inv, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

		//cvtColor(thres_img_inv, thres_img_inv, ColorConversionCodes::COLOR_GRAY2BGR);

		int index = 0;

		for (size_t i = 0; i < contours.size(); i++)
		{
			const vector<Point> contour = contours[i];

			// x 좌표 최소값, 최대값 초기화
			int minX = contour[0].x;
			int maxX = contour[0].x;

			// y 좌표 최소값, 최대값 초기화
			int minY = contour[0].y;
			int maxY = contour[0].y;

			int x = 0;
			int y = 0;

			// 컨투어 내의 모든 점에 대해 최소값과 최대값 업데이트
			for (const auto point : contour) {
				x = point.x;
				y = point.y;

				minX = std::min(minX, x);
				maxX = std::max(maxX, x);
				minY = std::min(minY, y);
				maxY = std::max(maxY, y);
			}

			int y_distance = maxY - minY;
			int x_distance = maxX - minX;


			if (x_distance < 200 || y_distance < 22 || y_distance > 42) continue;

			std::cout << "Min X : " << minX << " Min Y : " << minY << " Max X : " << maxX << " MaxY : " << maxY << std::endl;
			std::cout << "Y distance : " << y_distance << std::endl;

			double area = cv::contourArea(contours[i]);
			double length = cv::arcLength(contours[i], false);

			if (length > 3000) continue;



			std::cout << " id : " << i << " index : " << ++index << endl;
			std::cout << " area : " << area << " length : " << length << endl;

			std::string str = std::to_string(index);
			cv::putText(input_img, str, cv::Point(minX, minY), 1, 1, cv::Scalar(255, 255, 255), 1, 1);
			cv::rectangle(input_img, Point(minX, minY), Point(maxX, maxY), Scalar(0, 0, 255), 2);


			int loss_y = minY + y_distance / 2;
			Point center = find_loss_center(img_data, loss_y, w, minX, maxX);
			if (center.x == 0) continue;
			float radius = 10;
			cv::circle(input_img, center, radius, cv::Scalar(0, 255, 0), 2);



			cout << endl;
		}
		std::string filename = "solar_cell_output/output_" + std::to_string(++num) + ".jpg";
		imwrite(filename, input_img);
	}



	int a = 0;
	return 0;
}