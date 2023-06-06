#ifndef NIBLACKBINARIZATION_H
#define NIBLACKBINARIZATION_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

/**
 * @brief Namespace for std::filesystem methods
 */
namespace fs = std::filesystem;

/**
 * @brief A class for calculating, demonstrating and visualizing the threshold value using the Niblack method
 */
class NiblackBinarization {
public:
    /**
    * @brief Default constructor for the NiblackBinariation class
    */
    NiblackBinarization() = default;

    /**
    * @brief Copy constructor for the NiblackBinariation class
    * @param[in] cv::Mat& rhs - input image
    */
    NiblackBinarization(cv::Mat& rhs);

    /**
    * @brief Copy constructor for the NiblackBinariation class
    * @param[in] cv::Mat& src - input image
    * @param[in] window_size, determining the window size for the algorithm
    * @param[in] k - coefficient affecting the threshold value
    * @param[in] scale - the coefficient with which the graph will be scaled (default = 1)
    */
    NiblackBinarization(cv::Mat& src, const int window_size, const double k, const double& scale);

    /**
    * @brief Destructor for the NiblackBinariation class
    */
    ~NiblackBinarization() = default;

    /**
     * @brief Access operator for the NiblackBinarization class
     * @param[in] rhs NiblackBinarization - copyied object
     * @return NiblackBinarization&
     */
    NiblackBinarization& operator=(const NiblackBinarization& rhs);

    /**
     * @brief A method that checks the correctness of the image format
     * @param[in] cv::Mat image - input image
     * @return true/false
     */
    bool check_the_image(cv::Mat image);

    /**
     * @brief Method that performs image binarization using the Niblack method
     * @param[in] cv::Mat& src - input image
     * @param[in] window_size, determining the window size for the algorithm
     * @param[in] k - coefficient affecting the threshold value
     * @param[in] scale - the coefficient with which the graph will be scaled (default = 1)
     * @return cv::Mat object after binarization
     */
    cv::Mat niblackThreshold(const cv::Mat& src, int window_size, double k, double& scale);

    /**
     * @brief Method that demonstrates the source and from the binarized image obtained by calling the niblackThreshold method
     * @param[in] cv::Mat& src - input image
     * @param[in] window_size, determining the window size for the algorithm
     * @param[in] k - coefficient affecting the threshold value
     * @param[in] scale - the coefficient with which the graph will be scaled (default = 1)
     * @param[in] selected_row - the row for which the visualization will be performed
     * @param[in] executable_path - the path for the executable file to pass what to plotValues-method for visualization
     */
    void demonstrateNiblack(const cv::Mat& src, int window_size, double k, double scale, int selected_row, std::string executable_path);

    /**
     * @brief a method that stores the coordinates of points in a .tex file for visualization
     * @param[in] file - file for recording coordinates
     * @param[in] values - array of coordinates of points
     * @param[in] color - line color on the chart
     * @param[in] label - the inscription in the legend of the graph
    */
    void drawGraph(std::ofstream& file, const std::vector<double>& values, const std::string& color, const std::string& label);

    /**
     * @brief The method in which the structure of the .tex file is formed, as well as its contents, by calling the drawGraph method
     * @param filePath - the path to the executable file next to which the .tex file will be generated
     * @param localIntensity - array of vectors with local intensity values
     * @param meanValues - array of vectors with mean brightness values
     * @param varianceValues - array of vectors with standart deviation values
     * @param thresholdValues - array of threshold value vectors 
     * @param selectedRow - the number of the row selected for visualization
    */
    void plotValues(const std::string& filePath, const std::vector<double>& localIntensity, const std::vector<double>& meanValues, const std::vector<double>& varianceValues, const std::vector<double>& thresholdValues, int selectedRow);

    /**
     * @brief window_size setter
     * @param[in] window_size, determining the window size for the algorithm
    */
    void setWindowSize(int window_size) {
        window_size_ = window_size;
    }

    /**
     * @brief K setter
     * @param[in] k - coefficient affecting the threshold value
    */
    void setK(double k) {
        k_ = k;
    }

    /**
     * @brief target_row setter
     * @param[in] target_row - the row for which the visualization will be performed
    */
    void setTargetRow(int target_row) {
        target_row_ = target_row;
    }

    /**
     * @brief image setter
     * @param[in] image - input image
    */
    void setInputImage(const cv::Mat& image) {
        image_ = image.clone();
    }

private:
    cv::Mat image_; /*image_ - input image */
    int window_size_ = 1; /*window_size_, determining the window size for the algorithm */
    double k_ = 0.2; /*k - coefficient affecting the threshold value*/
    int target_row_ = 1; /*target_row - the row for which the visualization will be performed*/
    double scale_ = 1.0; /*scale - the coefficient with which the graph will be scaled (default = 1)*/
};

#endif NIBLACKBINARIZATION_H