<<<<<<< HEAD
#include <matrixs/matrixs.hpp>

MatrixS::~MatrixS() {
	delete[] data_;
}

MatrixS::MatrixS(const std::ptrdiff_t row_count, const std::ptrdiff_t col_count) {
	if (col_count < 0 || row_count < 0) {
		throw std::out_of_range("Out of range");
	}
	n_col_ = col_count;
	n_row_ = row_count;

	data_ = new int32_t[n_col_ * n_row_];
	for (std::ptrdiff_t i = 0; i < n_col_ * n_row_; i++) {
		data_[i] = 0;
	}
}

MatrixS::MatrixS(const SizeType& size)
{
	if (std::get<1>(size) < 0 || std::get<0>(size) < 0) {
		throw std::out_of_range("Out of range");
	}
	n_col_ = std::get<1>(size);
	n_row_ = std::get<0>(size);

	data_ = new int32_t[n_col_ * n_row_];
	for (std::ptrdiff_t i = 0; i < n_col_ * n_row_; i++) {
		data_[i] = 0;
	}
}

int32_t& MatrixS::at(const std::ptrdiff_t i_row, const std::ptrdiff_t j_col) {
	if (i_row < 0 || j_col < 0) {
		throw std::out_of_range("Out of range");
	}
	if (i_row >= n_row_ || j_col >= n_col_) {
		throw std::out_of_range("Out of range");
	}
	return data_[i_row * n_col_ + j_col];
}

int32_t& MatrixS::at(const SizeType& elem) {
	if (std::get<0>(elem) < 0 || std::get<1>(elem) < 0) {
		throw std::out_of_range("Out of range");
	}
	if (std::get<0>(elem) >= n_row_ || std::get<1>(elem) >= n_col_) {
		throw std::out_of_range("Out of range");
	}
	return data_[std::get<0>(elem) * n_col_ + std::get<1>(elem)];
};

const int32_t& MatrixS::at(const std::ptrdiff_t i_row, const std::ptrdiff_t j_col) const {
	if (i_row < 0 || j_col < 0) {
		throw std::out_of_range("Out of range");
	}
	if (i_row >= n_row_ || j_col >= n_col_) {
		throw std::out_of_range("Out of range");
	}
	return data_[i_row * n_col_ + j_col];
}

const int32_t& MatrixS::at(const SizeType& elem) const {
	if (std::get<0>(elem) < 0 || std::get<1>(elem) < 0) {
		throw std::out_of_range("Out of range");
	}
	if (std::get<0>(elem) >= n_row_ || std::get<1>(elem) >= n_col_) {
		throw std::out_of_range("Out of range");
	}
	return data_[std::get<0>(elem) * n_col_ + std::get<1>(elem)];
}

void MatrixS::resize(const std::ptrdiff_t new_i, const std::ptrdiff_t new_j) {
	if (new_i <= 0 || new_j <= 0) {
		throw std::out_of_range("Out of range");
	}
	else {
		int32_t* new_data = new int32_t[new_i * new_j];
		for (std::ptrdiff_t i = 0; i < new_i * new_j; i++) {
			new_data[i] = 0;
		}
		for (std::ptrdiff_t i = 0; i < new_i && i < n_row_; ++i) {
			for (std::ptrdiff_t j = 0; j < new_j && j < n_col_; ++j) {
				new_data[i * new_j + j] = this->at(i, j);
			}
		}
		n_row_ = new_i;
		n_col_ = new_j;

		delete[] data_;
		data_ = new_data;
		new_data = nullptr;
	}
}

void MatrixS::resize(const SizeType& new_size) {
	this->resize(std::get<0>(new_size), std::get<1>(new_size));
}

MatrixS::MatrixS(const MatrixS& mat) {
	n_row_ = mat.n_row_;
	n_col_ = mat.n_col_;
	data_ = new int32_t[n_col_ * n_row_];
	for (std::ptrdiff_t i = 0; i < n_col_ * n_row_; i++) {
		data_[i] = mat.data_[i];
	}
}

MatrixS& MatrixS::operator=(const MatrixS& rhs) {
	if (&rhs != this) {
		delete[] data_;
		n_row_ = rhs.n_row_;
		n_col_ = rhs.n_col_;
		data_ = new int32_t[n_col_ * n_row_];
		for (std::ptrdiff_t i = 0; i < n_col_ * n_row_; ++i) {
			data_[i] = rhs.data_[i];
		}
	}
	return *this;
}

std::ptrdiff_t MatrixS::nRows() const noexcept {
	return n_row_;
}

std::ptrdiff_t MatrixS::nCols() const noexcept {
	return n_col_;
}

const MatrixS::SizeType& MatrixS::ssize() const noexcept {
	return SizeType{ n_row_,n_col_ };
};
||||||| empty tree
=======
#include <matrixs/matrixs.hpp>

