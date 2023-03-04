#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <rational/rational.hpp>

TEST_CASE("[rational] - Rational ctor") {
  CHECK(Rational() == Rational(0, 1));
  CHECK(Rational(3) == Rational(3, 1));
  CHECK(Rational(-3) == Rational(-3, 1));
  CHECK(Rational(10, 6) == Rational(5, 3));
  CHECK(Rational(-10, 6) == Rational(-5, 3));
  CHECK(Rational(10, -6) == Rational(-5, 3));
  CHECK(Rational(-10, -6) == Rational(5, 3));
  CHECK_THROWS(Rational(1, 0));
}