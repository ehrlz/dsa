#include "linked_list.hpp"

#include <gtest/gtest.h>

TEST(linked_list, ll_ctor)
{
    dsa::LinkedList<int> list;
    EXPECT_EQ(list.size(), 0uz) << "list empty at construction";
}

TEST(linked_list, ll_copy_ctor)
{
    dsa::LinkedList<int> src = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    dsa::LinkedList<int> dst(src);
    EXPECT_EQ(dst, src);
}

TEST(linked_list, ll_copy_ctor_empty)
{
    dsa::LinkedList<int> src;
    dsa::LinkedList<int> dst(src);
    EXPECT_EQ(dst, src);
}

TEST(linked_list, ll_move_ctor)
{
    dsa::LinkedList<int> src = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    dsa::LinkedList<int> expected_dst(src);
    dsa::LinkedList<int> dst(std::move(src));
    EXPECT_EQ(dst, expected_dst);
    EXPECT_EQ(src.size(), 0);
}

TEST(linked_list, ll_move_ctor_empty)
{
    dsa::LinkedList<int> src;
    dsa::LinkedList<int> expected_dst(src);
    dsa::LinkedList<int> dst(std::move(src));
    EXPECT_EQ(dst, expected_dst);
    EXPECT_EQ(src.size(), 0);
}

TEST(linked_list, ll_append)
{
    dsa::LinkedList<int> list;
    const int n = 14;
    for (int i = 0; i < n; ++i) {
        list.append(i);
    }

    dsa::LinkedList<int> expected_list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, ll_size)
{
    dsa::LinkedList<int> list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(list.size(), 14);
}

TEST(linked_list, ll_size_empty)
{
    dsa::LinkedList<int> list;
    EXPECT_EQ(list.size(), 0);
}

TEST(linked_list, ll_front)
{
    dsa::LinkedList list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(list.front(), 0);
}

TEST(linked_list, ll_back)
{
    dsa::LinkedList list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(list.back(), 13);
}
