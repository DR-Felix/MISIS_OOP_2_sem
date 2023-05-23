#include <opencv2/opencv.hpp>
#include <cmath>

cv::Mat niblackThreshold(const cv::Mat& src, int windowSize, double k, double& scale) {
    cv::Mat imgGray;

    cv::cvtColor(src, imgGray, cv::COLOR_BGR2GRAY);

    // Определяем масштаб по ширине и высоте
    double scaleWidth = static_cast<double>(800) / imgGray.cols;
    double scaleHeight = static_cast<double>(600) / imgGray.rows;

    // Находим меньший коэффициент масштабирования, чтобы изображение поместилось в окно 800x600
    scale = std::min(scaleWidth, scaleHeight);

    // Масштабирование исходного изображения
    cv::Mat resizedSrc;
    cv::resize(imgGray, resizedSrc, cv::Size(), scale, scale);

    cv::Mat imgThresh(resizedSrc.size(), CV_8UC1);

    int halfWindowSize = windowSize / 2;

    for (int y = halfWindowSize; y < resizedSrc.rows - halfWindowSize; ++y) {
        for (int x = halfWindowSize; x < resizedSrc.cols - halfWindowSize; ++x) {
            // Вычисляем среднее значение яркости в окрестности
            double mean = 0.0;
            for (int j = -halfWindowSize; j <= halfWindowSize; ++j) {
                for (int i = -halfWindowSize; i <= halfWindowSize; ++i) {
                    mean += resizedSrc.at<uchar>(y + j, x + i); // возвращает значение яркости пикселя в позиции (y + j, x + i) в черно-белом изображении resizedSrc
                }
            }
            mean /= (windowSize * windowSize);

            // Вычисляем стандартное отклонение яркости в окрестности
            double stdDeviation = 0.0;
            for (int j = -halfWindowSize; j <= halfWindowSize; ++j) {
                for (int i = -halfWindowSize; i <= halfWindowSize; ++i) {
                    double diff = resizedSrc.at<uchar>(y + j, x + i) - mean;
                    stdDeviation += diff * diff;
                }
            }
            stdDeviation = std::sqrt(stdDeviation / (windowSize * windowSize));

            // Вычисляем пороговое значение яркости для текущего пикселя
            double threshold = mean + k * stdDeviation;

            // Бинаризация пикселя
            if (resizedSrc.at<uchar>(y, x) > threshold) {
                imgThresh.at<uchar>(y, x) = 255;
            }
            else {
                imgThresh.at<uchar>(y, x) = 0;
            }
        }
    }

    return imgThresh;
}

void demonstrateNiblack(const cv::Mat& src, int windowSize, double k, double& scale) {
    cv::Mat imgThresh = niblackThreshold(src, windowSize, k, scale);

    // Масштабирование окна изображения
    cv::Mat resizedWindow;
    cv::resize(src, resizedWindow, cv::Size(), scale, scale);

    cv::imshow("Original Image", resizedWindow);
    cv::imshow("Thresholded Image", imgThresh);
    cv::waitKey(0);
}

int main() {
    cv::Mat image = cv::imread("C:/Users/nick_/Downloads/test1.jpg");

    if (image.empty()) {
        std::cout << "Failed to load image." << std::endl;
        return -1;
    }

    /*if (image.channels() != 1) {
        std::cout << "Invalid image format. Only grayscale images are supported." << std::endl;
        return -1;
    }*/

    int windowSize = 31;
    double k = 0.2;
    double scale;
    demonstrateNiblack(image, windowSize, k, scale);

    return 0;
}
