#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cstdint>

#include <arrayd/arrayd.hpp>


ArrayD::ArrayD(const std::ptrdiff_t size) {
    ssize_ = size;
    if (size < 0) {
        throw std::invalid_argument("Size must be non-negative");
    }
    capacity_ = ssize_ * 2;
    data_ = new double[capacity_];
    for (int i = 0; i < capacity_; i++) {
        data_[i] = NULL;
    }
}

ArrayD::ArrayD(const ArrayD& other) {
    ssize_ = other.ssize_;
    capacity_ = ssize_ * 2;
    data_ = new double[capacity_];
    for (int i = 0; i < ssize_; ++i)
        data_[i] = other.data_[i];
}

ArrayD::ArrayD(ArrayD&& other) noexcept //Конструктор копирования && - означает временную ссылку, как только функция закончится, объект other будет удален
{
    ssize_ = other.ssize_;
    data_ = other.data_;
    capacity_ = other.capacity_;
    other.ssize_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
}

ArrayD& ArrayD::operator=(const ArrayD& other) {
    delete[] data_;
    ssize_ = other.ssize();
    capacity_ = ssize_ * 2;
    data_ = new double[capacity_];
    for (int i = 0; i < ssize_; ++i)
        data_[i] = other.data_[i];
    return *this;
}

double& ArrayD::operator[](const std::ptrdiff_t i) {
    if (i < 0 || i >= ssize_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[i];
}

const double& ArrayD::operator[](const std::ptrdiff_t i) const {
    if (i < 0 || i >= ssize_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[i];
}

ArrayD::~ArrayD() {
    delete[] data_;
}

std::ptrdiff_t ArrayD::ssize() const noexcept { return ssize_; }

void ArrayD::resize(const std::ptrdiff_t new_size) {
    if (new_size <= 0) {
        throw std::invalid_argument("New size must be non-negative");
    }
    if (new_size > capacity_) {
        double* old = data_;
        capacity_ = new_size * 2;
        data_ = new double[capacity_];
        for (int i = 0; i < new_size; i++) {
            data_[i] = old[i];
        }
        delete[] old;
    }
    ssize_ = new_size;
    int a = ssize_;
    for (int i = a; i < new_size; i += 1) {
        data_[i] = NULL;
    }
}

void ArrayD::insert(const std::ptrdiff_t i, const double& value) {
    if (i < 0 || i > ssize_) {
        throw std::out_of_range("invalid index");
    }
    (*this).resize(ssize_ + 1);
    for (int j = ssize_ - 1; j > i; --j) {
        data_[j] = data_[j - 1];
    }
    data_[i] = value;
}

void ArrayD::remove(const std::ptrdiff_t i) {
    if (i < 0 || i >= ssize_) { 
        throw std::out_of_range("invalid index"); 
    }
    std::rotate(data_ + i, data_ + i + 1, data_ + ssize_);
    (*this).resize(ssize_ - 1);
}

std::istream& ArrayD::ReadFrom(std::istream& istrm) {
    if (ssize_ > 0) {
        int i = 0;
        double xi = 0;
        while (!istrm.eof() && istrm.good() && i < ssize_) {
            istrm >> xi;
            data_[i] = xi;
            i++;
        }
    }
    else {
        istrm.setstate(std::ios_base::failbit);
    }
    return istrm;
}

std::ostream& ArrayD::WriteTo(std::ostream& ostrm) {
    if (ssize_ > 0) {
        int i = 0;
        while (ostrm.good() && i < ssize_) {
            ostrm << data_[i] << " ";
            i++;
        }
    }
    return ostrm;
}

std::ostream& operator<<(std::ostream& ostrm, ArrayD& array) {
    return array.WriteTo(ostrm);
}

std::istream& operator>>(std::istream& istrm, ArrayD& array) {
    return array.ReadFrom(istrm);
}