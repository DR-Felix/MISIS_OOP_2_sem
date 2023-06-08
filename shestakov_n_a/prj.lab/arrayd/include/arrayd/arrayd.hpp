#include <iostream>

#pragma once
#ifndef ARRAYD_ARRAYD_HPP_20230304
#define ARRAYD_ARRAYD_HPP_20230304

const std::exception out_of_range("Error: Out of range");

class ArrayD {
public:
	ArrayD() = default;
	ArrayD(const ArrayD& arr);
	explicit ArrayD(const std::ptrdiff_t size);
	ArrayD& operator=(const ArrayD& rhs);
	~ArrayD() { delete[] data_; }
	std::ptrdiff_t Ssize() const noexcept { return size_; };
	double& operator[](const std::ptrdiff_t i);
	const double& operator[](const std::ptrdiff_t i) const;
	void Resize(const std::ptrdiff_t size);
	void Remove(std::ptrdiff_t index);
	void Insert(double val, std::ptrdiff_t index);
	//
	std::ptrdiff_t ssize() const noexcept { return size_; };
	void resize(const std::ptrdiff_t size);
	void remove(std::ptrdiff_t index);
	void insert(double val, std::ptrdiff_t index);
private:
	std::ptrdiff_t capacity_{ 0 };
	std::ptrdiff_t size_{ 0 };
	double* data_{ nullptr };
};

#endif