#include <gtest/gtest.h>
#include "vector.h"

TEST(tests, vector_constructor) 
{
	dsa::Vector<int> vector;
	EXPECT_EQ(vector.size(), 0uz) << "vector is not empty at construction";
	EXPECT_GT(vector.capacity(), vector.size()) << "vector capacity shall be greater than size at construction";
}

