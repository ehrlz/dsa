#pragma once

#include <cstddef>
#include <cstdlib>

namespace dsa
{

template<typename T> class Vector
{

public:

	Vector()
		: size_(0uz)
		, capacity_(50uz)
	{
		data = malloc(capacity_ * sizeof(T));
	}

	Vector(std::size_t size, T element)
		: size_(size)
		, capacity_(size_ * 2)
	{
		data = malloc(capacity_ * sizeof(T));
	}

	~Vector()
	{
		free(data);
	}

	std::size_t size() const
	{
		return size_;
	}

	std::size_t capacity() const
	{
		return capacity_;
	}

private:
	void *data;						// data stored in the heap
	std::size_t size_;			// actual elements
	std::size_t capacity_; // max reserved capacity
};

}

