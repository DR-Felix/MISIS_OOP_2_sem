#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <cmath>

std::vector<double> calculateMeanBrightness(const cv::Mat& src) {
    cv::Mat imgGray;
    cv::cvtColor(src, imgGray, cv::COLOR_BGR2GRAY);

    std::vector<double> meanBrightness;

    for (int y = 0; y < imgGray.rows; ++y) {
        for (int x = 0; x < imgGray.cols; ++x) {
            meanBrightness.push_back(static_cast<double>(imgGray.at<uchar>(y, x)));
        }
    }

    return meanBrightness;
}

void saveMeanBrightnessToFile(const std::vector<double>& meanBrightness, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (double value : meanBrightness) {
            file << value << "\n";
        }
        file.close();
    }
    else {
        std::cout << "Ошибка: Не удалось открыть файл для сохранения данных.\n";
    }
}

cv::Mat niblackThreshold(const cv::Mat& src, int windowSize, double k, double& scale) {
    cv::Mat imgGray;
    cv::cvtColor(src, imgGray, cv::COLOR_BGR2GRAY);

    double scaleWidth = static_cast<double>(800) / imgGray.cols;
    double scaleHeight = static_cast<double>(600) / imgGray.rows;
    scale = std::min(scaleWidth, scaleHeight);

    cv::Mat resizedSrc;
    cv::resize(imgGray, resizedSrc, cv::Size(), scale, scale);

    cv::Mat imgThresh(resizedSrc.size(), CV_8UC1);

    int halfWindowSize = windowSize / 2;

    for (int y = halfWindowSize; y < resizedSrc.rows - halfWindowSize; ++y) {
        for (int x = halfWindowSize; x < resizedSrc.cols - halfWindowSize; ++x) {
            double mean = 0.0;
            for (int j = -halfWindowSize; j <= halfWindowSize; ++j) {
                for (int i = -halfWindowSize; i <= halfWindowSize; ++i) {
                    mean += resizedSrc.at<uchar>(y + j, x + i);
                }
            }
            mean /= (windowSize * windowSize);

            double stdDeviation = 0.0;
            for (int j = -halfWindowSize; j <= halfWindowSize; ++j) {
                for (int i = -halfWindowSize; i <= halfWindowSize; ++i) {
                    double diff = resizedSrc.at<uchar>(y + j, x + i) - mean;
                    stdDeviation += diff * diff;
                }
            }
            stdDeviation = std::sqrt(stdDeviation / (windowSize * windowSize));

            double threshold = mean + k * stdDeviation;

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

    cv::Mat resizedWindow;
    cv::resize(src, resizedWindow, cv::Size(), scale, scale);

    cv::imshow("Original Image", resizedWindow);
    cv::imshow("Thresholded Image", imgThresh);
    cv::waitKey(0);
}

int main(int argc, char** argv) {

    std::cout << "Enter the command in the format:\n";
    std::cout << "<input_image> <window_size> <k>\n";
    std::cout << "Where:\n";
    std::cout << "<input_image> - path to the input image.\n";
    std::cout << "<window_size> - window size (integer).\n";
    std::cout << "<k> - parameter k for the Niblack algorithm (floating point number).\n";

    if (argc != 4) {
        std::cout << "Error: Incorrect number of command line parameters.\n";
        std::cout << "The correct command format is: <input_image> <window_size> <k>\n";
        return -1;
    }


    //C:\Projects_C++\OOP_2023\bin.dbg\course_test.exe C:\Users\nick_\Downloads\test1.jpg 31 0,2

    std::string inputImagePath = argv[1];
    int windowSize = std::atoi(argv[2]);
    double k = std::atof(argv[3]);

    double scale;

    cv::Mat image = cv::imread(inputImagePath);

    if (image.empty()) {
        std::cout << "Ошибка: Не удалось загрузить изображение.\n";
        return -1;
    }

    std::vector<double> meanBrightness = calculateMeanBrightness(image);

    std::string dataFilename = "C:/Users/nick_/Downloads/mean_brightness.txt";

    saveMeanBrightnessToFile(meanBrightness, dataFilename);

    demonstrateNiblack(image, windowSize, k, scale);

    return 0;
}

