#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

const int GREEN_MIN = 21;
const int GREEN_MAX = 110;

void main(int argc, char** argv) {
	Mat src = imread("testImages\\4.jpg"); //�������� �����������

	imshow("input", src);
	imwrite("src.jpg", src);
	//��������� � ������ HSV
	Mat hsv = Mat(src.cols, src.rows, 8, 3); //
	std::vector<Mat> splitedHsv = std::vector<Mat>();
	cvtColor(src, hsv, COLOR_BGR2HSV);
	split(hsv, splitedHsv);

	//������� ���

	for (int y = 0; y < hsv.cols; y++) {
		for (int x = 0; x < hsv.rows; x++) {

			// �������� HSV-���������� �������
			int H = static_cast<int>(splitedHsv[0].at<uchar>(x, y));        // ���
			int S = static_cast<int>(splitedHsv[1].at<uchar>(x, y));        // �������������
			int V = static_cast<int>(splitedHsv[2].at<uchar>(x, y));        // �������

			//���� ������� ������� ������ ���� ��� �� �������� � �������� ��������, �� ����������� �����
			if ((S > 20) && (V < 200) /*|| (H < GREEN_MIN) || (H > GREEN_MAX))*/) {
				src.at<Vec3b>(x, y)[0] = 0;
				src.at<Vec3b>(x, y)[1] = 0;
				src.at<Vec3b>(x, y)[2] = 0;
			}
			else {
				src.at<Vec3b>(x, y)[0] = 255;
				src.at<Vec3b>(x, y)[1] = 255;
				src.at<Vec3b>(x, y)[2] = 255;
			}
		}
	}
	Mat tmp;

	//��������������� ��������� ��� �������� ���������� �����.
	int an = 0;
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(an * 2 + 1, an * 2 + 1), Point(an, an));
	dilate(src, tmp, element);
	erode(tmp, tmp, element);

	//��������� ����������� � ���������� ������
	Mat grayscaleMat;
	cvtColor(tmp, grayscaleMat, COLOR_BGR2GRAY);

	//������ �������� �����
	Mat mask(grayscaleMat.size(), grayscaleMat.type());
	Mat out(src.size(), src.type());
	threshold(grayscaleMat, mask, 200, 255, THRESH_BINARY_INV);

	//��������� ����������� ������������� ������ � ����� ����
	out = Scalar::all(255);
	//�������� ����������� ����������� ����� �����
	src.copyTo(out, mask);

	imshow("�� ���������", src);
	imshow("��������� ���������", tmp);
	imshow("���������", out);

	waitKey();
}