MatrixS::~MatrixS() {
	delete[] data_;
}

MatrixS::MatrixS(const std::ptrdiff_t row_count, const std::ptrdiff_t col_count) {
	if (col_count < 0 || row_count < 0) {
		throw std::out_of_range("Out of range");
	}
	n_col_ = col_count;
	n_row_ = row_count;

	data_ = new int32_t[n_col_ * n_row_];
	for (std::ptrdiff_t i = 0; i < n_col_ * n_row_; i++) {
		data_[i] = 0;
	}
}

MatrixS::MatrixS(const SizeType& size)
{
	if (std::get<1>(size) < 0 || std::get<0>(size) < 0) {
		throw std::out_of_range("Out of range");
	}
	n_col_ = std::get<1>(size);
	n_row_ = std::get<0>(size);

	data_ = new int32_t[n_col_ * n_row_];
	for (std::ptrdiff_t i = 0; i < n_col_ * n_row_; i++) {
		data_[i] = 0;
	}
}

int32_t& MatrixS::at(const std::ptrdiff_t i_row, const std::ptrdiff_t j_col) {
	if (i_row < 0 || j_col < 0) {
		throw std::out_of_range("Out of range");
	}
	if (i_row >= n_row_ || j_col >= n_col_) {
		throw std::out_of_range("Out of range");
	}
	return data_[i_row * n_col_ + j_col];
}

int32_t& MatrixS::at(const SizeType& elem) {
	if (std::get<0>(elem) < 0 || std::get<1>(elem) < 0) {
		throw std::out_of_range("Out of range");
	}
	if (std::get<0>(elem) >= n_row_ || std::get<1>(elem) >= n_col_) {
		throw std::out_of_range("Out of range");
	}
	return data_[std::get<0>(elem) * n_col_ + std::get<1>(elem)];
};

const int32_t& MatrixS::at(const std::ptrdiff_t i_row, const std::ptrdiff_t j_col) const {
	if (i_row < 0 || j_col < 0) {
		throw std::out_of_range("Out of range");
	}
	if (i_row >= n_row_ || j_col >= n_col_) {
		throw std::out_of_range("Out of range");
	}
	return data_[i_row * n_col_ + j_col];
}

const int32_t& MatrixS::at(const SizeType& elem) const {
	if (std::get<0>(elem) < 0 || std::get<1>(elem) < 0) {
		throw std::out_of_range("Out of range");
	}
	if (std::get<0>(elem) >= n_row_ || std::get<1>(elem) >= n_col_) {
		throw std::out_of_range("Out of range");
	}
	return data_[std::get<0>(elem) * n_col_ + std::get<1>(elem)];
}

void MatrixS::resize(const std::ptrdiff_t new_i, const std::ptrdiff_t new_j) {
	if (new_i <= 0 || new_j <= 0) {
		throw std::out_of_range("Out of range");
	}
	else {
		int32_t* new_data = new int32_t[new_i * new_j];
		for (std::ptrdiff_t i = 0; i < new_i * new_j; i++) {
			new_data[i] = 0;
		}
		for (std::ptrdiff_t i = 0; i < new_i && i < n_row_; ++i) {
			for (std::ptrdiff_t j = 0; j < new_j && j < n_col_; ++j) {
				new_data[i * new_j + j] = this->at(i, j);
			}
		}
		n_row_ = new_i;
		n_col_ = new_j;

		delete[] data_;
		data_ = new_data;
		new_data = nullptr;
	}
}

void MatrixS::resize(const SizeType& new_size) {
	this->resize(std::get<0>(new_size), std::get<1>(new_size));
}

MatrixS::MatrixS(const MatrixS& mat) {
	n_row_ = mat.n_row_;
	n_col_ = mat.n_col_;
	data_ = new int32_t[n_col_ * n_row_];
	for (std::ptrdiff_t i = 0; i < n_col_ * n_row_; i++) {
		data_[i] = mat.data_[i];
	}
}

MatrixS& MatrixS::operator=(const MatrixS& rhs) {
	if (&rhs != this) {
		delete[] data_;
		n_row_ = rhs.n_row_;
		n_col_ = rhs.n_col_;
		data_ = new int32_t[n_col_ * n_row_];
		for (std::ptrdiff_t i = 0; i < n_col_ * n_row_; ++i) {
			data_[i] = rhs.data_[i];
		}
	}
	return *this;
}

std::ptrdiff_t MatrixS::nRows() const noexcept {
	return n_row_;
}

std::ptrdiff_t MatrixS::nCols() const noexcept {
	return n_col_;
}

const MatrixS::SizeType& MatrixS::ssize() const noexcept {
	return SizeType{ n_row_,n_col_ };
};
>>>>>>> d41395efa836f5c7d767c2452853c96d33f87cda
