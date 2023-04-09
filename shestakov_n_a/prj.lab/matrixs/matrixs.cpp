#include <matrixs/matrixs.hpp>
#include <stdexcept>
#include <tuple>

MatrixS::MatrixS(const SizeType& size) {
    if (std::get<0>(size) < 0 || std::get<1>(size) < 0) { 
        throw std::invalid_argument("invalid size"); 
    }
    std::get<0>(size_) = std::get<0>(size);
    std::get<1>(size_) = std::get<1>(size);
    data_ = new int[std::get<0>(size_) * std::get<1>(size_)];
    for (int i = 0; i < std::get<0>(size_) * std::get<1>(size_); i++) {
        data_[i] = 0;
    }
}

MatrixS::MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n) {
    if (m < 0 || n < 0) { 
        throw std::invalid_argument("invalid size"); 
    }
    std::get<0>(size_) = m;
    std::get<1>(size_) = n;
    data_ = new int[std::get<0>(size_) * std::get<1>(size_)];
    for (int i = 0; i < std::get<0>(size_) * std::get<1>(size_); i++) {
        data_[i] = 0;
    }
}

MatrixS::MatrixS(const MatrixS& other) {
    std::get<0>(size_) = other.nRows();
    std::get<1>(size_) = other.nCols();
    data_ = new int[std::get<0>(size_) * std::get<1>(size_)];
    for (int i = 0; i < std::get<0>(size_) * std::get<1>(size_); i++) {
        data_[i] = other.at(i / std::get<1>(size_), i % std::get<0>(size_));
    }
}

MatrixS& MatrixS::operator=(const MatrixS& other) {
    delete[] data_;
    std::get<0>(size_) = other.nRows();
    std::get<1>(size_) = other.nCols();
    data_ = new int[std::get<0>(size_) * std::get<1>(size_)];
    for (int i = 0; i < std::get<0>(size_) * std::get<1>(size_); i++) {
        data_[i] = other.at(i / std::get<1>(size_), i % std::get<1>(size_));
    }
}

[[nodiscard]] const int& MatrixS::at(const SizeType& indexs) const {
    std::ptrdiff_t index_row = std::get<0>(indexs);
    std::ptrdiff_t index_col = std::get<1>(indexs);
    if (index_row >= std::get<0>(size_) || index_row < 0 || index_col >= std::get<1>(size_) || index_col < 0) { 
        throw std::out_of_range("invalid index"); 
    }
    return data_[std::get<1>(size_) * index_row + index_col];
}
[[nodiscard]] int& MatrixS::at(const SizeType& indexs) {
    std::ptrdiff_t index_row = std::get<0>(indexs);
    std::ptrdiff_t index_col = std::get<1>(indexs);
    if (index_row >= std::get<0>(size_) || index_row < 0 || index_col >= std::get<1>(size_) || index_col < 0) { 
        throw std::out_of_range("invalid index"); 
    }
    return data_[std::get<1>(size_) * index_row + index_col];
}

[[nodiscard]] const int& MatrixS::at(const std::ptrdiff_t  index_row, const std::ptrdiff_t index_col) const {
    if (index_row >= std::get<0>(size_) || index_row < 0 || index_col >= std::get<1>(size_) || index_col < 0) { 
        throw std::out_of_range("invalid index"); 
    }
    return data_[std::get<1>(size_) * index_row + index_col];
}
[[nodiscard]] int& MatrixS::at(const std::ptrdiff_t index_row, const std::ptrdiff_t index_col) {
    if (index_row >= std::get<0>(size_) || index_row < 0 || index_col >= std::get<1>(size_) || index_col < 0) { 
        throw std::out_of_range("invalid index"); 
    }
    return data_[std::get<1>(size_) * index_row + index_col];
}
[[nodiscard]] const MatrixS::SizeType& MatrixS::ssize() const noexcept {
    return size_;
}
[[nodiscard]] std::ptrdiff_t MatrixS::nRows() const noexcept {
    return std::get<0>(size_);
}
[[nodiscard]] std::ptrdiff_t MatrixS::nCols() const noexcept {
    return std::get<1>(size_);
}


void MatrixS::resize(const SizeType& size) {
    ptrdiff_t nRows = std::get<0>(size);
    ptrdiff_t nCols = std::get<1>(size);
    if (nRows <= 0 || nCols <= 0) { 
        throw std::invalid_argument("invalid size"); 
    }
    int* old = data_;
    data_ = new int[nRows * nCols];
    for (int i = 0; i < nRows * nCols; i++) { 
        data_[i] = 0; 
    }
    for (int i = 0; i < std::get<0>(size_); i++) {
        for (int j = 0; j < std::get<1>(size_); j++) {
            data_[std::get<1>(size_) * i + j] = old[std::get<1>(size_) * i + j];
        }
    }
    std::get<0>(size_) = nRows;
    std::get<1>(size_) = nCols;
    delete[] old;
}

void MatrixS::resize(std::ptrdiff_t nRows, ptrdiff_t nCols) {
    if (nRows <= 0 || nCols <= 0) { 
        throw std::invalid_argument("invalid size"); 
    }
    int* old = data_;
    data_ = new int[nRows * nCols];
    for (int i = 0; i < nRows * nCols; i++) { 
        data_[i] = 0; 
    }
    for (int i = 0; i < std::get<0>(size_); i++) {
        for (int j = 0; j < std::get<1>(size_); j++) {
            data_[std::get<1>(size_) * i + j] = old[std::get<1>(size_) * i + j];
        }
    }
    std::get<0>(size_) = nRows;
    std::get<1>(size_) = nCols;
    delete[] old;
}

MatrixS::MatrixS(const MatrixS& mat) {
    std::get<0>(size_) = mat.nRows();
    std::get<0>(size_) = mat.nCols();
    data_ = new int32_t[std::get<0>(size_) * std::get<0>(size_)];
    for (std::ptrdiff_t i = 0; i < std::get<0>(size_) * std::get<0>(size_); i++) {
        data_[i] = mat.data_[i];
    }
}
