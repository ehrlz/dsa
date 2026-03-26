#include "vector.h"

#include <gtest/gtest.h>
#include <utility>

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
    EXPECT_EQ(vector, expected_vector) << "vector init ctor is not initializing the values correctly";
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
    EXPECT_EQ(copied_vector.size(), vector.size()) << "vector copy operator is not copying the vector size correctly";
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
    EXPECT_EQ(copied_vector.size(), vector.size()) << "vector copy operator is not copying the vector size correctly";
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
    EXPECT_EQ(&moved_vector.at(0), original_data_address) << "vector move ctor is not moving the data";

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
    EXPECT_EQ(&moved_vector.at(0), original_data_address) << "vector move operator is not moving the data";

    EXPECT_EQ(vector.size(), 0) << "old vector hasn't been cleaned";
    EXPECT_EQ(vector.capacity(), 0) << "old vector hasn't been cleaned";
}

TEST(tests, vector_reserve)
{
    dsa::Vector<int> vector;
    auto resize_value{100uz};
    vector.reserve(resize_value);
    EXPECT_EQ(vector.size(), 0uz) << "vector resize changes size when it shouldn't";
    EXPECT_EQ(vector.capacity(), resize_value) << "vector resize doesn't change the capacity correctly";
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
    for (int idx{0}; idx < 40; ++idx)
    {
        vector.push_back(idx);
    }
    for (auto idx{0uz}; idx < 40; ++idx)
    {
        EXPECT_EQ(vector.at(idx), idx) << "vector push back doesn't insert properly the elements";
    }
}

TEST(tests, vector_push_back_resize)
{
    dsa::Vector<int> vector;
    for (int idx{0uz}; idx < 75; ++idx)
    {
        vector.push_back(idx);
    }
    EXPECT_EQ(vector.size(), 75) << "vector push back doesn't increase the size properly";
    EXPECT_EQ(vector.capacity(), 128) << "vector push back doesn't increase the capacity";
}

TEST(tests, vector_at)
{
    dsa::Vector<int> vector;
    vector.push_back(1);
    EXPECT_NO_THROW(vector.at(0));

    const int value_to_compare = 10;
    vector.at(0) = value_to_compare;
    EXPECT_EQ(vector.at(0), value_to_compare) << "vector at doesn't retrieve a reference";
}

TEST(tests, vector_at_out_of_bounds)
{
    dsa::Vector<int> vector;
    for (int idx{0uz}; idx < 75; ++idx)
    {
        vector.push_back(idx);
    }
    EXPECT_THROW(vector.at(76), std::out_of_range) << "vector at doesn't raises an exception accessing out of bounds";
}

TEST(tests, vector_at_init_out_of_bounds)
{
    dsa::Vector<int> vector;
    EXPECT_THROW(vector.at(1), std::out_of_range) << "vector at doesn't raises an exception accessing out of bounds";
}

TEST(tests, vector_equal_op_no_size)
{
    dsa::Vector<int> vector;
    dsa::Vector<int> other_vector;
    EXPECT_EQ(vector, other_vector) << "vector eq operator is not working properly";
}
