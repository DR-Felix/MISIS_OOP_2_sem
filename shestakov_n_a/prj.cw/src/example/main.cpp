#include <niblack/niblack.hpp>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <cmath>

int main(int argc, char** argv) {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_ERROR);

    system("chcp 65001");
    std::string OutputDirectory;
    std::string InputDirectory;

    std::string executable_path = argv[0];

    bool savingInFile = false;
    bool demonstration = false;
    bool visualization = false;

    int window_size = 31;
    double k = -0.2;
    int target_row = 10;

    if (argc == 1) {
        std::cout << "Описание доступных команд\n";
        std::cout << "-M : Сохранить результат бинаризации в стандартную директорию" << '\n';
        std::cout << "-D : Вывести исходное и отбинаризованное изображение в двух окнах" << '\n';
        std::cout << "-V : Визуализировать параметры алгоритма в graph.tex" << '\n';
        std::cout << "-w : Ввести параметр-значение размера окна бинаризации" << '\n';
        std::cout << "-k : Ввести параметр-значение коэффициента бинаризации" << '\n';
        std::cout << "-t : Ввести параметр-значение ряда, для которого будет выполнена визуализация" << '\n';
        std::cout << "Следующие команды нужно использовать по образцу: -[command]=[way]" << '\n';
        std::cout << "-l : Указать путь к изображению" << '\n';
        std::cout << "-s : Указать путь для сохранения изображения" << '\n';
        std::cout << "Помощь:" << '\n';
        std::cout << "-h : Показать возможные команды" << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (static_cast<std::string>(argv[i]) == "-M") {
            savingInFile = true;
        }
        else if (static_cast<std::string>(argv[i]) == "-D") {
            demonstration = true;
        }
        else if (static_cast<std::string>(argv[i]) == "-V") {
            visualization = true;
        }
        else if (static_cast<std::string>(argv[i]) == "-h") {
            std::cout << "Описание доступных команд\n";
            std::cout << "-M : Сохранить результат бинаризации в стандартную директорию" << '\n';
            std::cout << "-D : Вывести исходное и отбинаризованное изображение в двух окнах" << '\n';
            std::cout << "-V : Визуализировать параметры алгоритма в graph.tex" << '\n';
            std::cout << "-w : Ввести параметр-значение размера окна бинаризации" << '\n';
            std::cout << "-k : Ввести параметр-значение коэффициента бинаризации" << '\n';
            std::cout << "-t : Ввести параметр-значение ряда, для которого будет выполнена визуализация" << '\n';
            std::cout << "Следующие команды нужно использовать по образцу: -[command]=[way]" << '\n';
            std::cout << "-l : Указать путь к изображению" << '\n';
            std::cout << "-s : Указать путь для сохранения изображения" << '\n';
            std::cout << "Помощь:" << '\n';
            std::cout << "-h : Показать возможные команды" << std::endl;
            return 0;
        }
        else if (static_cast<std::string>(argv[i]).size() > 2) {
            std::string param = static_cast<std::string>(argv[i]);
            if (param[0] == '-' && param[2] == '=') {
                if (param[1] == 'l') {
                    InputDirectory = param.substr(3, param.size() - 3);
                }
                else if (param[1] == 's') {
                    OutputDirectory = param.substr(3, param.size() - 3);
                }
                else if (param[1] == 'w') {
                    std::string value = param.substr(3, param.size() - 3);
                    try {
                        window_size = std::stoi(value);
                        if (window_size % 2 == 0) {
                            std::cout << "Error: The window size must be an odd integer!\n";
                            return -1;
                        }
                        if (window_size <= 0) {
                            std::cout << "Error: The window size must be a positive integer!\n";
                            return -1;
                        }
                    }
                    catch (const std::invalid_argument& e) {
                        std::cout << "Error: Invalid window size!\n";
                        return -1;
                    }
                    catch (const std::out_of_range& e) {
                        std::cout << "Error: Window size out of range!\n";
                        return -1;
                    }
                }
                else if (param[1] == 'k') {
                    std::string value = param.substr(3, param.size() - 3);
                    try {
                        k = std::stof(value);
                    }
                    catch (const std::invalid_argument& e) {
                        std::cout << "Error: Invalid value for k!\n";
                        return -1;
                    }
                    catch (const std::out_of_range& e) {
                        std::cout << "Error: Value for k out of range!\n";
                        return -1;
                    }
                }
                else if (param[1] == 't' && visualization) {
                    cv::Mat image1 = cv::imread(InputDirectory, cv::IMREAD_ANYDEPTH);

                    target_row = std::stod(param.substr(3, param.size() - 3));

                    if (target_row < 1 || target_row > image1.rows) {
                        std::cout << "Error: Invalid row number.\n";
                        std::cout << "Enter the row number (1-" << image1.rows << "): ";
                        return -1;
                    }
                }
                else {
                    throw std::invalid_argument("invalid argument");
                }
            }
            else {
                throw std::invalid_argument("invalid argument");
            }
        }
        else {
            throw std::invalid_argument("invalid argument");
        }

    }

    cv::Mat image = cv::imread(InputDirectory, cv::IMREAD_ANYDEPTH);

    NiblackBinarization niblack;

    bool is_bw = niblack.check_the_image(image);

    if (!is_bw) {
        std::cout << "Error: Incorrect input. Image is not black-white or has another depth of coding." << std::endl;
        return -1;
    }

    if (image.empty()) {
        std::cout << "Error: Failed to upload image.\n";
        return 1;
    }

    if (savingInFile) {
        cv::Mat image = cv::imread(InputDirectory, cv::IMREAD_ANYDEPTH);
        NiblackBinarization niblack;

        niblack.setWindowSize(window_size);
        niblack.setK(k);
        niblack.setTargetRow(target_row);

        cv::Mat result = niblack.niblackThreshold(image, window_size, k);

        niblack.saveTheImage(result, OutputDirectory, "Thresholded_Image.png");
    }

    if (demonstration) {
        cv::Mat image = cv::imread(InputDirectory, cv::IMREAD_ANYDEPTH);
        NiblackBinarization niblack;

        niblack.setWindowSize(window_size);
        niblack.setK(k);
        niblack.setTargetRow(target_row);

        cv::Mat result = niblack.niblackThreshold(image, window_size, k);

        cv::imshow("Old Image", image);
        cv::imshow("Thresholded Image", result);

        cv::waitKey(0);
        cv::destroyAllWindows();
    }
    if (visualization) {
        cv::Mat image = cv::imread(InputDirectory, cv::IMREAD_ANYDEPTH);
        NiblackBinarization niblack;

        niblack.setWindowSize(window_size);
        niblack.setK(k);
        niblack.setTargetRow(target_row);

        niblack.visualizationNiblack(image, window_size, k, target_row, OutputDirectory);
    }

    /*std::string executable_path = argv[0];
    std::string input_image_path = argv[1];
    int window_size = std::atoi(argv[2]);
    double k = std::atof(argv[3]);
    int target_row = std::atoi(argv[4]);

    cv::Mat image = cv::imread(input_image_path, cv::IMREAD_ANYDEPTH);*/

    //NiblackBinarization niblack;

    //niblack.setWindowSize(window_size);
    //niblack.setK(k);
    //niblack.setTargetRow(target_row);
    /*niblack.setInputImage(image);

    bool is_bw = niblack.check_the_image(image);

    if (!is_bw) {
        std::cout << "Error: Incorrect input. Image is not black-white or has another depth of coding." << std::endl;
        return -1;
    }

    if (image.empty()) {
        std::cout << "Error: Failed to upload image.\n";
        return -1;
    }*/

    /*if (window_size % 2 == 0) {
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
    }*/

    //C:\Projects_C++\OOP_2023\bin.dbg\example.exe prj.cw/example/test4.png 31 -0.5 10
    //bin.dbg\example.exe example/images/test5.png 31 -0.5 10
    //niblack_example.exe images\test5.png 31 -0.2 10

    return 0;
}
