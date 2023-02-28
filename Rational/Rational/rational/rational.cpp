#include <iostream>
#include <sstream>
#include <exception>
#include <string>

#include "rational.h"

Rational::Rational(const int32_t num_, const int32_t denum_) {
    num = num_;
    denum = denum_;
    if (denum == 0) {
        throw std::exception();
    }
    else if (denum < 0) {
        denum *= -1;
        num *= -1;
    }
}


std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) { //const, так как значение объекта класса Rational не меняем
    return rhs.writeTo(ostrm);
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const {
    ostrm << num << separator << denum;
    return ostrm;
}

std::istream& operator>>(std::istream& istrm, Rational& rhs) //inline - повышение скорости у часто используемых функций
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
            *this = Rational(num_, denum_); // альтернативная запись этих двух строк *this = Rational(num_, denum_);
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


Rational& Rational::NOD(Rational& const rhs) {
    int32_t chsl = num;
    int32_t znam = denum;
    if (chsl > znam) {
        int r = -1;
        int a = chsl;
        int b = znam;
        int c = 0;
        while (r != 0) {
            r = a % b;
            if (r != 0) {
                a = b;
                b = r;
            }
        }
        chsl /= b;
        znam /= b;
        num = chsl;
        denum = znam;
    }
    else if (chsl < znam) {
        int r = -1;
        int a = znam;
        int b = chsl;
        int c = 0;
        while (r != 0) {
            r = a % b;
            if (r != 0) {
                a = b;
                b = r;
            }
        }
        chsl /= b;
        znam /= b;
        num = chsl;
        denum = znam;
    }
    else {
        int32_t del = chsl;
        chsl /= del;
        znam /= del;
        num = chsl;
        denum = znam;
    }
    if (denum < 0) {
        denum *= -1;
        num *= -1;
    }
    Rational res(num, denum);
    return res;
}

Rational& Rational::operator+=(const Rational& rhs) {
    num = num * rhs.denum + denum * rhs.num;
    denum = denum * rhs.denum;
    Rational a(num, denum);
    return NOD(a);
}

Rational& Rational::operator-=(const Rational& rhs) {
    num = num * rhs.denum - denum * rhs.num;
    denum = denum * rhs.denum;
    Rational a(num, denum);
    return NOD(a);
}

Rational& Rational::operator*=(const Rational& rhs) {
    num *= rhs.num;
    denum *= rhs.denum;
    Rational a(num, denum);
    return NOD(a);
}

Rational& Rational::operator/=(const Rational& rhs) {
    num *= rhs.denum;
    denum *= rhs.num;
    Rational a(num, denum);
    return NOD(a);
}


Rational operator-(const Rational& rhs) {
    return (rhs * Rational(-1, 1));
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational sum(lhs);
    sum += rhs;
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