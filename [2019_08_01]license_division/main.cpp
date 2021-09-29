//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <opencv2/xphoto/white_balance.hpp>
//#include <string>
////#include<Windows.h>
//#include<vector>
////#include <boost/filesystem.hpp>
//#include <experimental/filesystem>
//#include <typeinfo>
//#include <map>
//#include <math.h>
#include "Division_license.h"
//#define PI  3.14159265358979323846
//#define PI  3.141592653
//
//using namespace std;
//using namespace cv;
//namespace fs = experimental::filesystem;
//
//
//void bubble_sort(vector < map<string, Point_<int>> >& cnt, int n) {
//	int i, j;
//	map<string, Point_<int>> temp;
//	// ������ E
//	//const int E = 40;
//
//	/*const double WIDTH_DIFF = 0.7;
//	const double MAX_AREA_DIFF = 1.3;
//	const double MIN_AREA_DIFF = 0.7;*/
//
//
//	for (i = n - 1; i > 0; i--) {
//		// 0 ~ (i-1)���� �ݺ�
//		for (j = 0; j < i; j++) {
//			//double area_ratio = ((cnt[j]["br"] - cnt[j]["tl"]).x * (cnt[j]["br"] - cnt[j]["tl"]).y) / ((cnt[j + 1]["br"] - cnt[j + 1]["tl"]).x * (cnt[j + 1]["br"] - cnt[j + 1]["tl"]).y);
//			// j��°�� j+1��°�� ��Ұ� ũ�� ���� �ƴϸ� ��ȯ
//			if (
//				//�� ���� ���̿� ���� �簢���� �»�� ���������� �Ÿ� �� (������ �簢������ ����)
//				//cnt[j]["br"].x - cnt[j]["tl"].x > cnt[j+1]["tl"].x - cnt[j]["br"].x
//				// x, y��ǥ ��ġ
//				//&&
//				cnt[j]["tl"].x > cnt[j + 1]["tl"].x
//				// ����ũ�� ������������
//				/*&&
//				(
//					area_ratio <= MAX_AREA_DIFF
//					&&
//					area_ratio >= MIN_AREA_DIFF
//				)*/
//				//&& cnt[j]["cxy"].y > cnt[j+1]["cxy"].y
//				)
//			{
//				temp = cnt[j];
//				cnt[j] = cnt[j + 1];
//				cnt[j + 1] = temp;
//			}
//
//		}
//
//	}
//
//}
//
//static map<string, Mat> insert2map(string path) {
//	map<string, Mat> imgs_color;
//
//	for (auto&& x : fs::recursive_directory_iterator(path)) {
//		//cout << x.path().extension() << endl;
//		if (x.path().extension() == ".jpg" || x.path().extension() == ".JPG") {
//			/*cout << x.path().generic_string() << endl;
//			cout << x.path().stem().generic_string() << endl;*/
//			imgs_color.insert(pair<string, Mat>(x.path().stem().generic_string(), imread(x.path().generic_string(), IMREAD_COLOR)));
//		}
//		//x.path().extension() == ".jpg" || x.path().extension() == ".JPG" ? cout << x.path().generic_string << endl : cout << endl;
//	}
//	cout << "input done" << endl;
//	return imgs_color;
//}
//
//void convert2gray_test(Mat& imgs_gray) {
//	if (imgs_gray.size().width >= 2000) {
//		resize(imgs_gray, imgs_gray, Size(imgs_gray.size() / 2), 0, 0, INTER_AREA);
//	}
//	cvtColor(imgs_gray, imgs_gray, COLOR_RGB2GRAY);
//	GaussianBlur(imgs_gray, imgs_gray, Size(5, 5), 0);
//	Canny(imgs_gray, imgs_gray, 100, 150);
//
//	cout << "cvt2gray, gaussian blur, canny, resize done" << endl;
//}
//
//void convert2gray(map<string, Mat>& imgs_gray) {
//	map<string, Mat>::iterator iter;
//	for (iter = imgs_gray.begin(); iter != imgs_gray.end(); iter++) {
//		//���� ���� �Ÿ� ����. 
//		if (imgs_gray[iter->first].size().width >= 2000) {
//			resize(imgs_gray[iter->first], imgs_gray[iter->first], Size(imgs_gray[iter->first].size() / 2), 0, 0, INTER_AREA);
//		}
//		cvtColor(imgs_gray[iter->first], imgs_gray[iter->first], COLOR_RGB2GRAY);
//		GaussianBlur(imgs_gray[iter->first], imgs_gray[iter->first], Size(5, 5), 0);
//		Canny(imgs_gray[iter->first], imgs_gray[iter->first], 100, 150);
//	}
//	cout << "cvt2gray, gaussian blur, canny, resize done" << endl;
//}
//
//// ���� �̹��� �ϳ��ϳ� �ذ��ϴ� �ɷ� �ϰ� ���� �Լ����� for�� �����°� �ξ� ������ ����.
//vector < map<string, Point_<int> > > find_img_contour(Mat& imgs_canny) {
//	const int MIN_AREA = 280;
//	const int MIN_WIDTH = 4;
//	const int MIN_HEIGHT = 7;
//	const double MIN_RATIO = 0.35;
//	const double MAX_RATIO = 0.85;
//
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierarchy;
//
//	//map <string, Point_<int>> cnt;
//	//vector < map<string, Point_<int>> > cnt;
//
//	Scalar color = (255, 0, 0);
//	// ������ ã�� ��, ���� �׸� Mat Ŭ���� ����
//	findContours(imgs_canny, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
//
//	vector <Rect> boundRect(contours.size());
//	vector<vector<Point>> approx(contours.size());
//	//Mat drawing = Mat::zeros(imgs_canny.size(), CV_8UC3);
//	double epsilon;
//	//cout << "124 line" << endl;
//	// �ѷ��� ���̿��� 0.1�� ����, approxPolyDP �̿�.
//	for (int i = 0; i < contours.size(); i++) {
//		epsilon = 0.1 * arcLength(contours[i], true);
//		approxPolyDP(contours[i], approx[i], epsilon, true);
//		boundRect[i] = boundingRect(approx[i]);
//	}
//	//cout << "131 line" << endl;
//	vector < map<string, Point_<int> > > cnt;
//	double ratio;
//	double area;
//	// ���� ũ��, ����, ���� ����, ���� ������ �̿��Ͽ� �簢�� �ɷ�����
//	for (int i = 0; i < contours.size(); i++) {
//		area = (double)boundRect[i].height * boundRect[i].width;
//		ratio = (double)boundRect[i].width / boundRect[i].height;
//
//		if (area > MIN_AREA
//			&& boundRect[i].height > MIN_HEIGHT
//			&& boundRect[i].width > MIN_WIDTH
//			&& MIN_RATIO < ratio
//			&& ratio < MAX_RATIO
//			)
//		{
//			//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 1, LINE_8, 0);
//			map<string, Point_<int> > tocnt;
//			tocnt.insert(pair<string, Point_<int>>("tl", boundRect[i].tl()));
//			tocnt.insert(pair<string, Point_<int>>("br", boundRect[i].br()));
//			tocnt.insert(pair<string, Point_<int>>("cxy", (boundRect[i].tl() + (boundRect[i].br() - boundRect[i].tl()) / 2)));
//			cnt.push_back(tocnt);
//		}
//
//	}
//	// �߽����� x ��ǥ �������� ����
//	bubble_sort(cnt, (int)cnt.size());
//	return cnt;
//
//}
//
//void draw_img_contour2(map<string, Mat>& imgs_gray) {
//	double epsilon;
//	double ratio;
//	double area;
//	const int MIN_AREA = 280;
//	const int MIN_WIDTH = 4;
//	const int MIN_HEIGHT = 7;
//	const double MIN_RATIO = 0.35;
//	const double MAX_RATIO = 0.85;
//
//	map <string, Mat>::iterator iter;
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierarchy;
//
//	Mat drawing;
//
//	vector <Rect> boundRect(contours.size());
//	vector<vector<Point>> approx(contours.size());
//
//	//map <string, Point_<int>> cnt;
//	//vector < map<string, Point_<int>> > cnt;
//
//	Scalar color = (255, 0, 0);
//
//	// �̹��� �� ó��, ĳ�� ���� ���� �� contour ã�� �� �׸�.
//	for (iter = imgs_gray.begin(); iter != imgs_gray.end(); iter++) {
//		// ����þ� �� ����, ĳ�� ���� ����, ������ ã��
//		GaussianBlur(imgs_gray[iter->first], imgs_gray[iter->first], Size(5, 5), 0);
//		Canny(imgs_gray[iter->first], imgs_gray[iter->first], 100, 150);
//		findContours(imgs_gray[iter->first], contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
//
//		// ���� �׸� Mat Ŭ���� ����
//		drawing = Mat::zeros(imgs_gray[iter->first].size(), CV_8UC3);
//
//		// �ѷ��� ���̿��� 0.1�� ����, approxPolyDP �̿�.
//		for (int i = 0; i < contours.size(); i++) {
//			epsilon = 0.1 * arcLength(contours[i], true);
//			approxPolyDP(contours[i], approx[i], epsilon, true);
//			boundRect[i] = boundingRect(approx[i]);
//		}
//
//		// ���ο� �ּҸ� �Ҵ��ϴ°� ������ vector�� clear�ؼ� ����ϴ°��� ������ �𸣰��� ���� �ʱ�ȭ �ϸ� ���� �޸𸮿� ����Ǿ��ִ� �����ʹ� ���ư��°ǰ�?
//		vector < map<string, Point_<int>> > cnt;
//		// ���� ũ��, ����, ���� ����, ���� ������ �̿��Ͽ� �簢�� �ɷ�����
//		for (int i = 0; i < contours.size(); i++) {
//			area = (double)boundRect[i].height * boundRect[i].width;
//			ratio = (double)boundRect[i].width / boundRect[i].height;
//
//			if (area > MIN_AREA
//				&& boundRect[i].height > MIN_HEIGHT
//				&& boundRect[i].width > MIN_WIDTH
//				&& MIN_RATIO < ratio
//				&& ratio < MAX_RATIO
//				)
//			{
//				//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 1, LINE_8, 0);
//				map<string, Point_<int> > tocnt;
//				tocnt.insert(pair<string, Point_<int>>("tl", boundRect[i].tl()));
//				tocnt.insert(pair<string, Point_<int>>("br", boundRect[i].br()));
//				tocnt.insert(pair<string, Point_<int>>("cxy", (boundRect[i].tl() + (boundRect[i].br() - boundRect[i].tl()) / 2)));
//				cnt.push_back(tocnt);
//			}
//
//		}
//		// ����
//		bubble_sort(cnt, (int)cnt.size());
//
//	}
//
//
//}
//
//vector <map<string, Point_<int> > > result_img_contour(vector < map<string, Point_<int>> >& cnt) {
//	const double PI = 3.14159265358979323846;
//
//	// ������ �ؾ��Ѵ�... ���� ũ��, ���α��� ����, ���� ����
//	const int DEGREE = 30;
//	const double WIDTH_DIFF = 7.0;
//	const double MIN_AREA_DIFF = 0.6;
//	const double MAX_AREA_DIFF = 1.3;
//	const int LIST_LEN = 3;
//	const int MAX_AREA = 20000;
//	const double MIN_COORDINATE_DIFF_Y = 0.8;
//	const double MAX_COORDINATE_DIFF_Y = 1.3;
//
//	Scalar color = (255, 0, 0);
//
//	vector <map<string, Point_<int> > > before_result;
//	map<string, Point_<int> > tocnt;
//
//	for (int i = 0; i < (int)cnt.size(); i++) {
//		int rect_width = cnt[i]["br"].x - cnt[i]["tl"].x;
//
//		//rectangle(drawing, cnt[i]["tl"], cnt[i]["br"], color, 1, LINE_8, 0);
//		// j�� i ���� �����ϸ� �� �� ��ǥ,(�迭)�� �ִ� �����Ͷ��� �� ����.
//		for (int j = i; j < (int)cnt.size(); j++) {
//			if (cnt[i]["cxy"].x == cnt[j]["cxy"].x) {
//				continue;
//			}
//			//((cnt[i]["br"] - cnt[i]["tl"]).x * (cnt[i]["br"] - cnt[i]["tl"]).y) / ((cnt[j]["br"] - cnt[j]["tl"]).x * (cnt[j]["br"] - cnt[j]["tl"]).y)
//			//else if �� if�ιٲٰ� �� ���� ���� ����.
//			else if (
//				// ���� ���� ��
//				((cnt[i]["br"] - cnt[i]["tl"]).x * (cnt[i]["br"] - cnt[i]["tl"]).y) / ((cnt[j]["br"] - cnt[j]["tl"]).x * (cnt[j]["br"] - cnt[j]["tl"]).y) > MIN_AREA_DIFF
//				&&
//				((cnt[i]["br"] - cnt[i]["tl"]).x * (cnt[i]["br"] - cnt[i]["tl"]).y) / ((cnt[j]["br"] - cnt[j]["tl"]).x * (cnt[j]["br"] - cnt[j]["tl"]).y) < MAX_AREA_DIFF
//				&&
//				((cnt[j]["br"] - cnt[j]["tl"]).x * (cnt[j]["br"] - cnt[j]["tl"]).y) < MAX_AREA
//				// ���� ���� ��
//				&&
//				atan((cnt[i]["cxy"].y - cnt[j]["cxy"].y) / (cnt[j]["cxy"].x - cnt[i]["cxy"].x)) * 180 / PI < DEGREE
//				&&
//				atan((cnt[i]["cxy"].y - cnt[j]["cxy"].y) / (cnt[j]["cxy"].x - cnt[i]["cxy"].x)) * 180 / PI > -DEGREE
//				// i��° �簢���� j��°�� �簢���� �Ÿ����� �� (�� ������ �߽��� �Ÿ�/ i��° �簢���� ���� ���̷� ��)
//				&&
//				(cnt[j]["cxy"].x - cnt[i]["cxy"].x) / rect_width < WIDTH_DIFF
//				&&
//				(cnt[i]["cxy"].y / cnt[j]["cxy"].y) > MIN_COORDINATE_DIFF_Y
//				&&
//				(cnt[i]["cxy"].y / cnt[j]["cxy"].y) < MAX_COORDINATE_DIFF_Y
//				)
//			{
//				/*rectangle(drawing, cnt[i]["tl"], cnt[i]["br"], Scalar(0, 255, 0), 1, LINE_8, 0);
//				rectangle(drawing, cnt[j]["tl"], cnt[j]["br"], Scalar(0,255,0), 1, LINE_8, 0);
//				cout << "�Ÿ� : " << (cnt[i]["cxy"].x - cnt[j]["cxy"].x) / rect_width << endl;
//				cout << "tl : " << cnt[j]["tl"] << endl << "br : " << cnt[j]["br"] << endl;
//				cout << j << "���� ���� ũ��: " << ((cnt[j]["br"] - cnt[j]["tl"]).x* (cnt[j]["br"] - cnt[j]["tl"]).y) << endl;*/
//
//
//				tocnt.insert(pair<string, Point_<int>>("tl", cnt[j]["tl"]));
//				tocnt.insert(pair<string, Point_<int>>("br", cnt[j]["br"]));
//				before_result.push_back(tocnt);
//				tocnt.clear();
//				//before_result.push_back({ cnt[j]["tl"], cnt[j]["br"] });
//			}
//
//		}
//
//		if (before_result.size() < LIST_LEN) {
//			before_result.clear();
//			continue;
//		}
//		else {
//			tocnt.insert(pair<string, Point_<int>>("tl", cnt[i]["tl"]));
//			tocnt.insert(pair<string, Point_<int>>("br", cnt[i]["br"]));
//			before_result.insert(before_result.begin(), tocnt);
//			/*for (auto a : before_result) {
//				rectangle(drawing, a["tl"], a["br"], Scalar(0, 0, 255), 1, LINE_8, 0);
//			}*/
//
//			tocnt.clear();
//			break;
//		}
//
//
//	}
//	return before_result;
//}
//
//// �̹����� �簢�� �׸��� �Լ��� ���� ���� ������ �Ƿ� ���غ��� �����̶�
//// ��ó���԰� ���ÿ� ������ �׸�.
//
////void drawSquares(Mat& image, const vector<vector<Point> >& squares)
////{
////	Scalar color = Scalar(255, 0, 0);
////	for (size_t i = 0; i < squares.size(); i++)
////	{
////		const Point* p = &squares[i][0];
////		int n = (int)squares[i].size();
////		polylines(image, &p, &n, 1, true, color, 3, LINE_AA);
////	}
////}
//
////void drawSquares(Mat& img, const vector<vector<Point> >& contours, vector<Vec4i>& hierarchy) {
////	vector <Rect> boundRect;
////	vector<vector<Point>> approx;
////	double epsilon;
////
////	for (size_t i = 0; i < contours.size(); i++) {
////		epsilon = 0.1 * arcLength(contours[i], true);
////		approxPolyDP(contours[i], approx[i], epsilon, true);
////		boundRect[i] = boundingRect(approx[i]);
////	}
////
////	double ratio;
////	Scalar color = (255, 0, 0);
////	Mat drawing = Mat::zeros(img.size(), CV_8UC3);
////
////	for (int i = 0; i < contours.size(); i++) {
////		ratio = (double)boundRect[i].height / boundRect[i].width;
////		drawControus(drawing, contours, i, color, 1, 8, hierarchy, 0,)
////		drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
////	}
////}
//
//void write_roi_file(Mat& imgs_gray, vector < map<string, Point_ <int> > >& result_contour_list, string write_path) {
//	vector <Rect> roi;
//	Point_ <int> start_point;
//	Point_ <int> end_point;
//
//	for (auto a : result_contour_list) {
//		if (a.size() == 0) {
//			continue;
//		}
//		else if (a.size() <= 4) {
//			//������ ���� 2/3 ���� �� �а�. ������ �Ʒ��� �� ���� ���̸�ŭ��.
//			//start_point = Point_ <int>((a[0]["tl"].x - (int)((a[a.size() - 1]["br"].x - a[0]["tl"].x) * 2 / 3)), (a[0]["tl"].y - (int)(a[a.size() - 1]["br"].y - a[0]["tl"].y) * 2 / 3));
//			//end_point = Point_ <int>((a[a.size() - 1]["br"].x * 2 - a[0]["tl"].x), (a[a.size() - 1]["br"].y * 2 - a[0]["tl"].y));
//			start_point = a[0]["tl"];
//			end_point = a[a.size() - 1]["br"];
//		}
//		else {
//			start_point = a[0]["tl"];
//			end_point = a[a.size() - 1]["br"];
//
//		}
//
//		roi.push_back(Rect(start_point, end_point));
//	}
//	int x = 0;
//	cout << roi.size() << endl;
//
//	map<string, Mat>::iterator iter;
//	for (iter = imgs_gray.begin(); iter != imgs_gray.end(); iter++) {
//		cout << "x : " << x << endl;
//		cout << "tl : " << roi[x].tl() << endl << "br : " << roi[x].br() << endl;
//		imwrite(write_path + iter->first + ".jpg", imgs_gray[iter->first](roi[x]));
//		x++;
//	}
//}

