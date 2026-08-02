#include "vector.hpp"

#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <utility>

namespace
{
dsa::Vector<int> fill_vector(size_t n)
{
    dsa::Vector<int> vector;
    for (size_t i = 1uz; i <= n; ++i) {
        vector.push_back(i);
    }
    return vector;
}

dsa::Vector<std::unique_ptr<int>> fill_vector_heap_refs(size_t n)
{
    dsa::Vector<std::unique_ptr<int>> vector;
    for (size_t i = 1uz; i <= n; ++i) {
        vector.push_back(std::make_unique<int>(i));
    }
    return vector;
}

template <typename T>
void expect_unique_ptr_vector_eq(const dsa::Vector<std::unique_ptr<T>>& v,
                                 const dsa::Vector<std::unique_ptr<T>>& expected)
{
    ASSERT_EQ(v.size(), expected.size());
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(*v[i], *expected[i]);
    }
}
} // namespace

namespace dsa
{

template <typename T>
void PrintTo(const Vector<T>& v, std::ostream* os)
{
    *os << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) {
            *os << ", ";
        }
        *os << ::testing::PrintToString(v[i]); // handles nested types too
    }
    *os << "] (size=" << v.size() << ", capacity=" << v.capacity() << ")";
}

} // namespace dsa

TEST(tests, vector_constructor)
{
    dsa::Vector<int> vector;
    EXPECT_EQ(vector.size(), 0uz) << "vector is not empty at construction";
    EXPECT_EQ(vector.capacity(), 0uz) << "vector capacity shall be 0 at construction";
}

TEST(tests, vector_init_list_ctor)
{
    dsa::Vector<int> vector{1, 2, 3};
    dsa::Vector<int> expected_vector;
    expected_vector.push_back(1);
    expected_vector.push_back(2);
    expected_vector.push_back(3);
    EXPECT_EQ(vector, expected_vector)
        << "vector init ctor is not initializing the values correctly";
}

TEST(tests, vector_copy_ctor)
{
    dsa::Vector<int> vector;
    vector.push_back(1);
    dsa::Vector<int> copied_vector(vector);
    EXPECT_EQ(copied_vector.size(), vector.size())
        << "vector copy constructor is not copying the vector size correctly";
    EXPECT_EQ(copied_vector.capacity(), vector.capacity())
        << "vector copy constructor is not copying the vector capacity correctly";
    EXPECT_EQ(vector, copied_vector) << "vector copy constructor is not copying correctly";
}

TEST(tests, vector_copy_ctor_different)
{
    dsa::Vector<int> vector;
    vector.push_back(1);
    dsa::Vector<int> copied_vector(vector);
    copied_vector.at(0) = 2;
    EXPECT_EQ(copied_vector.size(), vector.size())
        << "vector copy constructor is not copying the vector size correctly";
    EXPECT_EQ(copied_vector.capacity(), vector.capacity())
        << "vector copy constructor is not copying the vector capacity correctly";
    EXPECT_EQ(vector.at(0), 1) << "vector copy constructor is not copying correctly";
    EXPECT_EQ(copied_vector.at(0), 2) << "vector copy constructor is not copying correctly";
}

TEST(tests, vector_copy_asignment)
{
    dsa::Vector<int> vector;
    vector.push_back(1);
    dsa::Vector<int> copied_vector = vector;
    EXPECT_EQ(copied_vector.size(), vector.size())
        << "vector copy operator is not copying the vector size correctly";
    EXPECT_EQ(copied_vector.capacity(), vector.capacity())
        << "vector copy operator is not copying the vector capacity correctly";
    EXPECT_EQ(vector, copied_vector) << "vector copy constructor is not copying correctly";
}

TEST(tests, vector_copy_asignment_different)
{
    dsa::Vector<int> vector;
    vector.push_back(1);
    dsa::Vector<int> copied_vector = vector;
    copied_vector.at(0) = 2;
    EXPECT_EQ(copied_vector.size(), vector.size())
        << "vector copy operator is not copying the vector size correctly";
    EXPECT_EQ(copied_vector.capacity(), vector.capacity())
        << "vector copy operator is not copying the vector capacity correctly";
    EXPECT_EQ(vector.at(0), 1) << "vector copy constructor is not copying correctly";
    EXPECT_EQ(copied_vector.at(0), 2) << "vector copy constructor is not copying correctly";
}

TEST(tests, vector_move_ctor)
{
    dsa::Vector<int> vector;
    vector.push_back(1);

    const int* original_data_address = &vector.at(0);

    dsa::Vector<int> moved_vector(std::move(vector));
    EXPECT_EQ(&moved_vector.at(0), original_data_address)
        << "vector move ctor is not moving the data";

    EXPECT_EQ(vector.size(), 0) << "old vector hasn't been cleaned";
    EXPECT_EQ(vector.capacity(), 0) << "old vector hasn't been cleaned";
}

