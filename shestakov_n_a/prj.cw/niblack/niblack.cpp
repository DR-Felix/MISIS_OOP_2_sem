#include <niblack/niblack.hpp>

NiblackBinarization::NiblackBinarization(cv::Mat& rhs) {
    NiblackBinarization niblack(rhs);
    niblack.window_size_ = 1;
    niblack.k_ = 0.2;
    niblack.target_row_ = 1;
    niblack.scale_ = 1.0;
}

NiblackBinarization::NiblackBinarization(cv::Mat& src, const int window_size, const double k, const double& scale) {
    NiblackBinarization niblack(src);
    niblack.window_size_ = window_size;
    niblack.k_ = k;
    niblack.scale_ = scale;
}

void NiblackBinarization::drawGraph(std::ofstream& file, const std::vector<double>& values, const std::string& color, const std::string& label) {
    file << "\\addplot[color=" << color << "] coordinates {";
    for (int i = 0; i < values.size(); ++i) {
        file << "(" << i << "," << values[i] << ") ";
    }
    file << "};" << std::endl;
    file << "\\addlegendentry{" << label << "}" << std::endl;
}

void NiblackBinarization::plotValues(std::filesystem::path file_path, const std::vector<double>& local_intensity, const std::vector<double>& mean_values, const std::vector<double>& variance_values, const std::vector<double>& threshold_values, int selected_row) {
    
    fs::path directoryPath = file_path.remove_filename();

    fs::path folderPath = directoryPath / "plots";

    // Create the folder if it doesn't exist
    if (!fs::exists(folderPath))
        fs::create_directory(folderPath);

    // Create the file path
    fs::path filePath = folderPath / "graph.tex";

    // Open the file
    std::ofstream file(filePath);

    if (!file)
    {
        std::cout << "Error opening file." << std::endl;
        return;
    }

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

    drawGraph(file, local_intensity, "red", "Local Intensity");
    drawGraph(file, mean_values, "blue", "Mean");
    drawGraph(file, variance_values, "green", "Variance");
    drawGraph(file, threshold_values, "purple", "Threshold");

    file << "\\end{axis}" << std::endl;
    file << "\\end{tikzpicture}" << std::endl;
    file << "\\end{document}" << std::endl;

    file.close();

    std::cout << "Graph saved to " << folderPath << std::endl;
}

bool NiblackBinarization::check_the_image(cv::Mat image) {
    if (image.depth() != 8) {
        return -1;
    }

    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
            if (pixel[0] != pixel[1] || pixel[0] != pixel[2] || pixel[1] != pixel[2]) {
                return false;
            }
        }
    }

    return true;
}

cv::Mat NiblackBinarization::niblackThreshold(const cv::Mat& src, int window_size, double k, double& scale) {
    double scale_width = static_cast<double>(800) / src.cols;
    double scale_height = static_cast<double>(600) / src.rows;
    scale = std::min(scale_width, scale_height);

    cv::Mat resized_src;
    cv::resize(src, resized_src, cv::Size(), scale, scale);

    cv::Mat img_thresh(resized_src.size(), CV_8UC1);

    int half_window_size = window_size / 2;

    for (int y = half_window_size; y < resized_src.rows - half_window_size; ++y) {
        for (int x = half_window_size; x < resized_src.cols - half_window_size; ++x) {
            double mean = 0.0;
            for (int j = -half_window_size; j <= half_window_size; ++j) {
                for (int i = -half_window_size; i <= half_window_size; ++i) {
                    mean += resized_src.at<uchar>(y + j, x + i);
                }
            }
            mean /= (window_size * window_size);

            double std_deviation = 0.0;
            for (int j = -half_window_size; j <= half_window_size; ++j) {
                for (int i = -half_window_size; i <= half_window_size; ++i) {
                    double diff = resized_src.at<uchar>(y + j, x + i) - mean;
                    std_deviation += diff * diff;
                }
            }
            std_deviation = std::sqrt(std_deviation / (window_size * window_size));

            double threshold = mean + k * std_deviation;

            if (resized_src.at<uchar>(y, x) > threshold) {
                img_thresh.at<uchar>(y, x) = 255;
            }
            else {
                img_thresh.at<uchar>(y, x) = 0;
            }
        }
    }
    resized_src.release();

    return img_thresh;
}

