<<<<<<< HEAD
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <arrayd/arrayd.hpp>

TEST_CASE("Test number 1") {
	ArrayD arr;
	CHECK_THROWS(arr[0]);
	CHECK(arr.Ssize() == 0);
	arr.Resize(5);
	for (int i = 0; i < arr.Ssize(); i++) {
		CHECK(arr[i] == 0.0);
	}
	CHECK_THROWS(arr[7]);
	arr[1] = 56.24;
	CHECK(arr[1] == 56.24);
	ArrayD arr1(arr);
	for (int i = 0; i < arr1.Ssize(); i++) {
		CHECK(arr1[i] == arr[i]);
	}
	arr1[1] = 78.25;
	CHECK(arr1[1] != arr[1]);
	arr1 = arr;
	for (int i = 0; i < arr1.Ssize(); i++) {
		CHECK(arr1[i] == arr[i]);
	}
	arr.Remove(3);
	CHECK(arr[0] == arr1[0]);
	CHECK(arr[1] == arr1[1]);
	CHECK(arr[2] == arr1[3]);
	CHECK(arr[3] == arr1[4]);
	arr.Insert(5.5, 3);
	CHECK(arr[0] == arr1[0]);
	CHECK(arr[1] == arr1[1]);
	CHECK(arr[2] == arr1[3]);
	CHECK(arr[3] == 5.5);
	CHECK(arr[4] == arr1[4]);
}
||||||| empty tree
=======
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <arrayd/arrayd.hpp>

TEST_CASE("Test number 1") {
	ArrayD arr;
	CHECK_THROWS(arr[0]);
	CHECK(arr.Ssize() == 0);
	arr.Resize(5);
	for (int i = 0; i < arr.Ssize(); i++) {
		CHECK(arr[i] == 0.0);
	}
	CHECK_THROWS(arr[7]);
	arr[1] = 56.24;
	CHECK(arr[1] == 56.24);
	ArrayD arr1(arr);
	for (int i = 0; i < arr1.Ssize(); i++) {
		CHECK(arr1[i] == arr[i]);
	}
	arr1[1] = 78.25;
	CHECK(arr1[1] != arr[1]);
	arr1 = arr;
	for (int i = 0; i < arr1.Ssize(); i++) {
		CHECK(arr1[i] == arr[i]);
	}
	arr.Remove(3);
	CHECK(arr[0] == arr1[0]);
	CHECK(arr[1] == arr1[1]);
	CHECK(arr[2] == arr1[3]);
	CHECK(arr[3] == arr1[4]);
	arr.Insert(5.5, 3);
	CHECK(arr[0] == arr1[0]);
	CHECK(arr[1] == arr1[1]);
	CHECK(arr[2] == arr1[3]);
	CHECK(arr[3] == 5.5);
	CHECK(arr[4] == arr1[4]);
}
>>>>>>> d41395efa836f5c7d767c2452853c96d33f87cda
