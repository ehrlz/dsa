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
    // ctors and dtors
    Vector()
        : data_(nullptr), size_(0uz), capacity_(0uz)
    {
    }

    Vector(std::initializer_list<T> init)
        : data_(nullptr), size_(0uz), capacity_(init.size())
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
        : data_(nullptr), size_(other.size_), capacity_(other.size_)
    {
        if (capacity_ > 0) {
            data_ = static_cast<T*>(::operator new(capacity_ * sizeof(T)));
            std::uninitialized_copy(other.begin(), other.end(), data_);
        }
    }

    Vector& operator=(const Vector& other)
    {
        if (this != &other) {
            Vector tmp(other);
            swap(tmp);
        }
        return *this;
    }

    Vector(Vector&& other) noexcept
        : data_(nullptr), size_(0uz), capacity_(0uz)
    {
        swap(other);
    }

    Vector& operator=(Vector&& other) noexcept
    {
        if (this != &other) {
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
        if (size_ != other_vector.size_) {
            return false;
        }
        for (auto idx{0uz}; idx < size_; ++idx) {
            if (data_[idx] != other_vector.data_[idx]) {
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

    // note: push back a self-reference is UB
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
            std::size_t new_cap = capacity_ == 0 ? 1 : size_ * GROW_FACTOR;
            reallocate(new_cap);
        }

        T* ptr = std::construct_at(data_ + size_, std::forward<Args>(args)...);
        size_++;
        return *ptr;
    }

    // accesses

    const T& at(std::size_t idx) const
    {
        if (idx >= size_) {
            throw std::out_of_range("vector: out of bounds access");
        }
        return data_[idx];
    }

    T& at(std::size_t idx)
    {
        return const_cast<T&>(std::as_const(*this).at(idx));
    }

    // No bounds checking (faster. use at to access with safety)
    const T& operator[](std::size_t idx) const
    {
        return data_[idx];
    }

    T& operator[](std::size_t idx)
    {
        return const_cast<T&>(std::as_const(*this)[idx]);
    }

    void pop_back()
    {
        if (size_ == 0) {
            throw std::runtime_error("vector: popping back an empty vector");
        }
        data_[size_ - 1].~T();
        --size_;
    }

    void clear()
    {
        clear_data_elems();
        size_ = 0;
    }

    bool empty()
    {
        return size_ == 0;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    T& front()
    {
        return data_[0];
    }

    const T& front() const
    {
        return data_[0];
    }

    T& back()
    {
        return data_[size_ - 1];
    }

    const T& back() const
    {
        return data_[size_ - 1];
    }

    T* data() noexcept
    {
        return data_;
    }

    const T* data() const noexcept
    {
        return data_;
    }

    void resize(size_t n)
    {

        if (n > capacity_) {
            reallocate(n);
        }
        if (n > size_) {
            for (size_t i = size_; i < n; ++i) {
                std::construct_at(data_ + i);
            }
        } else if (n < size_) {
            for (size_t i = n; i < size_; ++i) {
                data_[i].~T();
            }
        }
        size_ = n;
    }

    void resize(size_t n, const T& value)
    {
        if (n > capacity_) {
            reallocate(n);
        }
        if (n > size_) {
            for (size_t i = size_; i < n; ++i) {
                ::new (static_cast<void*>(std::addressof(data_[i]))) T(value);
            }
        } else if (n < size_) {
            for (size_t i = n; i < size_; ++i) {
                data_[i].~T();
            }
        }
        size_ = n;
    }

    // note: inserting a self-reference is UB
    void insert(std::size_t pos, const T& elem)
    {
        if (pos > size_) {
            throw std::out_of_range("invalid position");
        }

        if (size_ == capacity_) {
            reallocate(capacity_ == 0 ? 1 : capacity_ * GROW_FACTOR);
        }

        // move elems to the right
        if (size_ > pos) {
            std::construct_at(data_ + size_, std::move(data_[size_ - 1]));
            for (size_t i = size_ - 1; i > pos; --i) {
                data_[i] = std::move(data_[i - 1]);
            }
            data_[pos] = elem;
        } else { // inserting last
            std::construct_at(data_ + pos, elem);
        }

        ++size_;
    }

    void erase(size_t pos)
    {
        if (pos >= size_) {
            throw std::out_of_range("vector: erasing out of bounds");
        }

        // move elems to the left
        for (size_t i = pos; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }

        data_[size_ - 1].~T();

        --size_;
    }

  private:
    T* data_;              // data stored in the heap
    std::size_t size_;     // actual elements
    std::size_t capacity_; // max reserved capacity

    static constexpr std::size_t GROW_FACTOR = 2;

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
        for (auto idx{0uz}; idx < size_; ++idx) {
            try {
                new (new_data + idx) T(std::move_if_noexcept(data_[idx]));
            } catch (...) {
                // cleans and rethrows
                for (auto clean_idx{0uz}; clean_idx < idx; ++clean_idx) {
                    new_data[clean_idx].~T();
                }
                ::operator delete(new_data);
                throw;
            }
        }

        // cleans the old array
        for (auto idx{0uz}; idx < size_; ++idx) {
            data_[idx].~T();
        }
        ::operator delete(data_);

        data_ = new_data;
        capacity_ = new_capacity;
    }

    void clear_memory()
    {
        if (data_) {
            clear_data_elems();
            ::operator delete(data_);
        }
    }

    void clear_data_elems()
    {
        std::destroy_n(data_, size_);
    }
};

} // namespace dsa
