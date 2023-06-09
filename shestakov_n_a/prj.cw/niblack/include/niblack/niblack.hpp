#ifndef NIBLACKBINARIZATION_H
#define NIBLACKBINARIZATION_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Класс для расчета, демонстрации и визуализации порогового значения по методу Ниблэка
 */
class NiblackBinarization {
public:
    /**
    * @brief Конструктор по умолчанию для класса NiblackBinariation
    */
    NiblackBinarization() = default;

    /**
    * @brief Конструктор копирования для класса NiblackBinariation
    * @param[in] cv::Mat& rhs матрица, для которой будет применен алгоритм
    */
    NiblackBinarization(cv::Mat& rhs);

    /**
    * @brief Конструктор копирования для класса NiblackBinariation
    * @param[in] cv::Mat& src матрица, для которой будет применен алгоритм
    * @param[in] window_siz - размер окна, в котором будет происходить бинаризация
    * @param[in] k - коэффициент, влияющий на величину порогового значения
    */
    NiblackBinarization(cv::Mat& src, const int window_size, const double k);

    /**
    * @brief Деструктор для класса NiblackBinariation
    */
    ~NiblackBinarization() = default;

    /**
     * @brief Оператор доступа для класса NiblackBinarization
     * @param[in] rhs NiblackBinarization - копируемый объект
     * @return NiblackBinarization&
     */
    NiblackBinarization& operator=(const NiblackBinarization& rhs);

    /**
     * @brief Метод, который проверяет корректность формата изображения
     * @param[in] cv::Mat image - входное изображение на проверку
     * @return true/false
     */
    bool check_the_image(cv::Mat image);

    /**
     * @brief Метод, выполняющий бинаризацию изображения по методу Ниблэка
     * @param[in] cv::Mat& src - входное изображение
     * @param[in] window_size - размер области, в котором будет осуществляться бинаризация
     * @param[in] k - коэффициент, влияющий на величину порогового значения
     * @return cv::Mat object после бинаризации
     */
    cv::Mat niblackThreshold(const cv::Mat& src, int window_size, double k);

    /**
     * @brief Метод, осуществляющий демонстрацию исходного и отбинаризованного изображения, полученного с помощью вызова niblackThreshold-метода
     * @param[in] cv::Mat& src - входное изображение
     * @param[in] window_size - размер области, в котором будет осуществляться бинаризация
     * @param[in] k - коэффициент, влияющий на величину порогового значения
     * @param[in] selected_row - ряд, для которого будет осуществляться визуализация
     * @param[in] executable_path - путь для исполняемого файла для передачи чего в plotValues-метода для визуализации
     */
    void demonstrateNiblack(const cv::Mat& src, int window_size, double k, int selected_row, std::string executable_path);

    /**
     * @brief метод, сохраняющий координаты точек в .tex-файл для визуализации
     * @param[in] file - файл для записи координат
     * @param[in] values - массив координат точек
     * @param[in] color - цвет линии на графике
     * @param[in] label - надпись в легенде графика
    */
    void drawGraph(std::ofstream& file, const std::vector<double>& values, const std::string& color, const std::string& label);

    /**
     * @brief Метод, в котором формируется структура .tex-файла, а также его содержимое посредством вызова drawGraph-метода
     * @param filePath - путь к исполняему файлу, рядом с которым будет сгенерирован .tex-файл
     * @param localIntensity - массив векторов со значениями локальной интенсивности
     * @param meanValues - массив векторов со значениями средней яркости
     * @param varianceValues - массив векторов со значениями среднего отклонения
     * @param thresholdValues - массив векторов порогового значения 
     * @param selectedRow - номер выбранной для визуализации линии
    */
    void plotValues(std::filesystem::path filePath, const std::vector<double>& localIntensity, const std::vector<double>& meanValues, const std::vector<double>& varianceValues, const std::vector<double>& thresholdValues, int selectedRow);

    /**
     * @brief Сеттер для window_size
     * @param[in] window_size - размер области, в котором будет осуществляться бинаризация
    */
    void setWindowSize(int window_size) {
        window_size_ = window_size;
    }

    /**
     * @brief Сеттер для k
     * @param[in] k - коэффициент, влияющий на величину порогового значения
    */
    void setK(double k) {
        k_ = k;
    }

    /**
     * @brief Сеттер для target_row
     * @param[in] target_row - ряд, для которого будет осуществляться визуализация
    */
    void setTargetRow(int target_row) {
        target_row_ = target_row;
    }

    /**
     * @brief Сеттер для image
     * @param[in] image - входное изображение
    */
    void setInputImage(const cv::Mat& image) {
        image_ = image.clone();
    }

private:
    cv::Mat image_; /*image_ - входное изображение */
    int window_size_ = 1; /*window_size_ - азмер области, в котором будет осуществляться бинаризация */
    double k_ = 0.2; /*k - коэффициент, влияющий на величину порогового значения*/
    int target_row_ = 1; /*target_row - ряд, для которого будет осуществляться визуализация*/
};

#endif NIBLACKBINARIZATION_H