TEST(tests, vector_move_operator)
{
    dsa::Vector<int> vector;
    vector.push_back(1);

    const int* original_data_address = &vector.at(0);

    dsa::Vector<int> moved_vector;
    moved_vector = std::move(vector);
    EXPECT_EQ(&moved_vector.at(0), original_data_address)
        << "vector move operator is not moving the data";

    EXPECT_EQ(vector.size(), 0) << "old vector hasn't been cleaned";
    EXPECT_EQ(vector.capacity(), 0) << "old vector hasn't been cleaned";
}

TEST(tests, vector_reserve)
{
    dsa::Vector<int> vector;
    auto resize_value{100uz};
    vector.reserve(resize_value);
    EXPECT_EQ(vector.size(), 0uz) << "vector resize changes size when it shouldn't";
    EXPECT_EQ(vector.capacity(), resize_value)
        << "vector resize doesn't change the capacity correctly";
}

TEST(tests, vector_push_back)
{
    dsa::Vector<int> vector;
    int element_to_insert = 1;
    vector.push_back(element_to_insert);
    EXPECT_EQ(vector.size(), 1uz) << "vector push back doesn't increase the size";
    EXPECT_EQ(vector.at(0), element_to_insert);
}

TEST(tests, vector_push_back_multiple_elements)
{
    dsa::Vector<int> vector;
    for (int idx{0}; idx < 40; ++idx) {
        vector.push_back(idx);
    }
    for (auto idx{0uz}; idx < 40; ++idx) {
        EXPECT_EQ(vector.at(idx), idx) << "vector push back doesn't insert properly the elements";
    }
}

TEST(tests, vector_push_back_resize)
{
    dsa::Vector<int> vector;
    for (int idx{0uz}; idx < 75; ++idx) {
        vector.push_back(idx);
    }
    EXPECT_EQ(vector.size(), 75) << "vector push back doesn't increase the size properly";
    EXPECT_EQ(vector.capacity(), 128) << "vector push back doesn't increase the capacity";
}

TEST(tests, vector_access_operator)
{
    dsa::Vector<int> vector;
    vector.push_back(10);

    const int value_to_compare = 10;
    EXPECT_EQ(vector[0], value_to_compare) << "vector operator[] doesn't retrieve a reference";
}

TEST(tests, vector_at)
{
    dsa::Vector<int> vector;
    vector.push_back(10);
    EXPECT_NO_THROW(vector.at(0));

    const int value_to_compare = 10;
    EXPECT_EQ(vector.at(0), value_to_compare) << "vector at doesn't retrieve a reference";
}

TEST(tests, vector_at_out_of_bounds)
{
    dsa::Vector<int> vector;
    for (int idx{0uz}; idx < 75; ++idx) {
        vector.push_back(idx);
    }
    EXPECT_THROW(vector.at(76), std::out_of_range)
        << "vector at doesn't raises an exception accessing out of bounds";
}

TEST(tests, vector_at_init_out_of_bounds)
{
    dsa::Vector<int> vector;
    EXPECT_THROW(vector.at(1), std::out_of_range)
        << "vector at doesn't raises an exception accessing out of bounds";
}

TEST(tests, vector_equal_op_no_size)
{
    dsa::Vector<int> vector;
    dsa::Vector<int> other_vector;
    EXPECT_EQ(vector, other_vector) << "vector eq operator is not working properly";
}

TEST(tests, vector_pop_back)
{
    auto vector = fill_vector_heap_refs(10);
    vector.pop_back();
    dsa::Vector<std::unique_ptr<int>> expected_vector;
    expected_vector.push_back(std::make_unique<int>(1));
    expected_vector.push_back(std::make_unique<int>(2));
    expected_vector.push_back(std::make_unique<int>(3));
    expected_vector.push_back(std::make_unique<int>(4));
    expected_vector.push_back(std::make_unique<int>(5));
    expected_vector.push_back(std::make_unique<int>(6));
    expected_vector.push_back(std::make_unique<int>(7));
    expected_vector.push_back(std::make_unique<int>(8));
    expected_vector.push_back(std::make_unique<int>(9));
    expect_unique_ptr_vector_eq(vector, expected_vector);
}

TEST(tests, vector_pop_back_empty)
{
    auto vector = dsa::Vector<int>{};
    EXPECT_THROW(vector.pop_back(), std::runtime_error);
}

TEST(tests, vector_clear)
{
    auto vector = fill_vector_heap_refs(100);
    vector.clear();
    EXPECT_EQ(vector.size(), 0);
    vector.push_back(std::make_unique<int>(1));
    EXPECT_EQ(vector.size(), 1);
}

TEST(tests, vector_empty)
{
    auto vector = fill_vector_heap_refs(100);
    vector.clear();
    EXPECT_TRUE(vector.empty());
}

