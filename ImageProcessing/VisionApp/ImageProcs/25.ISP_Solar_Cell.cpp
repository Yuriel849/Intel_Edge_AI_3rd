#include "Common.h"

void main()
{
	// File path to solar cell image (1 of 6)
	std::string filePath = "../KCCImageNet/solar_cell/solar_cell_03.png";

	cv::Mat src_draw = cv::imread(filePath, cv::ImreadModes::IMREAD_ANYCOLOR);  // Color image of solar cell
	cv::Mat src_gray = cv::imread(filePath, cv::ImreadModes::IMREAD_GRAYSCALE); // Grayscale image of solar cell
	cv::Mat src_bin = cv::Mat::zeros(src_gray.size(), CV_8UC1);					// Empty matrix for binarization of same size as solar cell

	// Binarization
	int thres = 200;
	cv::threshold(src_gray, src_bin, thres, 255, ThresholdTypes::THRESH_BINARY);

	// Dilate
	int kernelSz = 2;
	int shape = MorphShapes::MORPH_ELLIPSE;
	//int type = MorphTypes::MORPH_CLOSE;
	cv::Size sz = Size(2 * kernelSz + 1, 2 * kernelSz + 1);
	cv::Mat SE = cv::getStructuringElement(shape, sz);
	cv::Mat src_dilate;
	cv::dilate(src_bin, src_dilate, SE);
	//cv::morphologyEx(src_bin, src_dilate, type, SE);
	cv::Mat diff_dilate = src_dilate - src_bin;

	vector<Point2i> brokenFinger;

	uchar* binData = src_bin.data;
	int bin_rows = src_bin.rows;
	int bin_cols = src_bin.cols;
	for (size_t row = 0; row < bin_rows; row++)
	{
		for (size_t col = 0; col < bin_cols; col++)
		{
			size_t idx = row * bin_cols + col;

			// 좌우로 7칸씩 검색
			for (size_t lr = 1; lr < 8; lr++)
			{
				/* O		   O
				 * O		   O
				 * O X X T X X O
				 * O		   O
				 * O		   O
				 * 
				 * 좌우로 한 칸씩 이동하여 검색을 하면서,
				 * 좌우 각 칸에서 위아래로 두 칸까지 모두 하얀색인데
				 * 현 위치가 검은색이면 FINGER 끊어진 부분으로 정의
				 */
				if (0 <= (idx - lr) && (idx + lr) < bin_cols && 0 < (row - 2) && (row + 2) < bin_rows)
				{
					if ((binData[idx] == 0)&&
						(binData[idx - lr] == 255) &&
						(binData[(row - 1) * bin_cols + col - lr] == 255) &&
						(binData[(row - 2) * bin_cols + col - lr] == 255) &&
						(binData[(row + 1) * bin_cols + col - lr] == 255) &&
						(binData[(row + 2) * bin_cols + col - lr] == 255) &&
						(binData[idx + lr] == 255) &&
						(binData[(row - 1) * bin_cols + col + lr] == 255) &&
						(binData[(row - 2) * bin_cols + col + lr] == 255) &&
						(binData[(row + 1) * bin_cols + col + lr] == 255)&&
						(binData[(row + 2) * bin_cols + col + lr] == 255))
					{
						brokenFinger.push_back(Point2d(row, col));
						break;
					}
				}
			}
		}
	}

	for (size_t i = 0; i < brokenFinger.size(); i++)
	{
		cv::drawMarker(src_draw, brokenFinger.at(i), CV_RGB(255, 0, 0), MarkerTypes::MARKER_SQUARE);
	}
	
	//for (size_t k = 0; k < finds.size(); k++)
	//{
	//	cv::rectangle(src_draw, finds[k], CV_RGB(255, 0, 0), 1);

	//	string msg;
	//	cv::drawMarker(src_draw, finds[k].tl(), CV_RGB(255, 0, 0), MarkerTypes::MARKER_CROSS);
	//	msg = to_string(k + 1);
	//	putText(src_draw, msg, finds[k].tl(), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(10, 0, 10), 1, 8);

	//}

	int a = 0; // Anchor for breakpoint
}