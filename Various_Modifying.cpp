#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat img1 = imread("hwfig03.jpg", IMREAD_COLOR);
	Mat img2 = Mat(size(img1), CV_8UC3, Scalar(255, 255, 255)); //선 그림
	Mat img3 = Mat(size(img1), CV_8UC3, Scalar(255, 255, 255)); //사각형 그림
	Mat img4 = Mat(size(img1), CV_8UC3, Scalar(255, 255, 255)); //원 그림
	CV_Assert(img1.data&&img2.data,img3.data&&img3.data$$img4.data); //예외처리
	img2 = img1.clone(); //img2에 img1 복사
	img3 = img1.clone(); //img3에 img1 복사
	img4 = img1.clone(); //img4에 img1 복사

	Point2i pt, sumr(0, 0), sumg(0, 0), sumb(0, 0), sumy(0, 0), sump(0, 0);
	int countr, countg, countb, county, countp; //픽셀 수
	countr = countb = countg = county = countp = 0; //초기화

	for (pt.y = 0; pt.y < img1.rows; pt.y++) {
		for (pt.x = 0; pt.x < img1.cols; pt.x++) {
			if (img1.at<Vec3b>(pt.y, pt.x)[0] < 60 &&
				img1.at<Vec3b>(pt.y, pt.x)[1] < 60 &&
				img1.at<Vec3b>(pt.y, pt.x)[2]>150) { //빨간색
				countr++; //빨간색을 나타내는 픽셀 수 세기
				sumr += pt; //다 더하기
			}
			else if (img1.at<Vec3b>(pt.y, pt.x)[0] > 100 &&
				img1.at<Vec3b>(pt.y, pt.x)[1] < 65 &&
				img1.at<Vec3b>(pt.y, pt.x)[2]<65) { //파란색
				countb++;
				sumb += pt;
			}
			else if (img1.at<Vec3b>(pt.y, pt.x)[0] < 50 &&
				img1.at<Vec3b>(pt.y, pt.x)[1] > 100 &&
				img1.at<Vec3b>(pt.y, pt.x)[2]< 50) { //초록색
				countg++;
				sumg += pt;
			}
			else if (img1.at<Vec3b>(pt.y, pt.x)[0] < 60 &&
				img1.at<Vec3b>(pt.y, pt.x)[1] > 150 &&
				img1.at<Vec3b>(pt.y, pt.x)[2]> 150) { //노란색
				county++;
				sumy += pt;
			}
			else if (img1.at<Vec3b>(pt.y, pt.x)[0] > 200 &&
				img1.at<Vec3b>(pt.y, pt.x)[1] < 180 &&
				img1.at<Vec3b>(pt.y, pt.x)[2]> 200) { //핑크색
				countp++;
				sump += pt;
			}
		}
	}

	Point2i rcenter(sumr.x / countr, sumr.y / countr); //빨간 원의 중점
	Point2i bcenter(sumb.x / countb, sumb.y / countb); //파란 원의 중점
	Point2i gcenter(sumg.x / countg, sumg.y / countg); //초록 원의 중점
	Point2i ycenter(sumy.x / county, sumy.y / county); //노란 원의 중점
	Point2i pcenter(sump.x / countp, sump.y / countp); //분홍 원의 중점

	line(img2, bcenter, rcenter, Scalar(0, 0, 0), 1); //파랑-빨강 선 그리기
	line(img2, rcenter, gcenter, Scalar(0, 0, 0), 1); //빨강-초록 선 그리기
	line(img2, gcenter, ycenter, Scalar(0, 0, 0), 1); //초록-노랑 선 그리기
	line(img2, ycenter, pcenter, Scalar(0, 0, 0), 1); //노랑-핑크 선 그리기

	int r_radius = sqrt((float)countr / 3.14); //빨간 원 반지름 구하기
	int b_radius = sqrt((float)countb / 3.14); //파란 원 반지름 구하기
	int g_radius = sqrt((float)countg / 3.14); //초록 원 반지름 구하기
	int y_radius = sqrt((float)county / 3.14); //노란 원 반지름 구하기
	int p_radius = sqrt((float)countp / 3.14); //분홍 원 반지름 구하기

	rectangle(img3, Point(gcenter.x - g_radius, rcenter.y - r_radius), //빨강-초록 사각형
		Point(rcenter.x + r_radius, gcenter.y + g_radius), Scalar(0, 0, 0), 1);
	rectangle(img3, Point(pcenter.x - p_radius, ycenter.y - y_radius), //노랑-핑크 사각형
		Point(ycenter.x + y_radius, pcenter.y + p_radius), Scalar(0, 0, 0), 1);

	circle(img4, rcenter, 5 * r_radius, Scalar(0, 0, 0), 1); //빨간색 원 주변 반지름 5배인 원 그림
	putText(img4, "Sun", Point(rcenter.x - 4 * r_radius, rcenter.y - r_radius * 5),FONT_HERSHEY_SIMPLEX,0.6,Scalar(0,0,0),1); //Sun이라는 글씨 씀
	circle(img4, gcenter, 3 * g_radius, Scalar(0, 0, 0), 1); //초록색 원 주변 반지름 3배인 원 그림
	putText(img4, "Earth", Point(gcenter.x - 4 * g_radius, gcenter.y - g_radius * 3), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 0), 1); //Earth라는 글씨 씀
	circle(img4, ycenter, 1.2 * y_radius, Scalar(0, 0, 0), 1); //노란색 원 주변 반지름 1.2배인 원 그림
	putText(img4, "Moon", Point(ycenter.x - 4 * y_radius, ycenter.y - y_radius * 1.2), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 0), 1); //Moon이라는 글씨 씀

	imshow("hwfig03", img1);
	imshow("Line",img2);
	imshow("Rectangle", img3);
	imshow("Circle", img4);
	waitKey(0);
}