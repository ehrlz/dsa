#include "vector.h"

#include <gtest/gtest.h>

TEST(tests, vector_constructor)
{
    dsa::Vector<int> vector;
    EXPECT_EQ(vector.size(), 0uz) << "vector is not empty at construction";
    EXPECT_GT(vector.capacity(), vector.size()) << "vector capacity shall be greater than size at construction";
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
    EXPECT_EQ(vector.capacity(), 100) << "vector push back doesn't increase the capacity";
}

TEST(tests, vector_at_out_of_bounds)
{
    dsa::Vector<int> vector;
    for (int idx{0uz}; idx < 75; ++idx)
    {
        vector.push_back(idx);
    }
    EXPECT_THROW(vector.at(76), std::invalid_argument)
        << "vector at doesn't raises an exception accessing out of bounds";
}

TEST(tests, vector_at_init_out_of_bounds)
{
    dsa::Vector<int> vector;
    EXPECT_THROW(vector.at(1), std::invalid_argument)
        << "vector at doesn't raises an exception accessing out of bounds";
}

TEST(tests, vector_at)
{
    dsa::Vector<int> vector;
    vector.push_back(1);
    EXPECT_NO_THROW(vector.at(0));
}
