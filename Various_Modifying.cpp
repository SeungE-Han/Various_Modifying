#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat img1 = imread("hwfig03.jpg", IMREAD_COLOR);
	Mat img2 = Mat(size(img1), CV_8UC3, Scalar(255, 255, 255)); //�� �׸�
	Mat img3 = Mat(size(img1), CV_8UC3, Scalar(255, 255, 255)); //�簢�� �׸�
	Mat img4 = Mat(size(img1), CV_8UC3, Scalar(255, 255, 255)); //�� �׸�
	CV_Assert(img1.data&&img2.data,img3.data&&img3.data$$img4.data); //����ó��
	img2 = img1.clone(); //img2�� img1 ����
	img3 = img1.clone(); //img3�� img1 ����
	img4 = img1.clone(); //img4�� img1 ����

	Point2i pt, sumr(0, 0), sumg(0, 0), sumb(0, 0), sumy(0, 0), sump(0, 0);
	int countr, countg, countb, county, countp; //�ȼ� ��
	countr = countb = countg = county = countp = 0; //�ʱ�ȭ

	for (pt.y = 0; pt.y < img1.rows; pt.y++) {
		for (pt.x = 0; pt.x < img1.cols; pt.x++) {
			if (img1.at<Vec3b>(pt.y, pt.x)[0] < 60 &&
				img1.at<Vec3b>(pt.y, pt.x)[1] < 60 &&
				img1.at<Vec3b>(pt.y, pt.x)[2]>150) { //������
				countr++; //�������� ��Ÿ���� �ȼ� �� ����
				sumr += pt; //�� ���ϱ�
			}
			else if (img1.at<Vec3b>(pt.y, pt.x)[0] > 100 &&
				img1.at<Vec3b>(pt.y, pt.x)[1] < 65 &&
				img1.at<Vec3b>(pt.y, pt.x)[2]<65) { //�Ķ���
				countb++;
				sumb += pt;
			}
			else if (img1.at<Vec3b>(pt.y, pt.x)[0] < 50 &&
				img1.at<Vec3b>(pt.y, pt.x)[1] > 100 &&
				img1.at<Vec3b>(pt.y, pt.x)[2]< 50) { //�ʷϻ�
				countg++;
				sumg += pt;
			}
			else if (img1.at<Vec3b>(pt.y, pt.x)[0] < 60 &&
				img1.at<Vec3b>(pt.y, pt.x)[1] > 150 &&
				img1.at<Vec3b>(pt.y, pt.x)[2]> 150) { //�����
				county++;
				sumy += pt;
			}
			else if (img1.at<Vec3b>(pt.y, pt.x)[0] > 200 &&
				img1.at<Vec3b>(pt.y, pt.x)[1] < 180 &&
				img1.at<Vec3b>(pt.y, pt.x)[2]> 200) { //��ũ��
				countp++;
				sump += pt;
			}
		}
	}

	Point2i rcenter(sumr.x / countr, sumr.y / countr); //���� ���� ����
	Point2i bcenter(sumb.x / countb, sumb.y / countb); //�Ķ� ���� ����
	Point2i gcenter(sumg.x / countg, sumg.y / countg); //�ʷ� ���� ����
	Point2i ycenter(sumy.x / county, sumy.y / county); //��� ���� ����
	Point2i pcenter(sump.x / countp, sump.y / countp); //��ȫ ���� ����

	line(img2, bcenter, rcenter, Scalar(0, 0, 0), 1); //�Ķ�-���� �� �׸���
	line(img2, rcenter, gcenter, Scalar(0, 0, 0), 1); //����-�ʷ� �� �׸���
	line(img2, gcenter, ycenter, Scalar(0, 0, 0), 1); //�ʷ�-��� �� �׸���
	line(img2, ycenter, pcenter, Scalar(0, 0, 0), 1); //���-��ũ �� �׸���

	int r_radius = sqrt((float)countr / 3.14); //���� �� ������ ���ϱ�
	int b_radius = sqrt((float)countb / 3.14); //�Ķ� �� ������ ���ϱ�
	int g_radius = sqrt((float)countg / 3.14); //�ʷ� �� ������ ���ϱ�
	int y_radius = sqrt((float)county / 3.14); //��� �� ������ ���ϱ�
	int p_radius = sqrt((float)countp / 3.14); //��ȫ �� ������ ���ϱ�

	rectangle(img3, Point(gcenter.x - g_radius, rcenter.y - r_radius), //����-�ʷ� �簢��
		Point(rcenter.x + r_radius, gcenter.y + g_radius), Scalar(0, 0, 0), 1);
	rectangle(img3, Point(pcenter.x - p_radius, ycenter.y - y_radius), //���-��ũ �簢��
		Point(ycenter.x + y_radius, pcenter.y + p_radius), Scalar(0, 0, 0), 1);

	circle(img4, rcenter, 5 * r_radius, Scalar(0, 0, 0), 1); //������ �� �ֺ� ������ 5���� �� �׸�
	putText(img4, "Sun", Point(rcenter.x - 4 * r_radius, rcenter.y - r_radius * 5),FONT_HERSHEY_SIMPLEX,0.6,Scalar(0,0,0),1); //Sun�̶�� �۾� ��
	circle(img4, gcenter, 3 * g_radius, Scalar(0, 0, 0), 1); //�ʷϻ� �� �ֺ� ������ 3���� �� �׸�
	putText(img4, "Earth", Point(gcenter.x - 4 * g_radius, gcenter.y - g_radius * 3), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 0), 1); //Earth��� �۾� ��
	circle(img4, ycenter, 1.2 * y_radius, Scalar(0, 0, 0), 1); //����� �� �ֺ� ������ 1.2���� �� �׸�
	putText(img4, "Moon", Point(ycenter.x - 4 * y_radius, ycenter.y - y_radius * 1.2), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 0, 0), 1); //Moon�̶�� �۾� ��

	imshow("hwfig03", img1);
	imshow("Line",img2);
	imshow("Rectangle", img3);
	imshow("Circle", img4);
	waitKey(0);
}