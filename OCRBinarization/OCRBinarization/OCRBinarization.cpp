#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

const int GREEN_MIN = 21;
const int GREEN_MAX = 110;

void main(int argc, char** argv) {
	Mat src = imread("testImages\\4.jpg"); //Исходное изображение

	imshow("input", src);
	imwrite("src.jpg", src);
	//Переводим в формат HSV
	Mat hsv = Mat(src.cols, src.rows, 8, 3); //
	std::vector<Mat> splitedHsv = std::vector<Mat>();
	cvtColor(src, hsv, COLOR_BGR2HSV);
	split(hsv, splitedHsv);

	//Удаляем фон

	for (int y = 0; y < hsv.cols; y++) {
		for (int x = 0; x < hsv.rows; x++) {

			// получаем HSV-компоненты пикселя
			int H = static_cast<int>(splitedHsv[0].at<uchar>(x, y));        // Тон
			int S = static_cast<int>(splitedHsv[1].at<uchar>(x, y));        // Интенсивность
			int V = static_cast<int>(splitedHsv[2].at<uchar>(x, y));        // Яркость

			//Если яркость слишком низкая либо Тон не попадает у заданный диапазон, то закрашиваем белым
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

	//Морфологическое замыкание для удаления остаточных шумов.
	int an = 0;
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(an * 2 + 1, an * 2 + 1), Point(an, an));
	dilate(src, tmp, element);
	erode(tmp, tmp, element);

	//Переводим изображение в чернобелый формат
	Mat grayscaleMat;
	cvtColor(tmp, grayscaleMat, COLOR_BGR2GRAY);

	//Делаем бинарную маску
	Mat mask(grayscaleMat.size(), grayscaleMat.type());
	Mat out(src.size(), src.type());
	threshold(grayscaleMat, mask, 200, 255, THRESH_BINARY_INV);

	//Финальное изображение редварительно красим в белый цвет
	out = Scalar::all(255);
	//Копируем зашумленное изображение через маску
	src.copyTo(out, mask);

	imshow("До замыкания", src);
	imshow("Результат замыкания", tmp);
	imshow("Результат", out);

	waitKey();
}