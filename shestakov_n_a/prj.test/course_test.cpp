#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

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

void drawGraph(cv::Mat& plotImage, const std::vector<double>& values, cv::Scalar color) {
    int graphWidth = plotImage.cols - 100;
    int graphHeight = plotImage.rows - 100;
    double xScale = static_cast<double>(graphWidth) / values.size();
    double yScale = static_cast<double>(graphHeight) / 255.0;

    for (int i = 0; i < values.size() - 1; ++i) {
        int x1 = 50 + static_cast<int>(i * xScale);
        int x2 = 50 + static_cast<int>((i + 1) * xScale);
        int y1 = plotImage.rows - 50 - static_cast<int>(values[i] * yScale);
        int y2 = plotImage.rows - 50 - static_cast<int>(values[i + 1] * yScale);
        cv::line(plotImage, cv::Point(x1, y1), cv::Point(x2, y2), color, 2);
    }
}

void demonstrateNiblack(const cv::Mat& src, int windowSize, double k, double& scale, int selectedRow) {
    cv::Mat imgThresh = niblackThreshold(src, windowSize, k, scale);

    cv::Mat resizedWindow;
    cv::resize(src, resizedWindow, cv::Size(), scale, scale);

    cv::imshow("Original Image", resizedWindow);
    cv::imshow("Thresholded Image", imgThresh);

    cv::Mat plotImage(800, 600, CV_8UC3, cv::Scalar(255, 255, 255));

    std::vector<double> localIntensity;
    std::vector<double> meanValues;
    std::vector<double> varianceValues;
    std::vector<double> thresholdValues;

    int halfWindowSize = windowSize / 2;
    if (selectedRow >= halfWindowSize && selectedRow < imgThresh.rows - halfWindowSize) {
        double localInten = 0.0;
        double mean = 0.0;
        double variance = 0.0;
        double threshold = 0.0;

        int y = selectedRow;

        for (int x = halfWindowSize; x < imgThresh.cols - halfWindowSize; ++x) {
            localInten += static_cast<double>(src.at<cv::Vec3b>(y, x)[0]) / 3.0;

            double meanPixel = 0.0;
            for (int j = -halfWindowSize; j <= halfWindowSize; ++j) {
                for (int i = -halfWindowSize; i <= halfWindowSize; ++i) {
                    meanPixel += static_cast<double>(src.at<cv::Vec3b>(y + j, x + i)[0]) / 3.0;
                }
            }
            meanPixel /= (windowSize * windowSize);
            mean += meanPixel;

            double variancePixel = 0.0;
            for (int j = -halfWindowSize; j <= halfWindowSize; ++j) {
                for (int i = -halfWindowSize; i <= halfWindowSize; ++i) {
                    double diff = static_cast<double>(src.at<cv::Vec3b>(y + j, x + i)[0]) / 3.0 - meanPixel;
                    variancePixel += diff * diff;
                }
            }
            variancePixel /= (windowSize * windowSize);
            variance += variancePixel;

            double thresholdPixel = meanPixel + k * std::sqrt(variancePixel);
            threshold += thresholdPixel;
        }

        localInten /= (imgThresh.cols - 2 * halfWindowSize);
        mean /= (imgThresh.cols - 2 * halfWindowSize);
        variance /= (imgThresh.cols - 2 * halfWindowSize);
        threshold /= (imgThresh.cols - 2 * halfWindowSize);

        localIntensity.push_back(localInten);
        meanValues.push_back(mean);
        varianceValues.push_back(variance);
        thresholdValues.push_back(threshold);

        // Нормализация значений для отображения на графике
        double maxIntensity = *std::max_element(localIntensity.begin(), localIntensity.end());
        double maxMean = *std::max_element(meanValues.begin(), meanValues.end());
        double maxVariance = *std::max_element(varianceValues.begin(), varianceValues.end());
        double maxThreshold = *std::max_element(thresholdValues.begin(), thresholdValues.end());

        for (auto& value : localIntensity) {
            value = value / maxIntensity * 255.0;
        }

        for (auto& value : meanValues) {
            value = value / maxMean * 255.0;
        }

        for (auto& value : varianceValues) {
            value = value / maxVariance * 255.0;
        }

        for (auto& value : thresholdValues) {
            value = value / maxThreshold * 255.0;
        }

        // Отображение графиков на изображении
        drawGraph(plotImage, meanValues, cv::Scalar(0, 255, 0));          // Mean (зеленый)
        drawGraph(plotImage, varianceValues, cv::Scalar(0, 0, 255));      // Variance (красный)
        drawGraph(plotImage, thresholdValues, cv::Scalar(255, 0, 0));     // Actual Threshold (синий)

        cv::imshow("Mean Brightness Graph", plotImage); // Отображение графика
        cv::waitKey(0);
    }
    else {
        std::cout << "Error: Selected row is out of range.\n";
    }
}

int main(int argc, char** argv) {

    std::cout << "Enter the command in the format:\n";
    std::cout << "<input_image> <window_size> <k> <selected_row>\n";
    std::cout << "Where:\n";
    std::cout << "<input_image> - path to the input image.\n";
    std::cout << "<window_size> - window size (integer).\n";
    std::cout << "<k> - parameter k for the Niblack algorithm (floating point number).\n";
    std::cout << "<selected_row> - the row number for which to display the graphs.\n";

    if (argc != 5) {
        std::cout << "Error: Incorrect number of command line parameters.\n";
        std::cout << "The correct command format is: <input_image> <window_size> <k> <selected_row>\n";
        return -1;
    }

    std::string inputImagePath = argv[1];
    int windowSize = std::atoi(argv[2]);
    double k = std::atof(argv[3]);
    int selectedRow = std::atoi(argv[4]);

    double scale;

    cv::Mat image = cv::imread(inputImagePath);

    if (image.empty()) {
        std::cout << "Error: Failed to load image.\n";
        return -1;
    }

    demonstrateNiblack(image, windowSize, k, scale, selectedRow);

    return 0;
}
// C:\Projects_C++\OOP_2023\bin.dbg\course_test.exe C:\Users\nick_\Downloads\test1.jpg 31 0,2 5
