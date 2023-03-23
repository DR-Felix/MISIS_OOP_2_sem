#include <iosfwd>
#include <exception>
#include <stdexcept>
#include "cstdint"

int32_t GCD(int32_t a, int32_t b);

class Rational {

public:
    Rational() = default; //конструктор со значениями по умолчанию
    Rational(const Rational&) = default; //конструктор копирования со значением по умолчанию
    explicit Rational(const int32_t num_) noexcept;
    Rational(const int32_t num_, const int32_t denum_); //еще один конструктор по умолчанию с двумя входными значениями
    ~Rational() = default; //деструктор для чистки конструктора после завершения программы во избежание утечек памяти


    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational& rhs) const;

    Rational operator+=(const Rational& rhs);
    Rational operator-=(const Rational& rhs);
    Rational operator*=(const Rational& rhs);
    Rational operator/=(const Rational& rhs);

    Rational operator+=(const int32_t& rhs);
    Rational operator-=(const int32_t& rhs);
    Rational operator/=(const int32_t& rhs);
    Rational operator*=(const int32_t& rhs);

    std::istream& readFrom(std::istream& istrm);
    std::ostream& writeTo(std::ostream& ostrm) const noexcept; //const, поскольку нам нужен только вывод

    bool operator>(const Rational& rhs) const;

private: //в данном случае ставим параметры по умолчанию, которые пользователь изменить не сможет
    int32_t num{ 0 }; //числитель
    int32_t denum{ 1 }; //знаменатель
    static const char separator{ '/' }; //формат - черта дроби

};

Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);

Rational operator+(const Rational& lhs, const int32_t& rhs);
Rational operator-(const Rational& lhs, const int32_t& rhs);
Rational operator*(const Rational& lhs, const int32_t& rhs);
Rational operator/(const Rational& lhs, const int32_t& rhs);

Rational& operator++(Rational& lhs);
Rational& operator--(Rational& lhs);
Rational operator++(Rational& lhs, int);
Rational operator--(Rational& lhs, int);

Rational operator-(const Rational& rhs);

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs);
std::istream& operator>>(std::istream& istrm, Rational& rhs);

bool operator<(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);

bool operator==(const Rational& lhs, const int32_t& rhs);
bool operator!=(const Rational& lhs, const int32_t& rhs);
bool operator>(const Rational& lhs, const int32_t& rhs);
bool operator<(const Rational& lhs, const int32_t& rhs);
bool operator<=(const Rational& lhs, const int32_t& rhs);
bool operator>=(const Rational& lhs, const int32_t& rhs);
