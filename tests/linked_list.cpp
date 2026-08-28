
#include "linked_list.hpp"

#include <forward_list>
#include <gtest/gtest.h>

TEST(linked_list, ll_ctor)
{
    dsa::LinkedList<int> list;
    EXPECT_EQ(list.size(), 0uz) << "list empty at construction";
}

TEST(linked_list, ll_append)
{
    dsa::LinkedList<int> list;
    const int n = 14;
    for (int i = 0; i < n; ++i) {
        list.append(n);
    }

    auto expected_list = dsa::LinkedList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    // EXPECT_EQ(list, expected_list);
    EXPECT_EQ(list.size(), n) << "list empty at construction";
}

TEST(linked_list, ll_size)
{
    auto list = dsa::LinkedList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(list.size(), 14);
}

TEST(linked_list, ll_size_empty)
{
    dsa::LinkedList<int> list;
    EXPECT_EQ(list.size(), 0);
}

TEST(linked_list, ll_front)
{
    auto list = dsa::LinkedList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(list.front(), 0);
}

TEST(linked_list, ll_back)
{
    auto list = dsa::LinkedList{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(list.back(), 13);
}