TEST(tests, vector_front)
{
    auto vector = fill_vector(2);
    EXPECT_EQ(vector.front(), 1uz);
}

TEST(tests, vector_back)
{
    auto vector = fill_vector(20);
    EXPECT_EQ(vector.back(), 20uz);
}

TEST(tests, vector_data)
{
    auto vector = fill_vector(5);
    EXPECT_EQ(vector.data(), &vector[0]);
}

TEST(tests, vector_data_empty)
{
    dsa::Vector<int> vector;
    EXPECT_EQ(vector.data(), nullptr);
}

TEST(tests, vector_resize)
{
    auto vector = fill_vector_heap_refs(5);
    vector.resize(10);
    ASSERT_EQ(vector.size(), 10);
    for (size_t i = 0; i < 5; ++i) {
        ASSERT_NE(vector[i], nullptr);
        EXPECT_EQ(*vector[i], static_cast<int>(i + 1));
    }
    for (size_t i = 5; i < 10; ++i) {
        EXPECT_EQ(vector[i], nullptr);
    }
}

TEST(tests, vector_resize_init_value)
{
    auto vector = fill_vector(5);
    vector.resize(10, 14);
    dsa::Vector expected_vector = {1, 2, 3, 4, 5, 14, 14, 14, 14, 14};
    EXPECT_EQ(vector, expected_vector);
}

TEST(tests, vector_insert)
{
    auto vector = fill_vector(10);
    vector.insert(5, 14);
    dsa::Vector expected_vector = {1, 2, 3, 4, 5, 14, 6, 7, 8, 9, 10};
    EXPECT_EQ(vector, expected_vector);
}

TEST(tests, vector_insert_out_of_pos)
{
    auto vector = dsa::Vector<int>{};
    EXPECT_THROW(vector.insert(5, 14), std::out_of_range);
}

TEST(tests, vector_insert_empty)
{
    auto vector = dsa::Vector<int>{};
    vector.insert(0, 1);
    dsa::Vector expected_vector = {1};
    EXPECT_EQ(vector, expected_vector);
}

TEST(tests, vector_erase)
{
    auto vector = fill_vector_heap_refs(10);
    vector.erase(5);
    dsa::Vector<std::unique_ptr<int>> expected_vector;
    expected_vector.push_back(std::make_unique<int>(1));
    expected_vector.push_back(std::make_unique<int>(2));
    expected_vector.push_back(std::make_unique<int>(3));
    expected_vector.push_back(std::make_unique<int>(4));
    expected_vector.push_back(std::make_unique<int>(5));
    expected_vector.push_back(std::make_unique<int>(7));
    expected_vector.push_back(std::make_unique<int>(8));
    expected_vector.push_back(std::make_unique<int>(9));
    expected_vector.push_back(std::make_unique<int>(10));
    expect_unique_ptr_vector_eq(vector, expected_vector);
}

TEST(tests, vector_erase_empty)
{
    auto vector = dsa::Vector<int>{};
    EXPECT_THROW(vector.erase(2), std::out_of_range);
}

TEST(tests, vector_erase_first)
{
    auto vector = fill_vector_heap_refs(10);
    vector.erase(0);
    dsa::Vector<std::unique_ptr<int>> expected_vector;
    expected_vector.push_back(std::make_unique<int>(2));
    expected_vector.push_back(std::make_unique<int>(3));
    expected_vector.push_back(std::make_unique<int>(4));
    expected_vector.push_back(std::make_unique<int>(5));
    expected_vector.push_back(std::make_unique<int>(6));
    expected_vector.push_back(std::make_unique<int>(7));
    expected_vector.push_back(std::make_unique<int>(8));
    expected_vector.push_back(std::make_unique<int>(9));
    expected_vector.push_back(std::make_unique<int>(10));
    expect_unique_ptr_vector_eq(vector, expected_vector);
}

TEST(tests, vector_erase_last)
{
    const size_t size = 10;
    const size_t last_pos = size - 1;
    auto vector = fill_vector_heap_refs(size);
    vector.erase(last_pos);
    dsa::Vector<std::unique_ptr<int>> expected_vector;
    expected_vector.push_back(std::make_unique<int>(1));
    expected_vector.push_back(std::make_unique<int>(2));
    expected_vector.push_back(std::make_unique<int>(3));
    expected_vector.push_back(std::make_unique<int>(4));
    expected_vector.push_back(std::make_unique<int>(5));
    expected_vector.push_back(std::make_unique<int>(6));
    expected_vector.push_back(std::make_unique<int>(7));
    expected_vector.push_back(std::make_unique<int>(8));
    expected_vector.push_back(std::make_unique<int>(9));
    expect_unique_ptr_vector_eq(vector, expected_vector);
}
