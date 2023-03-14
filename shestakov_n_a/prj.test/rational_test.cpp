#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <rational/rational.hpp>

TEST_CASE("testing the rational functions") {

    CHECK(Rational(1, 2) + Rational(3, 4) == Rational(5, 4));
    CHECK(Rational(3, 4) - Rational(1, 2) == Rational(1, 4));
    CHECK(Rational(3, 4) * Rational(1, 2) == Rational(3, 8));
    CHECK(Rational(3, 4) / Rational(1, 2) == Rational(3, 2));

    CHECK_THROWS(Rational(3, 4) / Rational(0, 2) == Rational(1, 4));
   
    CHECK((Rational(1, 2) += Rational(3, 4)) == Rational(5, 4));

    CHECK(Rational(3, 4) > Rational(2, 3));
    CHECK(Rational(10, 8) < Rational(20, 10));
    CHECK(Rational(2, 5) >= Rational(2, 5));
    CHECK(Rational(3, 7) <= Rational(3, 7));

    CHECK(Rational(7, 9) == Rational(7, 9));
    CHECK(Rational(25, 60) == Rational(5, 12));
    CHECK(Rational(2, -4) == Rational(-2, 4));

}
