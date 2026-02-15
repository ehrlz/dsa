#pragma once

#include <cstddef>
#include <cstdlib>
#include <new>
#include <stdexcept>
#include <utility>

namespace dsa
{

template <typename T> class Vector
{

  public:
    Vector()
        : size_(0uz), capacity_(50uz), data_(nullptr)
    {
        data_ = static_cast<T*>(::operator new(capacity_ * sizeof(T)));
    }

    ~Vector()
    {
        for (auto idx{0uz}; idx < size_; ++idx)
        {
            data_[idx].~T();
        }
        ::operator delete(data_);
        data_ = nullptr;
    }

    Vector(const Vector& other_vector)
        : size_(other_vector.size_), capacity_(other_vector.capacity_), data_(nullptr)
    {
        data_ = static_cast<T*>(::operator new(capacity_ * sizeof(T)));

        for (auto idx{0uz}; idx < other_vector.size_; ++idx)
        {
            data_[idx] = other_vector.at(idx);
        }
    }

    Vector& operator=(const Vector& other_vector)
    {
        size_ = other_vector.size_;
        capacity_ = other_vector.capacity_;
        data_ = static_cast<T*>(::operator new(capacity_ * sizeof(T)));
        for (auto idx{0uz}; idx < other_vector.size_; ++idx)
        {
            data_[idx] = other_vector.at(idx);
        }
    }

    Vector(Vector&& other_vector) noexcept
        : size_(other_vector.size_), capacity_(other_vector.capacity_), data_(other_vector.data_)
    {
        // Nullify. Other case the old object will delete the moved mem. direction
        other_vector.nullify();
    }

    Vector& operator=(Vector&& other_vector)
    {
        size_ = other_vector.size_;
        capacity_ = other_vector.capacity_;
        data_ = other_vector.data_;

        other_vector.nullify();
        return *this;
    }

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

    // Reserves a new slot of memory if more memory is requested.
    // Data is moved or copied
    void reserve(std::size_t new_capacity)
    {
        if (new_capacity <= capacity_) // no reallocation needed
        {
            return;
        }
        reallocate(new_capacity);
    }

    // Adds the element at the end of the list
    template <typename U> void push_back(U&& elem)
    {
        if (size_ == capacity_) // reallocation needed
        {
            reallocate(size_ * 2);
        }
        new (data_ + size_) T(std::forward<U>(elem));
        size_++;
    }

    // Access an element of the list
    T& at(std::size_t idx)
    {
        if (idx >= size_)
        {
            throw std::out_of_range("vector: out of bounds access");
        }
        return data_[idx];
    }

    // Const access an element of the list
    const T& at(std::size_t idx) const
    {
        if (idx >= size_)
        {
            throw std::out_of_range("vector: out of bounds access");
        }
        return data_[idx];
    }

    // TODO implement operator[]

  private:
    T* data_;              // data stored in the heap
    std::size_t size_;     // actual elements
    std::size_t capacity_; // max reserved capacity

    void reallocate(std::size_t new_capacity)
    {
        // reserves new memory
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

        // moves or copies each element from the old array
        for (auto idx{0uz}; idx < size_; ++idx)
        {
            try
            {
                new (new_data + idx) T(std::move_if_noexcept(data_[idx]));
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
            data_[idx].~T();
        }
        ::operator delete(data_);

        data_ = new_data;
        capacity_ = new_capacity;
    }

    void nullify()
    {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }
};

} // namespace dsa
