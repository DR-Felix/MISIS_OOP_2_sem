#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat niblackThreshold(const cv::Mat& src, int windowSize, double k) {
    cv::Mat imgGray;
    cv::cvtColor(src, imgGray, cv::COLOR_BGR2GRAY);

    cv::Mat imgThresh;
    cv::adaptiveThreshold(imgGray, imgThresh, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, windowSize, k);

    return imgThresh;
}

void demonstrateNiblack(const cv::Mat& src, int windowSize, double k) {
    cv::Mat imgThresh = niblackThreshold(src, windowSize, k);

    cv::imshow("Original Image", src);
    cv::imshow("Thresholded Image", imgThresh);
    cv::waitKey(0);
}

void showImagesTogether(const cv::Mat& img1, const cv::Mat& img2, const std::string& label1, const std::string& label2) {
    //// Создаем разделительную линию
    //cv::Mat separator(img1.rows, 10, CV_8UC3, cv::Scalar(255, 255, 255));

    //// Создаем изображение с подписями
    //cv::Mat labeledImg;
    //std::cout << img1.size() << img1.type() << std::endl;
    //std::cout << img2.size() << img2.type() << std::endl;
    //std::cout << img1.size() << separator.type() << std::endl;
    //cv::vconcat(img1, separator, labeledImg);
    //cv::vconcat(labeledImg, img2, labeledImg);

    // Добавляем подписи
   /* cv::putText(labeledImg, label1, cv::Point(10, img1.rows + 20), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);
    cv::putText(labeledImg, label2, cv::Point(10, img1.rows + separator.rows + 40), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(255, 255, 255), 2);*/

    cv::imshow("Combined Images", img1);
    cv::waitKey(0);
    cv::imshow("Combined Images", img2);
    cv::waitKey(0);
}

int main() {
    cv::Mat image = cv::imread("C:/Users/nick_/Downloads/test.jpg");

    if (image.empty()) {
        std::cout << "Failed to load image." << std::endl;
        return -1;
    }

    int windowSize = 21;
    double k = -0.2;

    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(800, 600));

    cv::Mat imgThresh = niblackThreshold(resizedImage, windowSize, k);

    showImagesTogether(resizedImage, imgThresh, "Original Image", "Thresholded Image");

    return 0;
}
