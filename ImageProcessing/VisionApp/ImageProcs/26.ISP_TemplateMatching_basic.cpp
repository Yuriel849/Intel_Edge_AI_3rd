#include "Common.h"

void main()
{
	Mat img = imread("../KCCImageNet/images/ampoules/ampoules_02.png", IMREAD_COLOR);
	Mat templ = imread("../KCCImageNet/images/ampoules/ampoules_ptrn.jpg", IMREAD_COLOR);

	if (img.empty() || templ.empty())
	{
		cerr << "Image load failed!" << endl;
		return;
	}

	img = img + Scalar(50, 50, 50); // 영상 밝기를 +50 증가

	Mat noise(img.size(), CV_32SC3);
	randn(noise, 0, 10);
	add(img, noise, img, Mat(), CV_8UC3);

	Mat res, res_norm;
	matchTemplate(img, templ, res, TM_CCOEFF_NORMED);
	normalize(res, res_norm, 0, 255, NORM_MINMAX, CV_8U);

	double maxv;
	Point maxloc;
	minMaxLoc(res, 0, &maxv, 0, &maxloc);
	cout << "maxv: " << maxv << endl;

	rectangle(img, Rect(maxloc.x, maxloc.y, templ.cols, templ.rows), Scalar(0, 0, 255), 2);

	int a = 0; // Anchor for breakpoint
}