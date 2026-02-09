#include <gtest/gtest.h>
#include "vector.h"

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
