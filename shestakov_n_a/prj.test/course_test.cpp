#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

cv::Mat niblackThreshold(const cv::Mat& src, int windowSize, double k, double& scale) {

    double scaleWidth = static_cast<double>(800) / src.cols;
    double scaleHeight = static_cast<double>(600) / src.rows;
    scale = std::min(scaleWidth, scaleHeight);

    cv::Mat resizedSrc;
    cv::resize(src, resizedSrc, cv::Size(), scale, scale);

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
    resizedSrc.release();

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

cv::Mat plotValues(cv::Mat& plotImage, const std::vector<double>& localIntensity, const std::vector<double>& meanValues, const std::vector<double>& varianceValues, const std::vector<double>& thresholdValues, int selectedRow) {
    int plotWidth = plotImage.cols;
    int plotHeight = plotImage.rows;

    int numDataPoints = localIntensity.size();
    double dx = static_cast<double>(plotWidth) / static_cast<double>(numDataPoints - 1);

    std::vector<cv::Point> localIntensityPoints;
    std::vector<cv::Point> meanPoints;
    std::vector<cv::Point> variancePoints;
    std::vector<cv::Point> thresholdPoints;

    for (int i = 0; i < numDataPoints; ++i) {
        int x = static_cast<int>(i * dx);
        int yLocalIntensity = static_cast<int>((1.0 - localIntensity[i]) * (plotHeight - 1));
        int yMean = static_cast<int>((1.0 - meanValues[i]) * (plotHeight - 1));
        int yVariance = static_cast<int>((1.0 - varianceValues[i]) * (plotHeight - 1));
        int yThreshold = static_cast<int>((1.0 - thresholdValues[i]) * (plotHeight - 1));

        localIntensityPoints.emplace_back(x, yLocalIntensity);
        meanPoints.emplace_back(x, yMean);
        variancePoints.emplace_back(x, yVariance);
        thresholdPoints.emplace_back(x, yThreshold);
    }

    cv::Scalar localIntensityColor(255, 0, 0);   // Красный цвет для local intensity
    cv::Scalar meanColor(0, 0, 255);              // Синий цвет для mean
    cv::Scalar varianceColor(0, 255, 0);          // Зеленый цвет для variance
    cv::Scalar thresholdColor(0, 255, 255);       // Желтый цвет для threshold

    // Отображение графика
    for (int i = 1; i < numDataPoints; ++i) {
        cv::Point point1 = localIntensityPoints[i - 1];
        cv::Point point2 = localIntensityPoints[i];

        if (point1.inside(cv::Rect(0, 0, plotImage.cols, plotImage.rows)) && point2.inside(cv::Rect(0, 0, plotImage.cols, plotImage.rows))) {
            cv::line(plotImage, point1, point2, localIntensityColor);
        }
    }

    for (int i = 1; i < numDataPoints; ++i) {
        cv::Point point1 = meanPoints[i - 1];
        cv::Point point2 = meanPoints[i];

        if (point1.inside(cv::Rect(0, 0, plotImage.cols, plotImage.rows)) && point2.inside(cv::Rect(0, 0, plotImage.cols, plotImage.rows))) {
            cv::line(plotImage, point1, point2, meanColor);
        }
    }

    for (int i = 1; i < numDataPoints; ++i) {
        cv::Point point1 = variancePoints[i - 1];
        cv::Point point2 = variancePoints[i];

        if (point1.inside(cv::Rect(0, 0, plotImage.cols, plotImage.rows)) && point2.inside(cv::Rect(0, 0, plotImage.cols, plotImage.rows))) {
            cv::line(plotImage, point1, point2, varianceColor);
        }
    }

    for (int i = 1; i < numDataPoints; ++i) {
        cv::Point point1 = thresholdPoints[i - 1];
        cv::Point point2 = thresholdPoints[i];

        if (point1.inside(cv::Rect(0, 0, plotImage.cols, plotImage.rows)) && point2.inside(cv::Rect(0, 0, plotImage.cols, plotImage.rows))) {
            cv::line(plotImage, point1, point2, thresholdColor);
        }
    }

    //// Отметить выбранную строку
    //if (selectedRow >= 0 && selectedRow < plotHeight) {
    //    cv::line(plotImage, cv::Point(0, selectedRow), cv::Point(plotWidth - 1, selectedRow), cv::Scalar(0, 0, 0));
    //}

    return plotImage;
}



void demonstrateNiblack(const cv::Mat& src, int windowSize, double k, double& scale, int selectedRow) {
    cv::Mat imgThresh = niblackThreshold(src, windowSize, k, scale);

    cv::Mat resizedWindow;
    cv::resize(src, resizedWindow, cv::Size(), scale, scale);

    cv::Mat highlightedImage = resizedWindow.clone();
    cv::Scalar selectedRowColor(0, 0, 255);   // Синий цвет для выбранной строки

    int ySelectedRow = static_cast<int>(selectedRow * scale);
    cv::line(highlightedImage, cv::Point(0, ySelectedRow), cv::Point(highlightedImage.cols, ySelectedRow), selectedRowColor, 2);

    cv::imshow("Highlighted Image", highlightedImage);

    cv::imshow("Thresholded Image", imgThresh);

    cv::Mat plotImage(800, 600, CV_8UC3, cv::Scalar(255, 255, 255));

    std::vector<double> localIntensity;
    std::vector<double> meanValues;
    std::vector<double> varianceValues;
    std::vector<double> thresholdValues;

    int halfWindowSize = windowSize / 2;
    for (int y = halfWindowSize; y < imgThresh.rows - halfWindowSize; ++y) {
        double localInten = 0.0;
        double mean = 0.0;
        double variance = 0.0;
        double threshold = 0.0;

        for (int x = halfWindowSize; x < imgThresh.cols - halfWindowSize; ++x) {
            localInten += static_cast<double>(src.at<uchar>(y, x)) / 3.0;

            double meanPixel = 0.0;
            for (int j = -halfWindowSize; j <= halfWindowSize; ++j) {
                for (int i = -halfWindowSize; i <= halfWindowSize; ++i) {
                    meanPixel += static_cast<double>(src.at<uchar>(y + j, x + i)) / 3.0;
                }
            }
            meanPixel /= (windowSize * windowSize);
            mean += meanPixel;

            double variancePixel = 0.0;
            for (int j = -halfWindowSize; j <= halfWindowSize; ++j) {
                for (int i = -halfWindowSize; i <= halfWindowSize; ++i) {
                    double diff = static_cast<double>(src.at<uchar>(y + j, x + i)) / 3.0 - meanPixel;
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
    }

    // Нормализация значений для отображения на графике
    double maxIntensity = *std::max_element(localIntensity.begin(), localIntensity.end());
    double maxMean = *std::max_element(meanValues.begin(), meanValues.end());
    double maxVariance = *std::max_element(varianceValues.begin(), varianceValues.end());
    double maxThreshold = *std::max_element(thresholdValues.begin(), thresholdValues.end());

    for (size_t i = 0; i < localIntensity.size(); ++i) {
        localIntensity[i] /= maxIntensity;
        meanValues[i] /= maxMean;
        varianceValues[i] /= maxVariance;
        thresholdValues[i] /= maxThreshold;
    }

    cv::Mat plotGraph = plotValues(plotImage, localIntensity, meanValues, varianceValues, thresholdValues, selectedRow);

    cv::imshow("Row Parameters", plotGraph);
    cv::waitKey(0);

    plotGraph.release();

    localIntensity.clear();
    meanValues.clear();
    varianceValues.clear();
    thresholdValues.clear();

    imgThresh.release();

}


int main(int argc, char** argv) {
    std::cout << "Enter the command in the format:\n";
    std::cout << "<input_image> <window_size> <k> <target_row>\n";
    std::cout << "Where:\n";
    std::cout << "<input_image> - path to the input image.\n";
    std::cout << "<window_size> - window size (integer).\n";
    std::cout << "<k> - parameter k for the Niblack algorithm (floating point number).\n";
    std::cout << "<target_row> - row number for which to display the parameter graph.\n";

    if (argc != 5) {
        std::cout << "Error: Incorrect number of command line parameters.\n";
        std::cout << "The correct command format is: <input_image> <window_size> <k> <target_row>\n";
        return -1;
    }

    std::string inputImagePath = argv[1];
    int windowSize = std::atoi(argv[2]);
    double k = std::atof(argv[3]);
    int targetRow = std::atoi(argv[4]);

    double scale = 1;

    cv::Mat image = cv::imread(inputImagePath, cv::IMREAD_GRAYSCALE);

    int type = image.type();
    int depth = image.depth();

    std::cout << "Тип данных: " << type << std::endl;
    std::cout << "Глубина цвета: " << depth << std::endl;


    if (image.empty()) {
        std::cout << "Error: Failed to upload image.\n";
        return -1;
    }

    if (targetRow < 1 || targetRow > image.rows) {
        std::cout << "Error: Invalid row number.\n";
        std::cout << "Enter the row number (1-" << image.rows << "): ";
        return -1;
    }

    //C:\Projects_C++\OOP_2023\bin.dbg\course_test.exe C:\Users\nick_\Downloads\test.png 31 -0.5 10

    demonstrateNiblack(image, windowSize, k, scale, targetRow);

    return 0;
}
