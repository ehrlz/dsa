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
		data = static_cast<T*>(malloc(capacity_ * sizeof(T)));
	}

	Vector(std::size_t size, T element)
		: size_(size)
		, capacity_(size_ * 2)
	{
		data = static_cast<T*>(malloc(capacity_ * sizeof(T)));
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

	void reserve(std::size_t size)
	{
		if (size <= size_)
		{
			return;
		}

		T *new_data = static_cast<T*>(malloc(size * sizeof(T)));
		for(auto idx{0uz}; idx < size_; ++idx)
		{
			new_data[idx] = data[idx];
		}
		capacity_ = size;
		free(data);
		data = new_data;
	}

private:
	T *data;							// data stored in the heap
	std::size_t size_;			// actual elements
	std::size_t capacity_;	// max reserved capacity
};

}

