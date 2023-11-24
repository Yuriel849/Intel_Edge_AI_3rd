#include "Common.h"

// Identical to function getROIs(const Mat& search_img, const Mat& ptrn_img, vector<Rect>& rois) in "23.ISP_Template_Matching_Img.cpp"
void MatchingMethod(const Mat& serch_img, const Mat& ptrn_img, const double& thres, vector<Rect>& rois)
{
	Mat result = Mat::zeros(Size(serch_img.cols - ptrn_img.cols + 1, serch_img.rows - ptrn_img.rows + 1), CV_32FC1);
	int match_method = TM_CCORR_NORMED;
	matchTemplate(serch_img, ptrn_img, result, match_method);
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;

	bool multiobjects = true;
	if (!multiobjects)
	{
		minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
		{
			matchLoc = minLoc;
		}
		else
		{
			matchLoc = maxLoc;
		}

		rois.push_back(Rect(matchLoc.x, matchLoc.y, ptrn_img.cols, ptrn_img.rows));
	}
	else
	{
		Mat tm_bin;
		double min_thr = thres;
		double max_thr = 1.0;
		cv::threshold(result, tm_bin, min_thr, max_thr, ThresholdTypes::THRESH_BINARY);
		tm_bin *= 255;

		tm_bin.convertTo(tm_bin, CV_8UC1);

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(tm_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

		for (size_t i = 0; i < contours.size(); i++)
		{
			RotatedRect rrt = minAreaRect(contours[i]);
			//rois.push_back(rrt.boundingRect());
			rois.push_back(Rect(rrt.boundingRect().tl().x, rrt.boundingRect().tl().y, ptrn_img.cols, ptrn_img.rows));
		}
	}
}

void main()
{
	bool defectFlag = false;

	std::string filePath_Search = "./res/img/location_black.png";
	std::string filePath_Templt = "./res/img/wafer_template.png";

	cv::Mat src_draw = cv::imread(filePath_Search, cv::ImreadModes::IMREAD_ANYCOLOR);
	cv::Mat src_gray_search = cv::imread(filePath_Search, cv::ImreadModes::IMREAD_GRAYSCALE);
	cv::Mat src_gray_templt = cv::imread(filePath_Templt, cv::ImreadModes::IMREAD_GRAYSCALE);
	cv::Mat src_filled = src_draw.clone();

	double thres = 0.99;
	vector<Rect> finds;
	MatchingMethod(src_gray_search, src_gray_templt, thres, finds);

	for (size_t k = 0; k < finds.size(); k++)
	{
		cv::rectangle(src_draw, finds[k], CV_RGB(255, 0, 0), 1);

		string msg;
		cv::drawMarker(src_draw, finds[k].tl(), CV_RGB(255, 0, 0), MarkerTypes::MARKER_CROSS);
		msg = to_string(k + 1);
		putText(src_draw, msg, finds[k].tl(), FONT_HERSHEY_SIMPLEX, 0.5, CV_RGB(0, 255, 255), 1, 8);

		cv::rectangle(src_filled, finds[k], CV_RGB(0, 205, 255), CV_FILLED);



		cv::Mat src_templt = src_gray_templt.clone();
		cv::Mat src_wafer = src_gray_search(finds[k]).clone();
		cv::Mat src_tBin = cv::Mat::zeros(src_templt.size(), CV_8UC1);	// Empty matrix for binarization
		cv::Mat src_wBin = cv::Mat::zeros(src_wafer.size(), CV_8UC1);	// Empty matrix for binarization

		// For wafer : Mask y-axis 28 - 112
		cv::Mat mask = cv::Mat::zeros(src_wafer.size(), CV_8UC1);
		uchar* mData = mask.data;
		for (size_t row = 0; row < src_wafer.rows; row++)
		{
			for (size_t col = 0; col < src_wafer.cols; col++)
			{
				int index = row * src_wafer.cols + col;
				if (!(28 < row && row < 112)) { mData[index] = 255; }
			}
		}
		cv::Mat src_wMasked = src_wafer & mask;

		// For template : Mask y-axis 24 - 106
		mask = cv::Mat::zeros(src_templt.size(), CV_8UC1);
		mData = mask.data;
		for (size_t row = 0; row < src_templt.rows; row++)
		{
			for (size_t col = 0; col < src_templt.cols; col++)
			{
				int index = row * src_templt.cols + col;
				if (!(24 < row && row < 106)) { mData[index] = 255; }
			}
		}
		cv::Mat src_tMasked = src_templt & mask;

		// Binarization
		thres = 125;
		cv::threshold(src_wMasked, src_wBin, thres, 255, ThresholdTypes::THRESH_BINARY);
		cv::threshold(src_tMasked, src_tBin, thres, 255, ThresholdTypes::THRESH_BINARY);

		int kernelSz = 1;
		int shape = MorphShapes::MORPH_ELLIPSE;
		cv::Size sz = Size(2 * kernelSz + 1, 2 * kernelSz + 1);
		Mat SE = cv::getStructuringElement(shape, sz);

		//Ä§½Ä erode
		cv::Mat src_wErode;
		cv::Mat src_tErode;
		cv::erode(src_wBin, src_wErode, SE);
		cv::erode(src_tBin, src_tErode, SE);
		Mat diff_wErode = src_wBin - src_wErode;
		Mat diff_tErode = src_tBin - src_tErode;

		// Find contours
		vector<vector<Point>> wContours;
		vector<vector<Point>> tContours;
		vector<Vec4i> wHierarchy;
		vector<Vec4i> tHierarchy;
		findContours(src_wErode, wContours, wHierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		findContours(src_tErode, tContours, tHierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		Mat drawing_wafer = src_wafer.clone();
		Mat drawing_templt = src_templt.clone();

		if (wContours.size() == tContours.size())
		{
			for (size_t i = 0; i < wContours.size(); i++)
			{
				//drawContours(drawing, contours, (int)i, 50, 1, LINE_8, hierarchy, 0);
				//drawContours(drawing, contours, (int)i, 50, 1, LINE_8, hierarchy, 0);
				RotatedRect wRrt = minAreaRect(wContours[i]);
				Rect2f wR2f = wRrt.boundingRect2f();
				RotatedRect tRrt = minAreaRect(tContours[i]);
				Rect2f tR2f = tRrt.boundingRect2f();
				// Identify squares with minimum area bounding rectangle
				cv::rectangle(drawing_wafer, wR2f.tl(), wR2f.br(), 0, 1, LINE_8);
				cv::rectangle(drawing_templt, tR2f.tl(), tR2f.br(), 0, 1, LINE_8);

				if (abs(tR2f.area() - wR2f.area()) > 100)
				{
					defectFlag = true;
					break;
				}
			}
		}

		if (defectFlag)
		{
			cv::rectangle(src_filled, finds[k], CV_RGB(255, 0, 100), CV_FILLED);
			defectFlag = false;
		}

	}
	int a = 0;
}