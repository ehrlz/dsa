#pragma once

#include <cstddef>
#include <cstdlib>
#include <stdexcept>

namespace dsa
{

template <typename T> class Vector
{

  public:
    Vector()
        : size_(0uz), capacity_(50uz), data(nullptr)
    {
        data = static_cast<T*>(::operator new(capacity_ * sizeof(T)));
    }

    ~Vector()
    {
        for (auto idx{0uz}; idx < size_; ++idx)
        {
            data[idx].~T();
        }
        ::operator delete(data);
    }

    // TODO copy constructor
    // TODO copy assignment
    // TODO move constructor
    // TODO move assignment

    // Returns the number of elements in the vector
    std::size_t size() const
    {
        return size_;
    }

    // Returns the number of elements that could fit in the reserved memory
    std::size_t capacity() const
    {
        return capacity_;
    }

    T* swap_data(std::size_t new_capacity)
    {
        // reserves new memory
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

        // moves or copies each element from the old array
        for (auto idx{0uz}; idx < size_; ++idx)
        {
            try
            {
                new (new_data + idx) T(std::move(data[idx]));
            }
            catch (...)
            {
                // cleans and rethrows
                for (auto clean_idx{0uz}; clean_idx < idx; ++clean_idx)
                {
                    new_data[clean_idx].~T();
                }
                ::operator delete(new_data);
                throw;
            }
        }

        // cleans the old array
        for (auto idx{0uz}; idx < size_; ++idx)
        {
            data[idx].~T();
        }
        ::operator delete(data);

        capacity_ = new_capacity;
        return new_data;
    }

    // Reserves a new slot of memory if more memory is requested.
    // Data is moved or copied
    void reserve(std::size_t new_capacity)
    {
        if (new_capacity <= size_) // no reallocation needed
        {
            return;
        }
        data = swap_data(new_capacity);
    }

    // Adds the element at the end of the list
    template <typename U> void push_back(const U& elem)
    {
        static_assert(std::is_same<T, U>::value, "push_back argument type must exactly match Vector type");
        if (size_ == capacity_) // reallocation needed
        {
            data = swap_data(size_ * 2);
        }
        new (data + size_) T(elem);
        size_++;
    }

    // Access an element of the list
    T at(std::size_t idx)
    {
        if (idx >= size_)
        {
            throw std::invalid_argument("vector: out of bounds access");
        }
        return data[idx];
    }

  private:
    T* data;               // data stored in the heap
    std::size_t size_;     // actual elements
    std::size_t capacity_; // max reserved capacity
};

} // namespace dsa