// vector ���� list���ٰ� �̹��� �� ������ ��. 

int main() {
	Division_license divi;
	string img_path = "C:\\Users\\Cju\\Desktop\\[2019_08_01]before_division_license";
	string write_path = "C:\\Users\\Cju\\Desktop\\[2019_08_01]after_division_license\\";
	// imgs_color�� �ϳ��� �а�. main�� ���� ���� �ݰ�.
	// �̹����� �ֱ�
	//map<string, Mat> imgs_color = divi.insert2map(img_path);
	Mat img, img_binary;
	for (auto&& x : fs::recursive_directory_iterator(img_path)) {
		if (x.path().extension() == ".jpg" || x.path().extension() == ".JPG") {
			/*cout << x.path().generic_string() << endl;
			cout << x.path().stem().generic_string() << endl;*/
			//preprocessing �� �� �� �ִ°� . main���� ���� ��
			img = imread(x.path().generic_string(), IMREAD_COLOR);
			img.copyTo(img_binary);

			divi.preprocessing(img_binary);

			imwrite(write_path + x.path().stem().generic_string() + ".jpg", img_binary(divi.labeling(img_binary)));

			/*imgs_color.insert(pair<string, Mat>(x.path().stem().generic_string(), imread(x.path().generic_string(), IMREAD_COLOR)));
			divi.preprocessing(imgs_gray[iter->first]);*/
		}
		cout << x.path().stem().generic_string() << ".jpg write done " << endl;
		//x.path().extension() == ".jpg" || x.path().extension() == ".JPG" ? cout << x.path().generic_string << endl : cout << endl;
	}
	cout << "done" << endl;
	//map<string, Mat> imgs_gray(imgs_color);
	//cout << &imgs_color["1"].data << endl;
	//cout << &imgs_gray["1"].data << endl;
	//cout << "input done" << endl;
	//
	//// ��ó�� ����
	//map<string, Mat>::iterator iter;
	//for (iter = imgs_gray.begin(); iter != imgs_gray.end(); iter++) {
	//	divi.preprocessing(imgs_gray[iter->first]);
	//}
	//cout << "cvt2hsv, gaussian blur, white balance, " << endl;
	//
	////�󺧸� , roi ��ȯ
	////resize �� ������ ���� �ְڴ�. 
	////resize(imgs_gray[iter->first](divi.labeling(imgs_gray[iter->first])), imgs_gray[iter->first], Size(imgs_gray[iter->first].size() / 2), 0, 0, INTER_AREA);
	//for (iter = imgs_gray.begin(); iter != imgs_gray.end(); iter++) {
	//	imwrite(write_path + iter->first + ".jpg", imgs_gray[iter->first](divi.labeling(imgs_gray[iter->first])));
	//}
	//==============================================
	/*cv::imshow("color", imgs_color["39"]);
	cv::imshow("gray", imgs_gray["39"]);
	cv::waitKey(0);
	cv::imshow("color", imgs_color["139"]);
	cv::imshow("gray", imgs_gray["139"]);
	cv::waitKey(0);*/
	// contour �ϴ� ����
	////vector < map<string, Point_ <int> > > contour_list;
	//vector < vector < map<string, Point_ <int> > > > result_contour_list;

	//for (iter = imgs_gray.begin(); iter != imgs_gray.end(); iter++) {
	//	//contour_list = find_img_contour(imgs_gray[iter->first]);
	//	//result_contour_list.push_back(result_img_contour(contour_list));
	//	result_contour_list.push_back((divi.find_img_contour(imgs_gray[iter->first])));
	//	//divi.write_roi_file(imgs_gray[iter->first], divi.find_img_contour(imgs_gray[iter->first]), write_path);
	//}
	//cout << "380 line" << endl;

	//// ������ ��ȯ�� roi �������� �ϸ� �ɵ�

	//// roi ����
	//vector <Rect> roi;
	//Point_ <int> start_point;
	//Point_ <int> end_point;

	//for (auto a : result_contour_list) {
	//	cout << "a.size() : " << a.size() << endl;
	//	if (a.size() == 0) {
	//		continue;
	//	}
	//	else if (a.size() <= 4) {
	//		//������ ���� 2/3 ���� �� �а�. ������ �Ʒ��� �� ���� ���̸�ŭ��.
	//		start_point = Point_ <int>((a[0]["tl"].x - (int)((a[a.size() - 1]["br"].x - a[0]["tl"].x) * 2 / 3)), (a[0]["tl"].y - (int)(a[a.size() - 1]["br"].y - a[0]["tl"].y) * 2 / 3));
	//		end_point = Point_ <int>((a[a.size() - 1]["br"].x * 2 - a[0]["tl"].x), (a[a.size() - 1]["br"].y * 2 - a[0]["tl"].y));
	//		//start_point = a[0]["tl"];
	//		//end_point = a[a.size() - 1]["br"];
	//	}
	//	else {
	//		start_point = a[0]["tl"];
	//		end_point = a[a.size() - 1]["br"];

	//	}

	//	roi.push_back(Rect(start_point, end_point));
	//}
	//int x = 0;
	//cout << "here" << endl;
	//cout << roi.size() << endl;

	//for (iter = imgs_gray.begin(); iter != imgs_gray.end(); iter++) {
	//	cout << "x : " << x << endl;
	//	cout << "tl : " << roi[x].tl() << endl << "br : " << roi[x].br() << endl;
	//	imwrite(write_path + iter->first + ".jpg", imgs_gray[iter->first](roi[x]));
	//	x++;
	//}


	//cv::imshow("color", imgs_color["0"]);
	//cv::imshow("gray", imgs_gray["0"]);
	//cv::waitKey(0);
	//Mat drawing = Mat::zeros(imgs_gray["3"].size(), CV_8UC3);
	//drawSquares(imgs_gray["3"], squares);
	//drawContours(drawing, approx, 0, color, 2);

	//cv::imshow("contours", drawing);
	//imshow("contours", drawing);

	//==============================================

	//vector<vector<Point>> contours;
	//vector<Vec4i> hierarchy;

	//findContours(imgs_gray["3"], contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
	//
	//Mat drawing = Mat::zeros(imgs_gray["3"].size(), CV_8UC3);
	//Scalar color = Scalar(255, 0, 0);

	////vector <Point> approx;

	//double epsilon;

	//////���� ��ȯ
	////vector<Vec4i> lines;
	////HoughLinesP(imgs_gray["3"], lines, 1, CV_PI / 180, 100, 20, 1);

	////for (int i = 0; i < lines.size(); i++)
	////{
	////	Vec4i L = lines[i];
	////	line(drawing, Point(L[0], L[1]), Point(L[2], L[3]),
	////		color, 1, LINE_AA);
	////}
	//vector <Rect> boundRect(contours.size());
	//vector<vector<Point>> approx(contours.size());


	//for (size_t i = 0; i < contours.size(); i++) {
	//	epsilon = (double) 0.1 * arcLength(contours[i], true);
	//	approxPolyDP(contours[i], approx[i], epsilon, true);
	//	
	//	boundRect[(int)i] = boundingRect(contours[i]);
	//	
	//}
	////�ʹ� ���׸��� ���� ������ ���� �ȵǰڰ� ������ ũ���̻�����. ��� ������ ���缭.
	//double ratio;
	//double area;
	//const int MIN_AREA = 280;
	//const int MIN_WIDTH = 4;
	//const int MIN_HEIGHT = 7;
	//const double MIN_RATIO = 0.35;
	//const double MAX_RATIO = 0.85;

	////map <string, Point_<int>> cnt
	//
	//vector < map<string, Point_<int>> > cnt;

	//for (int i = 0; i < contours.size(); i++) {
	//	area = (double)boundRect[i].height * boundRect[i].width;
	//	ratio = (double)boundRect[i].width / boundRect[i].height;
	//	if (area > MIN_AREA 
	//		&& boundRect[i].height > MIN_HEIGHT
	//		&& boundRect[i].width > MIN_WIDTH
	//		&& MIN_RATIO < ratio 
	//		&& ratio < MAX_RATIO
	//		) 
	//	{
	//		//�簢�� �׷��ִ� �Լ�
	//		//rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 1, LINE_8, 0);

	//		//cnt.push_back(tocnt.insert(make_pair("ti", boundRect[i].tl())));

	//		// �迭�ȿ� map �ֱ�
	//		map<string, Point_<int> > tocnt;
	//		tocnt.insert(pair<string, Point_<int>>("tl", boundRect[i].tl()));
	//		tocnt.insert(pair<string, Point_<int>>("br", boundRect[i].br()));
	//		tocnt.insert(pair<string, Point_<int>>("cxy", (boundRect[i].tl() + (boundRect[i].br() - boundRect[i].tl()) / 2)));
	//		cnt.push_back(tocnt);

	//		/*cnt["tl"] = boundRect[i].tl();
	//		cnt["br"] = boundRect[i].br();
	//		cnt["cxy"] = (boundRect[i].tl() + (boundRect[i].br() - boundRect[i].tl()) / 2);*/
	//	}

	//}
	//
	////���� ���� �ؾ� ��
	//cout << "cnt size() : " << cnt.size() <<endl;

	//bubble_sort(cnt, (int)cnt.size());

	///*for (auto a : cnt) {
	//	cout << "tl : " << a["tl"] << endl << "br : " << a["br"] << endl;

	//}*/

	////16 ���� , /2 +5 ��
	//const double PI = 3.14159265358979323846;

	//// ������ �ؾ��Ѵ�... ���� ũ��, ���α��� ����, ���� ����
	//const int DEGREE = 20;
	//const double WIDTH_DIFF = 7.0;
	//const double MIN_AREA_DIFF = 0.6;
	//const double MAX_AREA_DIFF = 1.3;
	//const int LIST_LEN = 3;
	//const int MAX_AREA = 20000;
	//const double MIN_COORDINATE_DIFF_Y = 0.8;
	//const double MAX_COORDINATE_DIFF_Y = 1.3;

	//vector <map<string, Point_<int> > > before_result;
	//map<string, Point_<int> > tocnt;

	//for (int i = 0; i < (int)cnt.size(); i++) {
	//	int rect_width = cnt[i]["br"].x - cnt[i]["tl"].x;

	//	rectangle(drawing, cnt[i]["tl"], cnt[i]["br"], color, 1, LINE_8, 0);
	//	// j�� i ���� �����ϸ� �� �� ��ǥ,(�迭)�� �ִ� �����Ͷ��� �� ����.
	//	for (int j = i; j < (int)cnt.size(); j++) {
	//		if (cnt[i]["cxy"].x == cnt[j]["cxy"].x) {
	//			continue;
	//		}
	//		else if (
	//			// ���� ���� ��
	//			((cnt[i]["br"] - cnt[i]["tl"]).x * (cnt[i]["br"] - cnt[i]["tl"]).y) / ((cnt[j]["br"] - cnt[j]["tl"]).x * (cnt[j]["br"] - cnt[j]["tl"]).y) > MIN_AREA_DIFF
	//			&&
	//			((cnt[i]["br"] - cnt[i]["tl"]).x * (cnt[i]["br"] - cnt[i]["tl"]).y) / ((cnt[j]["br"] - cnt[j]["tl"]).x * (cnt[j]["br"] - cnt[j]["tl"]).y) < MAX_AREA_DIFF
	//			&&
	//			((cnt[j]["br"] - cnt[j]["tl"]).x * (cnt[j]["br"] - cnt[j]["tl"]).y) < MAX_AREA
	//			// ���� ���� ��
	//			&&
	//			atan((cnt[i]["cxy"].y - cnt[j]["cxy"].y) / (cnt[j]["cxy"].x - cnt[i]["cxy"].x)) * 180 / PI < DEGREE
	//			&&
	//			atan((cnt[i]["cxy"].y - cnt[j]["cxy"].y) / (cnt[j]["cxy"].x - cnt[i]["cxy"].x)) * 180 / PI > -DEGREE
	//			//i��° �簢���� j��°�� �簢���� �Ÿ����� �� (�� ������ �߽��� �Ÿ�/ i��° �簢���� ���� ���̷� ��)
	//			&&
	//			(cnt[j]["cxy"].x - cnt[i]["cxy"].x) / rect_width < WIDTH_DIFF
	//			&&
	//			(cnt[i]["cxy"].y / cnt[j]["cxy"].y) > MIN_COORDINATE_DIFF_Y
	//			&&
	//			(cnt[i]["cxy"].y / cnt[j]["cxy"].y) < MAX_COORDINATE_DIFF_Y

	//			)
	//		{
	//			/*rectangle(drawing, cnt[i]["tl"], cnt[i]["br"], Scalar(0, 255, 0), 1, LINE_8, 0);
	//			rectangle(drawing, cnt[j]["tl"], cnt[j]["br"], Scalar(0,255,0), 1, LINE_8, 0);
	//			cout << "�Ÿ��ϴ°ǵ� �̰� ��� ������ " << (cnt[i]["cxy"].x - cnt[j]["cxy"].x) / rect_width << endl;
	//			cout << "tl : " << cnt[j]["tl"] << endl << "br : " << cnt[j]["br"] << endl;
	//			cout << j << "���� ���� ũ��: " << ((cnt[j]["br"] - cnt[j]["tl"]).x* (cnt[j]["br"] - cnt[j]["tl"]).y) << endl;*/

	//			
	//			tocnt.insert(pair<string, Point_<int>>("tl", cnt[j]["tl"]) );
	//			tocnt.insert(pair<string, Point_<int>>("br", cnt[j]["br"]) );
	//			before_result.push_back(tocnt);
	//			tocnt.clear();
	//			//before_result.push_back({ cnt[j]["tl"], cnt[j]["br"] });
	//		}

	//	}

	//	if (before_result.size() < LIST_LEN) {
	//		before_result.clear();
	//		continue;
	//	}
	//	else {
	//		tocnt.insert(pair<string, Point_<int>>("tl", cnt[i]["tl"]));
	//		tocnt.insert(pair<string, Point_<int>>("br", cnt[i]["br"]));
	//		before_result.insert(before_result.begin(), tocnt);
	//		cout << "list size : " << before_result.size() << endl;
	//		for (auto a : before_result) {
	//			rectangle(drawing, a["tl"], a["br"], Scalar(0, 0, 255), 1, LINE_8, 0);
	//		}
	//		
	//		tocnt.clear();
	//		break;
	//	}
	//	
	//	

	//}
	//cv::imshow("color", imgs_color["242"]);
	//cv::imshow("gray", imgs_gray["3"]);
	//cv::imshow("contours", drawing);
	//cv::waitKey(0);

	////for (int i = 0; i < (int)cnt.size() - 1; i++) {

	////	rectangle(drawing, cnt[i]["tl"], cnt[i]["br"], Scalar(0, 255, 0), 1, LINE_8, 0);
	////	cout << "tl : " << cnt[i]["tl"] << endl << "br : " << cnt[i]["br"] << endl;
	////	cout << i << "���� ���� ũ��: " << ((cnt[i]["br"] - cnt[i]["tl"]).x * (cnt[i]["br"] - cnt[i]["tl"]).y) << endl;

	////	// �簢���� ���� ���̿�, �̹� �簢���� ���� �簢���� �߽������κ����� �Ÿ��� ���
	////	// ������ ��� ����ߴ� �߽��� �Ÿ� ����ϵ�, �簢�� �ȿ� �簢���� ���� �� ������ �Ÿ��� ��¥ ������ continue �̰� ������ ���� ó�� �ؼ� ���ص� �ɵ�. 4���̻��̾�� ��.

	////	int rect_width = cnt[i]["br"].x - cnt[i]["tl"].x;
	////	
	////	//cout << "tl : " << cnt[i]["tl"] << endl << "br : " << cnt[i]["br"] << endl;
	////	if (cnt[i]["cxy"].x == cnt[i + 1]["cxy"].x) {
	////		continue;
	////	}
	////	else if (
	////		// �̰͵� ������ �ٲ�� �ϴµ� ���� �ִٰ�
	////		rect_width - 15 < cnt[i + 1]["cxy"].x - cnt[i]["cxy"].x && rect_width + 15 > cnt[i + 1]["cxy"].x - cnt[i]["cxy"].x
	////		// �� �߽��� ������ ����
	////		&&
	////		atan((cnt[i]["cxy"].y - cnt[i + 1]["cxy"].y) / (cnt[i + 1]["cxy"].x - cnt[i]["cxy"].x)) * 180 / PI < DEGREE
	////		&&
	////		atan((cnt[i]["cxy"].y - cnt[i + 1]["cxy"].y) / (cnt[i + 1]["cxy"].x - cnt[i]["cxy"].x)) * 180 / PI > -DEGREE
	////		//
	////		)
	////	{
	////		rectangle(drawing, cnt[i]["tl"], cnt[i]["br"], color, 1, LINE_8, 0);
	////		//rectangle(drawing, cnt[i+1]["tl"], cnt[i+1]["br"], color, 1, LINE_8, 0);
	////		cout << "======================" << endl;
	////		cout << "tl : " << cnt[i]["tl"] << endl << "br : " << cnt[i]["br"] << endl;
	////		cout << i << "���� ���� ũ��: " << ((cnt[i]["br"] - cnt[i]["tl"]).x * (cnt[i]["br"] - cnt[i]["tl"]).y) << endl;
	////		cout << "���� ũ�� : " << atan((cnt[i]["cxy"].y - cnt[i + 1]["cxy"].y) / (cnt[i + 1]["cxy"].x - cnt[i]["cxy"].x)) * 180 / PI << endl;
	////		cout << "======================" << endl;

	////	}

	////}


	////drawSquares(imgs_gray["3"], squares);
	////drawContours(drawing, approx, 0, color, 2);

	////imshow("contours", drawing);
	return 0;
}