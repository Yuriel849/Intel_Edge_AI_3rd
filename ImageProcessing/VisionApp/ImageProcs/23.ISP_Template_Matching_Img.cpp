#include "Common.h"

// Compare the x-values of two Points
bool compare_point(Point lhs, Point rhs) { return lhs.x < rhs.x; }

/* Get Regions of Interest (ROIs)
 *	parameter:search_img : the image to be searched
 *  parameter:ptrn_img  : the template image to be searched for
 *  parameter:rois		: vector of rectangles (Rect) denoting the ROIs
 */
void getROIs(const Mat& search_img, const Mat& ptrn_img, vector<Rect>& rois)
{
	uchar* pSearch = search_img.data;
	int search_w = search_img.cols;
	int search_h = search_img.rows;
	uchar* pPtrn = ptrn_img.data;
	int ptrn_w = ptrn_img.cols;
	int ptrn_h = ptrn_img.rows;

	Mat tm_img = Mat::zeros(Size(search_w - ptrn_w + 1, search_h - ptrn_h + 1), CV_32FC1); // Zero matrix for template matching
	for (size_t row = 0; row < search_h - ptrn_h + 1; row++) // For each row of search_img
	{
		for (size_t col = 0; col < search_w - ptrn_w + 1; col++) // For each column of each row of search_img
		{
			double TM_SQDIFF = 0.0;		   // Square difference
			double TM_SQDIFF_NORMED = 0.0; // Normalized square difference
			for (size_t prow = 0; prow < ptrn_h; prow++) // For each row of ptrn_img
			{
				for (size_t pcol = 0; pcol < ptrn_w; pcol++) // For each column of each row of ptrn_img
				{
					// Check difference between each element of search_img with each element of ptrn_img; if identical images, difference will be zero
					int search_index = (row + prow) * search_w + (col + pcol);
					int ptrn_index = prow * ptrn_w + pcol;

					double diff = pSearch[search_index] - pPtrn[ptrn_index];
					TM_SQDIFF += (diff * diff);
				}
			}
			double ptrnSQ = 0., searchSQ = 0.;
			for (size_t prow = 0; prow < ptrn_h; prow++)
			{
				for (size_t pcol = 0; pcol < ptrn_w; pcol++)
				{
					// Calculate square of values of each element of search_img and ptrn_img, to use in normalizing the square difference (TM_SQDIFF_NORMED)
					int search_index = (row + prow) * search_w + (col + pcol);
					int ptrn_index = prow * ptrn_w + pcol;
					searchSQ += pSearch[search_index] * pSearch[search_index];
					ptrnSQ += pPtrn[ptrn_index] * pPtrn[ptrn_index];
				}
			}

			// If square difference is 0, means the image here is a perfect match for "ptrn_img"
			//matching_img.at<double>(row, col) = TM_SQDIFF;
			//if (TM_SQDIFF == 0)
			//	ptFind.push_back(Point(col, row));

			// Alternative to above: Use TM_SQDIFF_NORMED instead of TM_SQDIFF
			if (ptrnSQ == 0) ptrnSQ = 1;
			TM_SQDIFF_NORMED = TM_SQDIFF / sqrt(ptrnSQ * searchSQ);
			tm_img.at<float>(row, col) = TM_SQDIFF_NORMED;
			//if (TM_SQDIFF_NORMED <= 0.009)
			//	rois.push_back(Rect(col, row, ptrn_w, ptrn_h));
		}
	}
	Mat tm_bin;
	double min_thr = 0.8;
	double max_thr = 1.0;
	cv::threshold(tm_img, tm_bin, min_thr, max_thr, ThresholdTypes::THRESH_BINARY_INV);
	tm_bin *= 255;

	tm_bin.convertTo(tm_bin, CV_8UC1);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(tm_bin, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	for (size_t i = 0; i < contours.size(); i++)
	{
		RotatedRect rrt = minAreaRect(contours[i]);
		rois.push_back(rrt.boundingRect());
		//rois.push_back(Rect(rrt.center.x + offset_x, start_y, w, h));
	}


}

/* Get Regions of Interest (ROIs)
 *	parameter:img  : the image to be searched
 *  parameter:rois : vector of rectangles (Rect) denoting the ROIs
 */
void getROIs(const Mat& img, vector<Rect>& rois)
{
	Mat src_draw;
	cvtColor(img, src_draw, COLOR_GRAY2BGR);
	uchar* pData = img.data;
	int width = img.cols;
	int height = img.rows;

	//int contents_low = 190;
	int contents_up = 210;
	//int upper = 250;

	//get binaray image :: fiducial mark region
	cv::Mat src_bin = Mat::zeros(cv::Size(width, height), CV_8UC1);
	uchar* pDataBin = src_bin.data;
	for (size_t i = 0; i < width * height; i++)
		(pData[i] > contents_up) ? pDataBin[i] = 255 : pDataBin[i] = 0;

	//morphology :: remove noise, refine shape...from src_bin
	int kernelSz = 10;
	int shape = MorphShapes::MORPH_ELLIPSE;
	int type = MorphTypes::MORPH_OPEN;
	cv::Size sz = Size(2 * kernelSz + 1, 2 * kernelSz + 1);
	Mat SE = cv::getStructuringElement(shape, sz);
	Mat src_open;
	cv::morphologyEx(src_bin, src_open, type, SE);

	//input : src_open, binary or edge
	//fucntion : findcontours
	//output : regions
	RNG rng(12345);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(src_open, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	Mat drawing = Mat::zeros(src_open.size(), CV_8UC3);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawContours(drawing, contours, (int)i, color, CV_FILLED);
	}

	//calc : get points of CoG
	vector<Point> objs_center;
	for (size_t i = 0; i < contours.size(); i++)
	{
		double area = contourArea(contours[i]);
		RotatedRect rrt = minAreaRect(contours[i]);
		double arcLen = arcLength(contours[i], true);
		Point tl = rrt.boundingRect().tl();//top-left
		Point br = rrt.boundingRect().br();//bottom-right
		cv::rectangle(drawing, tl, br, CV_RGB(0, 0, 255));//two points
		cv::rectangle(drawing, rrt.boundingRect(), CV_RGB(0, 0, 255));//rectange

		//Center of Gravity
		int sumX = 0;
		int sumY = 0;
		for (size_t k = 0; k < contours[i].size(); k++)
		{
			sumX += contours[i].at(k).x;//Coord_x
			sumY += contours[i].at(k).y;//Coord_y
		}
		/*
			avg Y
			|
		  | | |
		||||||||
		||||||||

		*/
		//
		//
		///////// ... avg X
		///
		//

		Point center = Point(sumX / contours[i].size(), sumY / contours[i].size());
		objs_center.push_back(center);
	}

	for (size_t i = 0; i < objs_center.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
		drawMarker(drawing, objs_center[i], color, MarkerTypes::MARKER_TILTED_CROSS, 50);
	}

	std::sort(objs_center.begin(), objs_center.end(), compare_point); // 2

	//	             x1      x2
	//                       x1      x2
	//                                          x1    x2
	//left :: index [0]     [1]     [2]      ...     [7]

	int offset_x = 20;
	int start_y = 65;//image coord [y0][x0]
	int w = 53;
	int h = 200;
	//vector<Rect> vROIs;
	for (size_t k = 0; k < objs_center.size() - 1; k++)
	{
		//Point p1 = Point(objs_center[k].x + offset_x, start_y);//top_left
		//Point p2 = Point(p1.x + w, h);//bottom_right

		//data
		cv::Rect rt(Point(objs_center[k].x + offset_x, start_y), Point(objs_center[k].x + w, h));
		rois.push_back(rt);

		//display
		cv::rectangle(src_draw, rt, CV_RGB(255, 0, 0), 1);
	}
}

int main()
{
	if (false)
	{
		std::vector<std::string> students = {
	"Student1", "Student2", "Student3", "Student4", "Student5",
	"Student6", "Student7", "Student8", "Student9", "Student10",
	"Student11", "Student12", "Student13", "Student14", "Student15",
	"Student16", "Student17", "Student18", "Student19", "Student20"
		};

		// ���� ������ ���� �õ� ����
		std::random_device rd;
		std::mt19937 gen(rd());

		// ���� ������ ���� ����
		std::uniform_int_distribution<> distribution(0, students.size() - 1);
		int randomIndex = distribution(gen);

		// �������� ���õ� �л� ���
		std::cout << "���õ� �л�: " << students[randomIndex] << std::endl;


		return 1;
	}

	if (false)
	{

		{
			std::string fileName = "../KCCImageNet/images/ampoules/ampoules_01.png"; //�̹��� �ҷ����� �ڵ�
			cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE); //Mat���� src_gray�� Ŭ������ ���Ӱ� ���� �̹����� �о���δ�.

			Mat drawing;
			uchar* pData = src_gray.data;
			int widht = src_gray.cols;
			int height = src_gray.rows;
			int channels = src_gray.channels();

			if (channels == 3)
				drawing = src_gray.clone();
			else                              //gray �װԾƴϸ� ����̶�� 
				cvtColor(src_gray, drawing, COLOR_GRAY2BGR);

			// ����ȭ�۾� �κ�
			//�и�..segmentation 
			Mat src_bin;
			double thres = 200;
			cv::threshold(src_gray, src_bin, thres, 255, ThresholdTypes::THRESH_BINARY);

			//morpology ������ ���� �κ�

			int kernelSz = 4; // stucturing element
			int shape = MorphShapes::MORPH_ELLIPSE;
			cv::Size sz = Size(2 * kernelSz + 1, 2 * kernelSz + 1);
			Mat SE = cv::getStructuringElement(shape, sz);
			Mat src_open, src_close;
			int type = MorphTypes::MORPH_OPEN;
			cv::morphologyEx(src_bin, src_open, type, SE);
			type = MorphTypes::MORPH_CLOSE;
			cv::morphologyEx(src_open, src_close, type, SE);



			vector<vector<Point> > contours, contour_a; //��ü ��ü ������ ���� �����ͷ� ���� ���ο� ����
			vector<Vec4i> hierarchy;
			findContours(src_close, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);  // src_close_a���� contours ���� Ȯ��.

			RNG rng(12345);


			for (size_t i = 0; i < contours.size(); i++)  // ��ü contours�� ������ �׸��� ���� for��
			{
				double area = contourArea(contours[i]);
				if (area > 3000)
				{
					contour_a.push_back(contours[i]);

					Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
					drawContours(drawing, contours, (int)i, color, CV_FILLED);


				}
			}

			vector<Point> middle, rec_left_top;
			for (size_t i = 0; i < contour_a.size(); i++)
			{
				int sum_x = 0;
				int sum_y = 0;
				for (size_t a = 0; a < contour_a[i].size(); a++)
				{
					sum_x += contour_a[i].at(a).x;
					sum_y += contour_a[i].at(a).y;
				}
				int avg_x = sum_x / contour_a[i].size(); // �߽����� ��� x���� ���, ��� y���� ���
				int avg_y = sum_y / contour_a[i].size();
				middle.push_back(Point(avg_x, avg_y)); // Point �����ڷ� ������� x, y���� �����ϸ鼭 '��ü'�� �����Ѵ�.
			}


			// middle ���
			// ���� ���� �簢���� �»���� ã��.

			//���� 25 ���� 110�� �簢�� ������ ã��. -50 -200
			for (size_t k = 0; k < contour_a.size(); k++)
			{
				rec_left_top.push_back(Point(middle[k].x - 50, middle[k].y - 200));

			}

			vector<Point> liquid_line_points_vector;
			for (size_t q = 0; q < rec_left_top.size(); q++)
			{
				int w = 30;
				int h = 100;
				if (rec_left_top[q].x < 0) continue;
				if (rec_left_top[q].y < 0) continue;
				if (rec_left_top[q].x + w > src_gray.cols) continue;
				if (rec_left_top[q].y + h > src_gray.rows) continue;
				cv::rectangle(drawing, Rect(rec_left_top[q].x, rec_left_top[q].y, w, h), CV_RGB(255, 0, 0), 1);
				Mat ROI = src_gray(Rect(rec_left_top[q].x, rec_left_top[q].y, w, h)).clone(); // Ŭ���� ���� ���� ����ü�� �����.
				equalizeHist(ROI, ROI); // ������׷� ��Ȱȭ - ROI������ �� ��� �۾Ƽ�, ���� ��� ũ�� ���ֱ� ����
				// ���ɿ��� Region of Interest
				vector<int> sum_of_row_vector;
				for (size_t row = 0; row < ROI.rows; row++)
				{
					int sum_of_row = 0;
					for (size_t col = 0; col < ROI.cols; col++)
					{
						int index = row * ROI.cols + col;
						sum_of_row += ROI.data[index];
					}
					sum_of_row_vector.push_back(sum_of_row);
				}

				vector<int> diffs;
				for (size_t i = 0; i < sum_of_row_vector.size() - 1; i++)
				{
					int diff = abs(sum_of_row_vector[i] - sum_of_row_vector[i + 1]);
					diffs.push_back(diff);
				}
				int index_of_line = max_element(diffs.begin(), diffs.end()) - diffs.begin();
				//auto index_of_line = std::max_element(diffs.begin(), diffs.end())- diffs.begin();
				//int detected_line = *index_of_line;
				Point liquid_line_point = cv::Point(rec_left_top[q].x, rec_left_top[q].y + index_of_line);
				liquid_line_points_vector.push_back(liquid_line_point);
			}

			int rec_count = 0;
			for (size_t i = 0; i < liquid_line_points_vector.size(); i++)
			{
				line(drawing, liquid_line_points_vector[i], Point(liquid_line_points_vector[i].x + 25,
					liquid_line_points_vector[i].y), Scalar(0, 0, 255), 1); // �� ��ǥ�� ���� �׾��.
				if (liquid_line_points_vector[i].y > 130)
				{
					std::cout << "�ڿ���" << i + 1 << "�� �ҷ� " << std::endl;
					rec_count++;
				}
			}
			std::cout << "��" << rec_count << "�� " << "�ҷ� ����" << std::endl;


			return 1;

		}

		return 1;
	}




	int img_counts = 8;

	std::string fileName_ptrn = "../KCCImageNet/images/ampoules/ampoules_ptrn.jpg";

	cv::Mat src_gray_ptrn = cv::imread(fileName_ptrn, cv::ImreadModes::IMREAD_GRAYSCALE);

	for (size_t img_index = 1; img_index <= img_counts; img_index++)
	{
		//std::string fileName = "../KCCImageNet/images/ampoules/ampoules_05.png";
		std::string fileName = "../KCCImageNet/images/ampoules/ampoules_" + std::format("{:02d}.png", img_index);

		cv::Mat src_gray = cv::imread(fileName, cv::ImreadModes::IMREAD_GRAYSCALE);
		Mat src_draw;
		cvtColor(src_gray, src_draw, COLOR_GRAY2BGR);

		uchar* pData = src_gray.data;
		size_t width = src_gray.cols;
		size_t height = src_gray.rows;


		//���ؼ�
		int spec_min_y = 80;
		int spec_max_y = 130;

		Point ptSpecLine_TopL = Point(0, spec_min_y);//y = 80
		Point ptSpecLine_TopR = Point(width - 1, spec_min_y);//y = 80
		Point ptSpecLine_BtmL = Point(0, spec_max_y);//y = 130
		Point ptSpecLine_BtmR = Point(width - 1, spec_max_y);//y = 130


		Scalar alert_color(255, 0, 0);
		cv::line(src_draw, ptSpecLine_BtmL, ptSpecLine_BtmR, alert_color, 1);//����
		cv::line(src_draw, ptSpecLine_TopL, ptSpecLine_TopR, alert_color, 1);//�ִ�

		//priority choi
		std::vector<Rect> vROIs;
		getROIs(src_gray, vROIs);
		//for (size_t k = 0; k < vROIs.size() - 1; k++)
		//{
		//	cv::rectangle(src_draw, vROIs[k], CV_RGB(255, 0, 0), 1);
		//}


		std::vector<Rect> vROIs_TM;
		{
			Mat edge_search;
			Mat edge_ptrn;

			Mat mag;// = Mat::zeros(src_gray.size(), CV_16S);
			Mat dx, dy;
			Sobel(src_gray, dx, CV_32FC1, 1, 0);
			Sobel(src_gray, dy, CV_32FC1, 0, 1);
			magnitude(dx, dy, mag);
			mag.convertTo(mag, CV_8UC1);
			edge_search = mag >= 80;

			Sobel(src_gray_ptrn, dx, CV_32FC1, 1, 0);
			Sobel(src_gray_ptrn, dy, CV_32FC1, 0, 1);
			magnitude(dx, dy, mag);
			mag.convertTo(mag, CV_8UC1);
			edge_ptrn = mag >= 80;

			getROIs(edge_search, edge_ptrn, vROIs_TM);


			//user define - re-fined coord
			int offset_x = 5;
			int start_y = 65;//image coord [y0][x0]
			int w = 45;
			int h = 140;

			for (size_t i = 0; i < vROIs_TM.size(); i++)
			{
				vROIs_TM[i].x += offset_x;
				vROIs_TM[i].y = start_y;
				vROIs_TM[i].width = w;
				vROIs_TM[i].height = h;
			}

		}


		for (size_t k = 0; k < vROIs_TM.size(); k++)
		{
			cv::rectangle(src_draw, vROIs_TM[k], CV_RGB(255, 0, 0), 1);
		}


		//algorithm start
		//low-contrast =? >>> histogram eq ->>> high constrast
		Mat src_gray_Eq;
		cv::equalizeHist(src_gray, src_gray_Eq);
		//src_gray : image full size
		//src_gray_Eq : image full size

		//local area...sub image 
		//coord_x,y = (0,0)
		//coord_w,y = (vROIs[k].w, vROIs[k].h)
		for (size_t k = 0; k < vROIs.size(); k++)
		{
			int detected_Y_line = 0;//image full size Y

			Mat subImg = src_gray_Eq(vROIs[k]).clone();//image local size
			//subImg size ... 0,0, w, h

			Rect tempR = vROIs[k];
			// Rect ������ ��ǥ ã��
			vector<int> accumulated_horizontal;

			//coord_x,y = (0,0)
			//coord_w,y = (vROIs[k].w, vROIs[k].h)
			//projection : --->accumulated_horizontal[0]   ===========
			//projection : --->accumulated_horizontal[1]   =============
			//projection : --->                            ===============
			//projection : --->                            ================================
			//projection : --->                            ================================
			//projection : --->accumulated_horizontal[y-1] ================================
			for (int y = 0; y < vROIs[k].height; ++y) {
				int sum_line = 0;
				for (int x = 0; x < vROIs[k].width; ++x) {
					Point p = Point(x, y);
					sum_line += subImg.at<uchar>(p.y, p.x); //�� �� ���� �ִ� ���� �� ���ϱ� 
				}
				accumulated_horizontal.push_back(sum_line);
				//if (result_line < sum_line)
				//{
				//	result_line = sum_line;
				//	line(src_draw, Point(0, result_line), Point(639, result_line), Scalar(0, 125, 0), 1);
				//}
			}

			//1�� �̺� ���� �̿��� ū ��ȭ�� ��ġ(index) ���ϱ�
			vector<int> grads;
			for (size_t i = 1; i < accumulated_horizontal.size(); i++)//
			{
				int pre = accumulated_horizontal[i - 1];
				int cur = accumulated_horizontal[i];
				//1�� �̺�
				int diff = std::abs(cur - pre);
				grads.push_back(diff);

			}

			int max_index = 0;
			int max_value = 0;
			for (size_t i = 0; i < grads.size(); i++)//
			{
				if (max_value < grads[i])
				{
					max_value = grads[i];
					max_index = i;
				}
			}

			//full(global)  =  local   +  full(global)
			detected_Y_line = max_index + vROIs[k].y;

			Scalar judge_color(0, 255, 0);
			Scalar judge_color_OK(0, 255, 0);
			Scalar judge_color_NG(0, 0, 255);
			Point detected_pt1 = Point(vROIs[k].x, detected_Y_line);
			Point detected_pt2 = Point(vROIs[k].x + vROIs[k].width, detected_Y_line);
			//judge display OK vs NG
			string msg = "";
			if (spec_min_y <= detected_Y_line && detected_Y_line <= spec_max_y)
			{
				line(src_draw, detected_pt1, detected_pt2, judge_color_OK, 1);//����
				msg = "OK";
				judge_color = judge_color_OK;
			}
			else
			{
				line(src_draw, detected_pt1, detected_pt2, judge_color_NG, 1);//����
				msg = "NG";
				judge_color = judge_color_NG;
			}
			putText(src_draw, msg, Point(vROIs[k].x, vROIs[k].y), FONT_HERSHEY_SIMPLEX, 0.8, judge_color, 1, 8);
		}

		int a = 0;
	}
	//line(src_draw, Point(0, result_line), Point(639, result_line), Scalar(255, 165, 0), 1);

	return 1;
}