#include <algorithm>
#include <iostream>

#include <array_d/array_d.hpp>


ArrayD::ArrayD(int s) {             //или ArrayD::ArrayD(int s) : ssize_(s) { data = new double[ssize_]; }
    ssize_ = s;
    data = new double[ssize_];
}

ArrayD::ArrayD(const ArrayD& other) : ssize_(other.ssize_) //копируем уже имеющийся массив
{
    data = new double[ssize_];
    for (int i = 0; i < ssize_; ++i)
        data[i] = other.data[i];
}

ArrayD::ArrayD(std::initializer_list<double> list) : ssize_(list.size()) //создаем новый с помощью инициализирующего списка
{
    data = new double[ssize_];
    int i = 0;
    for (auto& item : list)
        data[i++] = item;
}

ArrayD& ArrayD::operator=(const ArrayD& other) {
    delete[] data;
    ssize_ = other.ssize();
    data = new double[ssize_];
    for (int i = 0; i < ssize_; ++i)
        data[i] = other.data[i];
    return *this;
}

ArrayD::ArrayD(ArrayD&& other) : ssize_(other.ssize_), data(other.data) //Конструктор копирования && означает временную ссылку,
{                                                                      //т. е. как только компилятор выйдет из функции, объект other будет удален
    other.ssize_ = 0;
    other.data = nullptr;
}

double& ArrayD::operator[](int iter) const {
    if (iter <= 0 || iter >= ssize_) { throw std::invalid_argument("invalid index of iterator"); }
    return data[iter];
}

ptrdiff_t ArrayD::ssize() const { return ssize_; } //функция получения размера

void ArrayD::resize(const int& new_size) {
    if (new_size <= 0) { throw std::invalid_argument("invalid size"); }
    double* old = data;
    ssize_ = new_size;
    data = new double[new_size];

    int min_size(1);
    if (size_t(old) < new_size) {
        min_size = size_t(old);
    }
    else {
        min_size = ssize_;
    }
    for (int i = 0; i < min_size; ++i) {
        data[i] = old[i];
    }
    delete[] old; //обязательно следим за памятью и чистим ненужные массивы!
}

void ArrayD::insert(const int& i, const double& elem) {
    if (i <= 0 || i > ssize_) { throw std::invalid_argument("invalid index"); }
    ssize_ += 1;
    double* old = data;
    data = new double[ssize_];
    for (int j = 0; j < i; ++j) {
        data[j] = old[j];
    }
    data[i] = elem;
    for (int j = i + 1; j < ssize_; ++j) {
        data[j] = old[j - 1];
    }
    delete[] old;
}
void ArrayD::remove(const int& i) {
    std::rotate(data + i, data + i + 1, data + ssize_);
    (*this).resize(ssize_ - 1);
}

std::istream& ArrayD::ReadFrom(std::istream& istrm) {
    if (ssize_ > 0) {
        int i = 0;
        double xi = 0;
        while (!istrm.eof() && istrm.good() && i < ssize_) {
            istrm >> xi;
            data[i] = xi;
            i += 1;
        }
    }
    else {
        throw std::exception();
    }
    return istrm;
}

std::ostream& ArrayD::WriteTo(std::ostream& ostrm) {
    if (ssize_ > 0) {
        int i = 0;
        while (ostrm.good() && i < ssize_) {
            ostrm << data[i] << " ";
            i += 1;
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