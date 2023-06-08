#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <rational/rational.hpp>

Rational InputRational(const std::string& str, Rational& rat)
{
	std::istringstream istrm(str);
	istrm >> rat;
	std::cout << istrm.fail();
	return rat;
}

TEST_CASE("Testing ctor") {
	Rational x(1, 3);
	InputRational("1/0", x);
	CHECK(Rational(1, 3) == x);


	CHECK(Rational() == Rational(0, 1));
	CHECK(Rational(10, 6) == Rational(5, 3));
	CHECK(Rational(-10, 6) == Rational(-5, 3));
	CHECK(Rational(-5) == Rational(-5, 1));
	CHECK(Rational(10, -6) == Rational(-5, 3));
	CHECK_THROWS(Rational(1, 0));
}

TEST_CASE("Testing Math Operator +") {
	CHECK(Rational(2, 3) + Rational(1, 2) == Rational(7, 6));
	CHECK(Rational(4, 3) + Rational(1, 2) == Rational(11, 6));
	CHECK(Rational(5, 2) + 2 == Rational(9, 2));
	CHECK(2 + Rational(5, 2) == Rational(9, 2));
}

TEST_CASE("Testing Math Operator -") {
	CHECK(Rational(2, 3) - Rational(1, 2) == Rational(1, 6));
	CHECK(Rational(4, 3) - Rational(1, 2) == Rational(5, 6));
	CHECK(Rational(5, 2) - 2 == Rational(1, 2));
	CHECK(2 - Rational(5, 2) == Rational(-1, 2));
}

TEST_CASE("Testing Math Operator *") {
	CHECK(Rational(2, 3) * Rational(1, 2) == Rational(1, 3));
	CHECK(Rational(4, 3) * Rational(1, 2) == Rational(2, 3));
	CHECK(Rational(5, 2) * 2 == Rational(5, 1));
	CHECK(-2 * Rational(5, 2) == Rational(-5, 1));
}

TEST_CASE("Testing Math Operator /") {
	CHECK(Rational(2, 3) / Rational(1, 2) == Rational(4, 3));
	CHECK(Rational(5, 2) / Rational(1, 2) == Rational(5, 1));
	CHECK(Rational(5, 2) / 2 == Rational(5, 4));
	CHECK(-2 / Rational(5, 2) == Rational(-4, 5));
}

TEST_CASE("Testing Math Operator (+,-,*,/)= and (++,--)") {
	Rational x = Rational(2, 3);
	x += 1;
	CHECK(x == Rational(5, 3));
	x -= 1;
	CHECK(x == Rational(2, 3));
	x /= 2;
	CHECK(x == Rational(1, 3));
	x *= 4;
	CHECK(x == Rational(4, 3));
	x++;
	CHECK(x == Rational(7, 3));
	x--;
	CHECK(x == Rational(4, 3));
	x += Rational(4, 3);
	CHECK(x == Rational(8, 3));
	x -= Rational(1, 2);
	CHECK(x == Rational(13, 6));
	x *= Rational(1, 2);
	CHECK(x == Rational(13, 12));
	x /= Rational(13, 2);
	CHECK(x == Rational(1, 6));
}

TEST_CASE("Testing Unary Operator -") {
	CHECK(-Rational(2, 3) == Rational(-2, 3));
}

TEST_CASE("Testing Logic Operator >") {
	CHECK(Rational(2, 3) > Rational(1, 2));
	CHECK_FALSE(Rational(1, 2) > Rational(2, 3));
	CHECK(Rational(2, 3) * 2 > 1);
}

TEST_CASE("Testing Logic Operator <") {
	CHECK_FALSE(Rational(2, 3) < Rational(1, 2));
	CHECK(Rational(1, 2) < Rational(2, 3));
	CHECK_FALSE(Rational(2, 3) * 2 < 1);
}

TEST_CASE("Testing Logic Operator >=") {
	CHECK(Rational(2, 3) >= Rational(1, 2));
	CHECK_FALSE(Rational(1, 2) >= Rational(2, 3));
	CHECK(Rational(2, 3) >= Rational(2, 3));
	CHECK(Rational(3, 2) >= 1);
}

TEST_CASE("Testing Logic Operator <=") {
	CHECK_FALSE(Rational(2, 3) <= Rational(1, 2));
	CHECK(Rational(1, 2) <= Rational(2, 3));
	CHECK(Rational(2, 3) <= Rational(2, 3));
	CHECK_FALSE(Rational(3, 2) <= 1);
}

TEST_CASE("Testing Logic Operator !=") {
	CHECK(Rational(2, 3) != Rational(1, 2));
	CHECK_FALSE(Rational(1, 2) != Rational(1, 2));
	CHECK(Rational(2, 3) != 2);
	CHECK_FALSE(Rational(2, 2) != 1);
}


TEST_CASE("Testing Logic Operator ==") {
	CHECK_FALSE(Rational(2, 3) == Rational(1, 2));
	CHECK(Rational(1, 2) == Rational(1, 2));
	CHECK_FALSE(Rational(2, 3) == 2);
	CHECK(Rational(2, 2) == 1);
}

TEST_CASE("Dividing by 0") {
	CHECK_THROWS(Rational(1, 0));
	CHECK_THROWS(Rational(1, 2) / 0);
	CHECK_THROWS(Rational(1, 2) / Rational(0, 5));
	Rational x = Rational(2, 3);
	CHECK_THROWS(x /= 0);
	CHECK_THROWS(x /= Rational(0, 5));
}

TEST_CASE("Checking input system") {
	Rational x;
	InputRational("1/4 ", x);
	CHECK(Rational(1, 4) == x);
	InputRational(" 1/2 ", x);
	CHECK(Rational(1, 2) == x);
	InputRational("1/7k", x);
	CHECK(Rational(1, 7) == x);
	InputRational("6/8", x);
	CHECK(Rational(3, 4) == x);
	std::string str_for_3 = "3/4 5/6 7/8";
	std::istringstream istrm_for_3(str_for_3);
	Rational y;
	Rational z;
	istrm_for_3 >> x >> y >> z;
	CHECK(Rational(3, 4) == x);
	CHECK(Rational(5, 6) == y);
	CHECK(Rational(7, 8) == z);

	x = Rational(1, 3);
	InputRational("1 /4", x);
	CHECK(Rational(1, 3) == x);
	InputRational("k/4", x);
	CHECK(Rational(1, 3) == x);
	InputRational("k/4", x);
	CHECK(Rational(1, 3) == x);
	InputRational("4/k", x);
	CHECK(Rational(1, 3) == x);
	InputRational("4-3", x);
	CHECK(Rational(1, 3) == x);
	InputRational("k3/4", x);
	CHECK(Rational(1, 3) == x);
	InputRational("3/ 4", x);
	CHECK(Rational(1, 3) == x);
	InputRational("3", x);
	CHECK(Rational(1, 3) == x);
}
