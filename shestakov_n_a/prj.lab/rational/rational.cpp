#include <rational/rational.hpp>

Rational& Rational::operator=(const Rational& rhs)
{
    num_ = rhs.num_;
    denum_ = rhs.denum_;
    return *this;
}

Rational& Rational::operator=(const int32_t& rhs)
{
    num_ = rhs;
    denum_ = 1;
    return *this;
}

Rational operator+(const Rational& lhs, const Rational& rhs)
{
    Rational sum(lhs);
    sum += rhs;
    sum.ReduceRational();
    return sum;
}

Rational operator+(const Rational& lhs, const int32_t& rhs)
{
    Rational sum(lhs);
    sum += rhs;
    return sum;
}

Rational operator+(const int32_t& lhs, const Rational& rhs)
{
    Rational sum(rhs);
    sum += lhs;
    return sum;
}

Rational operator-(const Rational& lhs, const Rational& rhs)
{
    Rational sum(lhs);
    sum -= rhs;
    sum.ReduceRational();
    return sum;
}

Rational operator-(const Rational& lhs, const int32_t& rhs)
{
    Rational sum(lhs);
    sum -= rhs;
    return sum;
}

Rational operator-(const int32_t& lhs, const Rational& rhs)
{
    Rational sum(rhs);
    sum -= lhs;
    return -sum;
}

Rational operator*(const Rational& lhs, const int32_t& rhs)
{
    Rational mul(lhs);
    mul *= rhs;
    mul.ReduceRational();
    return mul;
}

Rational operator*(const Rational& lhs, const Rational& rhs)
{
    Rational mul(lhs);
    mul *= rhs;
    mul.ReduceRational();
    return mul;
}

Rational operator*(const int32_t& lhs, const Rational& rhs)
{
    Rational mul(rhs);
    mul *= lhs;
    mul.ReduceRational();
    return mul;
}

Rational operator/(const Rational& lhs, const int32_t& rhs)
{
    Rational div(lhs);
    div /= rhs;
    div.ReduceRational();
    return div;
}

Rational operator/(const Rational& lhs, const Rational& rhs)
{
    Rational div(lhs);
    div /= rhs;
    div.ReduceRational();
    return div;
}

Rational operator/(const int32_t& lhs, const Rational& rhs)
{
    Rational div(lhs, 1);
    div /= rhs;
    div.ReduceRational();
    return div;
}

Rational operator-(const Rational& lhs)
{
    return lhs * (-1);
}

Rational& Rational::operator+=(const Rational& rhs)
{
    num_ = num_ * rhs.denum_ + rhs.num_ * denum_;
    denum_ = rhs.denum_ * denum_;
    ReduceRational();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs)
{
    num_ = num_ * rhs.denum_ - rhs.num_ * denum_;
    denum_ = rhs.denum_ * denum_;
    ReduceRational();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs)
{
    num_ = num_ * rhs.num_;
    denum_ = denum_ * rhs.denum_;
    ReduceRational();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs)
{
    if (rhs.num_ != 0) {
        if (rhs.num_ < 0)
            *this *= Rational(-rhs.denum_, -rhs.num_);
        else
            *this *= Rational(rhs.denum_, rhs.num_);
        ReduceRational();
        return *this;
    }
    else {
        throw division_by_zero;
    }
}

int Rational::Nod()
{
    int32_t num = std::abs(num_);
    int32_t denum = denum_;
    while (num > 0 && denum > 0) {
        if (num > denum)
            num %= denum;
        else
            denum %= num;
    };
    return num + denum;
}


Rational& Rational::operator++() {
    num_ = num_ + denum_;
    return *this;
}

Rational& Rational::operator--() {
    num_ = num_ - denum_;
    return *this;
}

Rational& Rational::operator++(int) {
    Rational result = *this;
    ++(*this);
    return result;
}

Rational& Rational::operator--(int) {
    Rational result = *this;
    --(*this);
    return result;
}

Rational& Rational::ReduceRational() {
    int32_t reduce_coef = Nod();
    if (reduce_coef != 1) {
        num_ /= reduce_coef;
        denum_ /= reduce_coef;
    };
    return *this;
}

Rational::Rational(int32_t num, int32_t denum) {
    if (denum == 0)
        throw division_by_zero;
    if (denum < 0) {
        num_ = num * (-1);
        denum_ = denum * (-1);
    }
    if (denum > 0) {
        num_ = num;
        denum_ = denum;
    }
    ReduceRational();
}

std::ostream& Rational::WriteTo(std::ostream& ostrm) const
{
    ostrm << num_ << separator << denum_;
    return ostrm;
}

std::istream& Rational::ReadFrom(std::istream& istrm) {
    char comma{ 0 };
    int32_t numerator{ 0 };
    int32_t denumerator{ 0 };
    istrm >> numerator;
    if (isspace(istrm.peek())) {
        istrm.setstate(std::ios_base::failbit);
        istrm.setstate(std::ios_base::eofbit);
    }
    istrm >> comma;
    if (comma != Rational::separator || isspace(istrm.peek())) {
        istrm.setstate(std::ios_base::failbit);
        istrm.setstate(std::ios_base::eofbit);
    }
    istrm >> denumerator;
    if (denumerator <= 0) {
        istrm.setstate(std::ios_base::failbit);
        istrm.setstate(std::ios_base::eofbit);
    }
    if (istrm.fail() == false) {
        num_ = numerator;
        denum_ = denumerator;
        ReduceRational();
    }
    return istrm;
}
