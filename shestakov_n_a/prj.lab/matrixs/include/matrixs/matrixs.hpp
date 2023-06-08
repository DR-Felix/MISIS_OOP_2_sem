#pragma once
#ifndef MATRIXS_MATRIXS_HPP_20230317
#define MATRIXS_MATRIXS_HPP_20230317

#include <sstream>
#include <vector>

class MatrixS {
public:
    using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;
public:
    explicit MatrixS(const SizeType& size = { 0, 0 });
    MatrixS(const std::ptrdiff_t row_count, const std::ptrdiff_t col_count);
    ~MatrixS();
    MatrixS& operator=(const MatrixS& rhs);
    MatrixS(const MatrixS& mat);

    std::ptrdiff_t nRows() const noexcept;
    std::ptrdiff_t nCols() const noexcept;
    const SizeType& ssize() const noexcept;
    int32_t& at(const SizeType& elem);
    const int32_t& at(const SizeType& elem) const;
    int32_t& at(const std::ptrdiff_t i_row, const std::ptrdiff_t j_col);
    const int32_t& at(const std::ptrdiff_t i_row, const std::ptrdiff_t j_col) const;

    void resize(const SizeType& new_size);
    void resize(const std::ptrdiff_t new_i, const std::ptrdiff_t new_j);
private:
    std::ptrdiff_t n_row_{ 0 };
    std::ptrdiff_t n_col_{ 0 };
    int32_t* data_{ nullptr };
};

#endif
