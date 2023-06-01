#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
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



void drawGraph(std::ofstream& file, const std::vector<double>& values, const std::string& color, const std::string& label) {
    file << "\\addplot[color=" << color << "] coordinates {";
    for (int i = 0; i < values.size(); ++i) {
        file << "(" << i << "," << values[i] << ") ";
    }
    file << "};" << std::endl;
    file << "\\addlegendentry{" << label << "}" << std::endl;
}

void plotValues(const std::string& filePath, const std::vector<double>& localIntensity, const std::vector<double>& meanValues, const std::vector<double>& varianceValues, const std::vector<double>& thresholdValues, int selectedRow) {
    std::ofstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Error: Failed to open file for writing." << std::endl;
        return;
    }

    file << "\\documentclass{standalone}" << std::endl;
    file << "\\usepackage{pgfplots}" << std::endl;
    file << "\\begin{document}" << std::endl;
    file << "\\begin{tikzpicture}" << std::endl;
    file << "\\begin{axis}" << std::endl;
    file << "[xlabel=Index,ylabel=Value," << std::endl;
    file << "legend pos=outer north east," << std::endl;
    file << "legend style={cells={anchor=west},font=\\small}," << std::endl;
    file << "width=10cm,height=8cm]" << std::endl;

    drawGraph(file, localIntensity, "red", "Local Intensity");
    drawGraph(file, meanValues, "blue", "Mean");
    drawGraph(file, varianceValues, "green", "Variance");
    drawGraph(file, thresholdValues, "yellow", "Threshold");

    file << "\\end{axis}" << std::endl;
    file << "\\end{tikzpicture}" << std::endl;
    file << "\\end{document}" << std::endl;

    file.close();

    std::cout << "Graph saved to " << filePath << std::endl;
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

    plotValues("graph.tex", localIntensity, meanValues, varianceValues, thresholdValues, selectedRow);

    cv::waitKey(0);

    localIntensity.clear();
    meanValues.clear();
    varianceValues.clear();
    thresholdValues.clear();

    imgThresh.release();

}


int main(int argc, char** argv) {

    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);

    if (argc != 5) {
        std::cout << "Error: Incorrect number of command line parameters.\n";
        std::cout << "Enter the command in the format:\n";
        std::cout << "<input_image> <window_size> <k> <target_row>\n";
        std::cout << "Where:\n";
        std::cout << "<input_image> - path to the input image.\n";
        std::cout << "<window_size> - window size (integer).\n";
        std::cout << "<k> - parameter k for the Niblack algorithm (floating point number).\n";
        std::cout << "<target_row> - row number for which to display the parameter graph.\n";
        return -1;
    }

    std::string inputImagePath = argv[1];
    int windowSize = std::atoi(argv[2]);
    double k = std::atof(argv[3]);
    int targetRow = std::atoi(argv[4]);

    double scale = 1;

    cv::Mat image = cv::imread(inputImagePath, cv::IMREAD_GRAYSCALE);

    if (image.empty()) {
        std::cout << "Error: Failed to upload image.\n";
        return -1;
    }

    if (targetRow < 1 || targetRow > image.rows) {
        std::cout << "Error: Invalid row number.\n";
        std::cout << "Enter the row number (1-" << image.rows << "): ";
        return -1;
    }

    //C:/Projects_C++/OOP_2023/bin.dbg/course_test.exe prj.cw/test.png 31 -0.5 10

    demonstrateNiblack(image, windowSize, k, scale, targetRow);

    return 0;
}
