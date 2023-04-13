#include <sstream>

#pragma once
#ifndef RATIONAL_RATIONAL_HPP_20230218
#define RATIONAL_RATIONAL_HPP_20230218

const std::exception division_by_zero("Error: Division by zero");

class Rational {
public:
    Rational() = default;
    Rational(const Rational&) = default;
    Rational(int32_t num, int32_t denum);
    explicit Rational(int32_t num) { num_ = num; denum_ = 1; };
    ~Rational() = default;

    Rational& operator=(const Rational& rhs);
    Rational& operator=(const int32_t& rhs);
    Rational& operator+=(const Rational& rhs);
    Rational& operator+=(const int32_t& rhs) { return operator+=(Rational(rhs, 1)); }
    Rational& operator-=(const Rational& rhs);
    Rational& operator-=(const int32_t& rhs) { return operator-=(Rational(rhs, 1)); }
    Rational& operator*=(const Rational& rhs);
    Rational& operator*=(const int32_t& rhs) { return operator*=(Rational(rhs, 1)); }
    Rational& operator/=(const Rational& rhs);
    Rational& operator/=(const int32_t& rhs) { return operator/=(Rational(rhs, 1)); }
    Rational& operator++(int);
    Rational& operator--(int);
    Rational& operator++();
    Rational& operator--();

    bool operator==(const Rational& rhs) const {
        return (num_ == rhs.num_)
            && (denum_ == rhs.denum_);
    }
    bool operator==(const int32_t& rhs) const {
        return (num_ == rhs)
            && (denum_ == 1);
    }
    bool operator!=(const Rational& rhs) const { return !operator==(rhs); }
    bool operator!=(const int32_t& rhs) const { return !operator==(rhs); }
    bool operator>(const Rational& rhs) const {
        return
            num_ * rhs.denum_ - rhs.num_ * denum_ > 0;
    };
    bool operator>(const int32_t& rhs) const {
        return
            num_ - rhs * denum_ > 0;
    };
    bool operator<(const Rational& rhs) const {
        return
            num_ * rhs.denum_ - rhs.num_ * denum_ < 0;
    };
    bool operator<(const int32_t& rhs) const {
        return
            num_ - rhs * denum_ < 0;
    };
    bool operator<=(const Rational& rhs) const { return !operator>(rhs); }
    bool operator<=(const int32_t& rhs) const { return !operator>(rhs); }
    bool operator>=(const Rational& rhs) const { return !operator<(rhs); }
    bool operator>=(const int32_t& rhs) const { return !operator<(rhs); }

    int Nod();
    Rational& ReduceRational();

    std::ostream& WriteTo(std::ostream& ostrm) const;
    std::istream& ReadFrom(std::istream& istrm);
private:
    int32_t num_{ 0 };
    int32_t denum_{ 1 };
    static const char separator{ '/' };
};

Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator+(const Rational& lhs, const int32_t& rhs);
Rational operator+(const int32_t& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const int32_t& rhs);
Rational operator-(const int32_t& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const int32_t& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator*(const int32_t& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const int32_t& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);
Rational operator/(const int32_t& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs);

inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs)
{
    return rhs.WriteTo(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, Rational& rhs)
{
    return rhs.ReadFrom(istrm);
}

#endif
