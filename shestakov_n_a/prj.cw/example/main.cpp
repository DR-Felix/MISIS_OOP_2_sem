#include <niblack/niblack.hpp>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <cmath>

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

    std::string executable_path = argv[0];
    std::string input_image_path = argv[1];
    int window_size = std::atoi(argv[2]);
    double k = std::atof(argv[3]);
    int target_row = std::atoi(argv[4]);

    double scale = 1.0;

    cv::Mat image = cv::imread(input_image_path, cv::IMREAD_ANYDEPTH);

    NiblackBinarization niblack;

    niblack.setWindowSize(window_size);
    niblack.setK(k);
    niblack.setTargetRow(target_row);
    niblack.setInputImage(image);

    bool is_bw = niblack.check_the_image(image);

    if (!is_bw) {
        std::cout << "Error: Incorrect input. Image is not black-white or has another depth of coding." << std::endl;
        return -1;
    }

    if (image.empty()) {
        std::cout << "Error: Failed to upload image.\n";
        return -1;
    }

    if (window_size % 2 == 0) {
        std::cout << "Error: The window size must be an odd number!\n";
        return -1;
    }

    if (window_size <= 0) {
        std::cout << "Error: The window size must be non-negative!\n";
        return -1;
    }

    if (target_row < 1 || target_row > image.rows) {
        std::cout << "Error: Invalid row number.\n";
        std::cout << "Enter the row number (1-" << image.rows << "): ";
        return -1;
    }

    //C:\Projects_C++\OOP_2023\bin.dbg\example.exe prj.cw/example/test4.png 31 -0.5 10
    //bin.dbg\example.exe example/images/test5.png 31 -0.5 10
    //niblack_example.exe images\test5.png 31 -0.2 10

    niblack.demonstrateNiblack(image, window_size, k, target_row, executable_path);

    return 0;
}
