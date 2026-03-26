#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <memory>
#include <new>
#include <stdexcept>
#include <utility>

namespace dsa
{

template <typename T>
class Vector
{

  public:
    // TODO iterator support

    // ctors and dtors
    Vector()
        : size_(0uz), capacity_(0uz), data_(nullptr)
    {
    }

    Vector(std::initializer_list<T> init)
        : size_(0uz), capacity_(init.size()), data_(nullptr)
    {
        data_ = static_cast<T*>(::operator new(capacity_ * sizeof(T)));

        std::uninitialized_copy(init.begin(), init.end(), data_);
        size_ = init.size();
    }

    ~Vector()
    {
        clear_memory();
    }

    Vector(const Vector& other)
        : size_(other.size_), capacity_(other.size_), data_(nullptr)
    {
        if (capacity_ > 0)
        {
            data_ = static_cast<T*>(::operator new(capacity_ * sizeof(T)));
            std::uninitialized_copy(other.begin(), other.end(), data_);
        }
    }

    Vector& operator=(const Vector& other)
    {
        if (this != &other)
        {
            Vector tmp(other);
            swap(tmp);
        }
        return *this;
    }

    Vector(Vector&& other) noexcept
        : size_(0uz), capacity_(0uz), data_(nullptr)
    {
        swap(other);
    }

    Vector& operator=(Vector&& other)
    {
        if (this != &other)
        {
            // other holds our data and destroys it at out of scope
            swap(other);
        }
        return *this;
    }

    // iterators
    T* begin() noexcept
    {
        return data_;
    }
    T* end() noexcept
    {
        return data_ + size_;
    }
    const T* begin() const noexcept
    {
        return data_;
    }
    const T* end() const noexcept
    {
        return data_ + size_;
    }

    // operators

    // 2 vectors are consider equal if they have the same size and elements in the same order
    bool operator==(const Vector& other_vector) const
    {
        if (size_ != other_vector.size_)
        {
            return false;
        }
        for (auto idx{0uz}; idx < size_; ++idx)
        {
            if (data_[idx] != other_vector.data_[idx])
            {
                return false;
            }
        }
        return true;
    }

    std::size_t size() const noexcept
    {
        return size_;
    }

    std::size_t capacity() const noexcept
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

    void push_back(const T& elem)
    {
        emplace_back(elem);
    }

    void push_back(T&& elem)
    {
        emplace_back(std::move(elem));
    }

    // Variadic template for constructing in place
    template <typename... Args>
    T& emplace_back(Args&&... args)
    {
        if (size_ == capacity_) // reallocation needed
        {
            std::size_t new_cap = capacity_ == 0 ? 1 : size_ * 2;
            reallocate(new_cap);
        }

        T* ptr = std::construct_at(data_ + size_, std::forward<Args>(args)...);
        size_++;
        return *ptr;
    }

    // accesses
    T& at(std::size_t idx)
    {
        if (idx >= size_)
        {
            throw std::out_of_range("vector: out of bounds access");
        }
        return data_[idx];
    }

    const T& at(std::size_t idx) const
    {
        if (idx >= size_)
        {
            throw std::out_of_range("vector: out of bounds access");
        }
        return data_[idx];
    }

    // No bounds checking (faster. use at to access with safety)
    T& operator[](std::size_t idx)
    {
        return data_[idx];
    }

    const T& operator[](std::size_t idx) const
    {
        return data_[idx];
    }

  private:
    T* data_;              // data stored in the heap
    std::size_t size_;     // actual elements
    std::size_t capacity_; // max reserved capacity

    void swap(Vector& other) noexcept
    {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(data_, other.data_);
    }

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

    void clear_memory()
    {
        if (data_)
        {
            std::destroy_n(data_, size_);
            ::operator delete(data_);
        }
    }
};

} // namespace dsa
