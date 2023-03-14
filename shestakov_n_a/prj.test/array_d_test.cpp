#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "array_d/array_d.hpp"
#include "doctest/doctest.h"

TEST_CASE("testing the DynamicArrays functions") {
    CHECK_NOTHROW(ArrayD{ 1, 2 });
    CHECK_NOTHROW(ArrayD{ 1, 2 }.ssize());
    CHECK_NOTHROW(ArrayD{ 1, 2 });
    ArrayD a{ 1,2 };
    ArrayD b;
    a.remove(1);
    a.insert(1, 3);
    b = a;
    b[1] = 0;
    std::cout << a << b;
}