#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <arrayt/arrayt.hpp>

using ArrayD = ArrayT <int>;

TEST_CASE("Test number 1") {
	ArrayD arr;
	CHECK_THROWS(arr[0]);
	CHECK(arr.ssize() == 0);
	arr.resize(5);
	std::cout << arr[0];
	for (int i = 1; i < arr.ssize(); i++) {
		CHECK(arr[i] == 0);
	}
	CHECK_THROWS(arr[7]);
	arr[1] = 56;
	CHECK(arr[1] == 56);
	ArrayD arr1(arr);
	for (int i = 0; i < arr1.ssize(); i++) {
		CHECK(arr1[i] == arr[i]);
	}
	arr1[1] = 78;
	CHECK(arr1[1] != arr[1]);
	arr1 = arr;
	for (int i = 0; i < arr1.ssize(); i++) {
		CHECK(arr1[i] == arr[i]);
	}
	arr.remove(3);
	CHECK(arr[0] == arr1[0]);
	CHECK(arr[1] == arr1[1]);
	CHECK(arr[2] == arr1[3]);
	CHECK(arr[3] == arr1[4]);
	arr.insert(5, 3);
	CHECK(arr[0] == arr1[0]);
	CHECK(arr[1] == arr1[1]);
	CHECK(arr[2] == arr1[3]);
	CHECK(arr[3] == 5);
	CHECK(arr[4] == arr1[4]);
}