void NiblackBinarization::demonstrateNiblack(const cv::Mat& src, int window_size, double k, double scale, int selected_row, std::string executable_path) {
    
    std::cout << "The image is in the process of binarization, please wait..." << std::endl;

    cv::Mat img_thresh = niblackThreshold(src, window_size, k, scale);

    std::cout << "Binarization is done successfully!" << std::endl;

    cv::Mat resized_window;
    cv::resize(src, resized_window, cv::Size(), scale, scale);

    cv::Mat highlighted_image;
    cv::cvtColor(resized_window, highlighted_image, cv::COLOR_GRAY2BGR);

    cv::Scalar selected_row_color(0, 0, 255); // Red color for chosen line
    int y_selected_row = static_cast<int>(selected_row * scale);
    cv::line(highlighted_image, cv::Point(0, y_selected_row), cv::Point(highlighted_image.cols, y_selected_row), selected_row_color, 2);

    fs::path directoryPath = fs::path(executable_path).remove_filename();
    fs::path folderPath = directoryPath / "plots";

    if (!fs::exists(folderPath))
        fs::create_directory(folderPath);

    fs::path imagePath1 = folderPath / "Highlighted_image.png";
    fs::path imagePath2 = folderPath / "New_image.png";

    cv::imwrite(imagePath1.string(), highlighted_image);
    cv::imwrite(imagePath2.string(), img_thresh);

    cv::imshow("Highlighted Image", highlighted_image);
    cv::imshow("Thresholded Image", img_thresh);

    std::vector<double> local_intensity;
    std::vector<double> mean_values;
    std::vector<double> variance_values;
    std::vector<double> threshold_values;

    int half_window_size = window_size / 2;

    for (int y = half_window_size; y < img_thresh.rows - half_window_size; ++y) {
        double local_inten = 0.0;
        double mean = 0.0;
        double variance = 0.0;
        double threshold = 0.0;

        for (int x = half_window_size; x < img_thresh.cols - half_window_size; ++x) {
            local_inten += static_cast<double>(resized_window.at<uchar>(y, x)) / 3.0;

            double mean_pixel = 0.0;
            for (int j = -half_window_size; j <= half_window_size; ++j) {
                for (int i = -half_window_size; i <= half_window_size; ++i) {
                    mean_pixel += static_cast<double>(resized_window.at<uchar>(y + j, x + i)) / 3.0;
                }
            }
            mean_pixel /= (window_size * window_size);
            mean += mean_pixel;

            double variance_pixel = 0.0;
            for (int j = -half_window_size; j <= half_window_size; ++j) {
                for (int i = -half_window_size; i <= half_window_size; ++i) {
                    double diff = static_cast<double>(resized_window.at<uchar>(y + j, x + i)) / 3.0 - mean_pixel;
                    variance_pixel += diff * diff;
                }
            }
            variance_pixel /= (window_size * window_size);
            variance += variance_pixel;

            threshold = mean_pixel + k * std::sqrt(variance_pixel);
        }

        local_intensity.push_back(local_inten);
        mean_values.push_back(mean);
        variance_values.push_back(variance);
        threshold_values.push_back(threshold);
    }

    // Normalization of values to display on the graph
    double max_intensity = *std::max_element(local_intensity.begin(), local_intensity.end());
    double max_mean = *std::max_element(mean_values.begin(), mean_values.end());
    double max_variance = *std::max_element(variance_values.begin(), variance_values.end());
    double max_threshold = *std::max_element(threshold_values.begin(), threshold_values.end());

    for (size_t i = 0; i < local_intensity.size(); ++i) {
        local_intensity[i] /= max_intensity;
        mean_values[i] /= max_mean;
        variance_values[i] /= max_variance;
        threshold_values[i] /= max_threshold;
    }

    plotValues(executable_path, local_intensity, mean_values, variance_values, threshold_values, selected_row);

    local_intensity.clear();
    mean_values.clear();
    variance_values.clear();
    threshold_values.clear();

    img_thresh.release();

    cv::waitKey(0);
}
