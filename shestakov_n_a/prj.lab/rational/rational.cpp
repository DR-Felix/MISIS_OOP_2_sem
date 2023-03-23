#include <iostream>
#include <sstream>
#include <exception>
#include <string>

#include <rational/rational.hpp>

Rational::Rational(const int32_t num_, const int32_t denum_) {
    if (denum == 0) {
        throw std::exception("DIVISION BY ZERO");
    }
    int32_t d = GCD(num_, denum_);
    num = num_/d;
    denum = denum_/d;
    if (denum < 0) {
        denum *= -1;
        num *= -1;
    }
}

Rational::Rational(const int32_t num_) noexcept {
    denum = 1;
    num = num_;
}

int32_t GCD(int32_t a, int32_t b) {
    a = abs(a);
    b = abs(b);
    while (a && b) {
        if (a > b) {
            a %= b;
        }
        else {
            b %= a;
        }
    }
    return a + b;
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) {
    return rhs.writeTo(ostrm);
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const noexcept {
    ostrm << num << separator << denum;
    return ostrm;
}

std::istream& operator>>(std::istream& istrm, Rational& rhs)
{                                                                   //передаем два значения: слева - объект типа потока istream, справа - наш объект класса
    return rhs.readFrom(istrm); //вызываем функцию readFrom для объекта rhs класса Rational, передав в него параметр istrm типа потока
}                                                                   //везде используем ссылки, ибо нам не нужно копировать объекты, мы работаем с тем, что есть

std::istream& Rational::readFrom(std::istream& istrm) { //создаем временные переменные separator_, num_, denum_
    char separator_(0);
    int32_t num_(0);
    int32_t denum_(0);
    istrm >> num_ >> separator_ >> denum_; //istrm - ссылка на поток чтения, поскольку потоки не копируются
    if (istrm.good() || istrm.eof() && !istrm.fail()) {
        if (Rational::separator == separator_) {
            istrm.clear();
            *this = Rational(num_, denum_);
            if (denum < 0) {
                denum *= -1;
                num *= -1;
            }
        }
        else {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
}


Rational Rational::operator+=(const Rational& rhs) {
    num = num * rhs.denum + denum * rhs.num;
    denum = denum * rhs.denum;
    int32_t d = GCD(num, denum);
    num = num / d;
    denum = denum / d;
    return Rational(num, denum);
}

Rational Rational::operator-=(const Rational& rhs) {
    num = num * rhs.denum - denum * rhs.num;
    denum = denum * rhs.denum;
    int32_t d = GCD(num, denum);
    num = num / d;
    denum = denum / d;
    return Rational(num, denum);
}

Rational Rational::operator*=(const Rational& rhs) {
    num *= rhs.num;
    denum *= rhs.denum;
    int32_t d = GCD(num, denum);
    num = num / d;
    denum = denum / d;
    return Rational(num, denum);
}

Rational Rational::operator/=(const Rational& rhs) {
    num *= rhs.denum;
    denum *= rhs.num;
    int32_t d = GCD(num, denum);
    num = num / d;
    denum = denum / d;
    if (denum == 0) {
        throw std::exception("DIVISION BY ZERO");
    }
    else {
        return Rational(num, denum);
    }
}


Rational Rational::operator+=(const int32_t& rhs) {
    num = num + rhs * denum;
    denum = denum;
    int32_t d = GCD(num, denum);
    num = num / d;
    denum = denum / d;
    return Rational(num, denum);
}

Rational Rational::operator-=(const int32_t& rhs) {
    num = num - rhs * denum;
    denum = denum;
    int32_t d = GCD(num, denum);
    num = num / d;
    denum = denum / d;
    return Rational(num, denum);
}

Rational Rational::operator*=(const int32_t& rhs) {
    num = num * rhs;
    denum = denum;
    int32_t d = GCD(num, denum);
    num = num / d;
    denum = denum / d;
    return Rational(num, denum);
}

Rational Rational::operator/=(const int32_t& rhs) {
    num = num;
    denum *= rhs;
    int32_t d = GCD(num, denum);
    num = num / d;
    denum = denum / d;
    return Rational(num, denum);
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational sum(lhs);
    sum += rhs;;
    return sum;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational sum(lhs);
    sum -= rhs;
    return sum;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational umn(lhs);
    umn *= rhs;
    return umn;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational del(lhs);
    del /= rhs;
    return del;
}

Rational operator+(const Rational& lhs, const int32_t& rhs) {
    Rational sum(lhs);
    sum += rhs;
    return sum;
}

Rational operator-(const Rational& lhs, const int32_t& rhs) {
    Rational sum(lhs);
    sum -= rhs;
    return sum;
}

Rational operator*(const Rational& lhs, const int32_t& rhs) {
    Rational umn(lhs);
    umn *= rhs;
    return umn;
}

Rational operator/(const Rational& lhs, const int32_t& rhs) {
    Rational del(lhs);
    del /= rhs;
    return del;
}

Rational& operator++(Rational& lhs) {
    lhs = lhs + 1;
    return lhs;
}

Rational& operator--(Rational& lhs) {
    lhs = lhs - 1;
    return lhs;
}
Rational operator++(Rational& lhs, int) {
    Rational old = lhs;
    lhs += 1;
    return old;
}

Rational operator--(Rational& lhs, int) {
    Rational old = lhs;
    lhs -= 1;
    return old;
}

Rational operator-(const Rational& rhs) {
    return (rhs * Rational(-1, 1));
}

bool Rational::operator==(const Rational& rhs) const { 
    return (num == rhs.num) && (denum == rhs.denum); 
}
bool Rational::operator!=(const Rational& rhs) const { 
    return !operator==(rhs); 
}

bool Rational::operator>(const Rational& rhs) const {
    return ((num * rhs.denum - rhs.num * denum) > 0);
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return rhs.operator>(lhs);
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !lhs.operator>(rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !rhs.operator>(lhs);
}

bool operator==(const Rational& lhs, const int32_t& rhs) {
    return lhs == Rational(rhs);
}

bool operator!=(const Rational& lhs, const int32_t& rhs) {
    return lhs != Rational(rhs);
}
bool operator>(const Rational& lhs, const int32_t& rhs) {
    return lhs > Rational(rhs);
}
bool operator<(const Rational& lhs, const int32_t& rhs) {
    return lhs < Rational(rhs);
}
bool operator<=(const Rational& lhs, const int32_t& rhs) {
    return lhs <= Rational(rhs);
}
bool operator>=(const Rational& lhs, const int32_t& rhs) {
    return lhs >= Rational(rhs);
}
