#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <gtest/gtest.h>

#include "linked_list.hpp"

TEST(linked_list, ll_ctor)
{
    dsa::LinkedList<int> list;
    EXPECT_EQ(list.size(), 0) << "list empty at construction";
}

TEST(linked_list, ll_copy_ctor)
{
    dsa::LinkedList<int> src = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    dsa::LinkedList<int> dst(src);
    EXPECT_EQ(dst, src);
}

TEST(linked_list, ll_copy_ctor_string)
{
    dsa::LinkedList<std::string> src = {std::to_string(0),
                                        std::to_string(1),
                                        std::to_string(2),
                                        std::to_string(3),
                                        std::to_string(4)};
    dsa::LinkedList<std::string> dst(src);
    EXPECT_EQ(dst, src);
}

TEST(linked_list, ll_copy_ctor_empty)
{
    dsa::LinkedList<int> src;
    dsa::LinkedList<int> dst(src);
    EXPECT_EQ(dst, src);
}

TEST(linked_list, ll_copy_assignment)
{
    dsa::LinkedList<int> src = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    dsa::LinkedList<int> dst;
    dst = src;
    EXPECT_EQ(dst, src);
}

TEST(linked_list, ll_copy_assignment_string)
{
    dsa::LinkedList<std::string> src = {std::to_string(0),
                                        std::to_string(1),
                                        std::to_string(2),
                                        std::to_string(3),
                                        std::to_string(4)};
    dsa::LinkedList<std::string> dst;
    dst = src;
    EXPECT_EQ(dst, src);
}

TEST(linked_list, ll_copy_assignment_empty)
{
    dsa::LinkedList<int> src;
    dsa::LinkedList<int> dst;
    dst = src;
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

TEST(linked_list, ll_move_ctor_string)
{
    dsa::LinkedList<std::string> src = {std::to_string(0),
                                        std::to_string(1),
                                        std::to_string(2),
                                        std::to_string(3),
                                        std::to_string(4)};
    dsa::LinkedList<std::string> expected_dst(src);
    dsa::LinkedList<std::string> dst(std::move(src));
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

TEST(linked_list, ll_move_assignment)
{
    dsa::LinkedList<int> src = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    dsa::LinkedList<int> expected_dst(src);
    dsa::LinkedList<int> dst;
    dst = std::move(src);
    EXPECT_EQ(dst, expected_dst);
    EXPECT_EQ(src.size(), 0);
}

TEST(linked_list, ll_move_assignment_string)
{
    dsa::LinkedList<std::string> src = {std::to_string(0),
                                        std::to_string(1),
                                        std::to_string(2),
                                        std::to_string(3),
                                        std::to_string(4)};
    dsa::LinkedList<std::string> expected_dst(src);
    dsa::LinkedList<std::string> dst;
    dst = std::move(src);
    EXPECT_EQ(dst, expected_dst);
    EXPECT_EQ(src.size(), 0);
}

TEST(linked_list, ll_move_assignment_empty)
{
    dsa::LinkedList<int> src;
    dsa::LinkedList<int> expected_dst(src);
    dsa::LinkedList<int> dst;
    dst = std::move(src);
    EXPECT_EQ(dst, expected_dst);
    EXPECT_EQ(src.size(), 0);
}

TEST(linked_list, ll_append_last)
{
    dsa::LinkedList<int> list;
    const int n = 14;
    for (int i = 0; i < n; ++i) {
        list.append_last(i);
    }

    dsa::LinkedList<int> expected_list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, ll_append_first)
{
    dsa::LinkedList<int> list;
    const int n = 14;
    for (int i = 0; i < n; ++i) {
        list.append_first(i);
    }

    dsa::LinkedList<int> expected_list = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, ll_append_mix)
{
    dsa::LinkedList<int> list;
    const int n = 5;
    for (int i = 0; i < n; ++i) {
        list.append_last(i);
    }
    for (int i = 0; i < n; ++i) {
        list.append_first(i);
    }
    dsa::LinkedList<int> expected_list = {4, 3, 2, 1, 0, 0, 1, 2, 3, 4};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, ll_append)
{
    dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    list.append(3, 10);
    dsa::LinkedList<int> expected_list{0, 1, 2, 10, 3, 4, 5};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, ll_append_head)
{
    dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    list.append(0, -1);
    dsa::LinkedList<int> expected_list{-1, 0, 1, 2, 3, 4, 5};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, ll_append_empty)
{
    dsa::LinkedList<int> list;
    EXPECT_THROW(list.append(0, 10), std::out_of_range);
}

TEST(linked_list, ll_append_out_of_range)
{
    dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    EXPECT_THROW(list.append(44, 10), std::out_of_range);
}

TEST(linked_list, ll_clear)
{
    dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    list.clear();
    dsa::LinkedList<int> expected_list{};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, ll_remove)
{
    dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    list.remove(2);
    dsa::LinkedList<int> expected_list{0, 1, 3, 4, 5};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, ll_remove_first)
{
    dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    list.remove(0);
    dsa::LinkedList<int> expected_list{1, 2, 3, 4, 5};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, ll_remove_empty)
{
    dsa::LinkedList<int> list{};
    EXPECT_THROW(list.remove(0), std::out_of_range);
}

TEST(linked_list, ll_remove_out_of_bounds)
{
    dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    EXPECT_THROW(list.remove(10), std::out_of_range);
}

TEST(linked_list, ll_pop)
{
    dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    list.pop();
    dsa::LinkedList<int> expected_list{1, 2, 3, 4, 5};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, ll_pop_empty)
{
    dsa::LinkedList<int> list{};
    EXPECT_THROW(list.pop(), std::out_of_range);
}

TEST(linked_list, emplace_last)
{
    dsa::LinkedList<std::string> list = {std::to_string(0),
                                         std::to_string(1),
                                         std::to_string(2),
                                         std::to_string(3),
                                         std::to_string(4)};
    list.emplace_last("44");
    dsa::LinkedList<std::string> expected_list = {std::to_string(0),
                                                  std::to_string(1),
                                                  std::to_string(2),
                                                  std::to_string(3),
                                                  std::to_string(4),
                                                  std::to_string(44)};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, emplace_last_empty)
{
    dsa::LinkedList<std::string> list;
    list.emplace_last("44");
    dsa::LinkedList<std::string> expected_list = {std::to_string(44)};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, emplace_first)
{
    dsa::LinkedList<std::string> list = {std::to_string(0),
                                         std::to_string(1),
                                         std::to_string(2),
                                         std::to_string(3),
                                         std::to_string(4)};
    list.emplace_first("44");
    dsa::LinkedList<std::string> expected_list = {std::to_string(44),
                                                  std::to_string(0),
                                                  std::to_string(1),
                                                  std::to_string(2),
                                                  std::to_string(3),
                                                  std::to_string(4)};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, emplace)
{
    dsa::LinkedList<std::string> list = {std::to_string(0),
                                         std::to_string(1),
                                         std::to_string(2),
                                         std::to_string(3),
                                         std::to_string(4)};
    list.emplace(3, "44");
    dsa::LinkedList<std::string> expected_list = {std::to_string(0),
                                                  std::to_string(1),
                                                  std::to_string(2),
                                                  std::to_string(44),
                                                  std::to_string(3),
                                                  std::to_string(4)};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, emplace_head)
{
    dsa::LinkedList<std::string> list = {std::to_string(0),
                                         std::to_string(1),
                                         std::to_string(2),
                                         std::to_string(3),
                                         std::to_string(4)};
    list.emplace(0, "44");
    dsa::LinkedList<std::string> expected_list = {std::to_string(44),
                                                  std::to_string(0),
                                                  std::to_string(1),
                                                  std::to_string(2),
                                                  std::to_string(3),
                                                  std::to_string(4)};
    EXPECT_EQ(list, expected_list);
}

TEST(linked_list, emplace_empty)
{
    dsa::LinkedList<std::string> list;
    EXPECT_THROW(list.emplace(0, "44"), std::out_of_range);
}

TEST(linked_list, emplace_out_of_bounds)
{
    dsa::LinkedList<std::string> list = {std::to_string(0),
                                         std::to_string(1),
                                         std::to_string(2),
                                         std::to_string(3),
                                         std::to_string(4)};
    EXPECT_THROW(list.emplace(10, "44"), std::out_of_range);
}

TEST(linked_list, access_operator)
{
    dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    EXPECT_EQ(list[0], 0);
}

TEST(linked_list, access_operator_const)
{
    const dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    EXPECT_EQ(list[0], 0);
}

TEST(linked_list, at)
{
    dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    EXPECT_EQ(list.at(0), 0);
}

TEST(linked_list, at_empty)
{
    dsa::LinkedList<int> list;
    EXPECT_THROW(list.at(0), std::out_of_range);
}

TEST(linked_list, at_out_of_bounds)
{
    dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    EXPECT_THROW(list.at(10), std::out_of_range);
}

TEST(linked_list, at_const)
{
    const dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    EXPECT_EQ(list.at(0), 0);
}

TEST(linked_list, at_empty_const)
{
    const dsa::LinkedList<int> list;
    EXPECT_THROW(list.at(0), std::out_of_range);
}

TEST(linked_list, at_out_of_bounds_const)
{
    const dsa::LinkedList<int> list{0, 1, 2, 3, 4, 5};
    EXPECT_THROW(list.at(10), std::out_of_range);
}

TEST(linked_list, ll_size)
{
    dsa::LinkedList<int> list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(list.size(), 14);
}

TEST(linked_list, ll_size_empty)
{
    dsa::LinkedList<int> list;
    EXPECT_TRUE(list.empty());
}

TEST(linked_list, ll_front)
{
    dsa::LinkedList list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(list.front(), 0);
}

TEST(linked_list, ll_front_const)
{
    const dsa::LinkedList list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(list.front(), 0);
}

TEST(linked_list, ll_back)
{
    dsa::LinkedList list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(list.back(), 13);
}

TEST(linked_list, ll_back_const)
{
    const dsa::LinkedList list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    EXPECT_EQ(list.back(), 13);
}

TEST(linked_list, iterator_begin)
{
    dsa::LinkedList list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    auto it = list.begin();
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(*++it, 1);
}

TEST(linked_list, iterator_begin_equal)
{
    dsa::LinkedList list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    auto it = list.begin();
    auto it2 = list.begin();
    EXPECT_EQ(it, it2);
}

TEST(linked_list, iterator_end)
{
    dsa::LinkedList list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    auto it = list.end();
    EXPECT_EQ(it, dsa::LinkedList<int>::Iterator(nullptr));
}

TEST(linked_list, iterator_begin_const)
{
    const dsa::LinkedList list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    auto it = list.begin();
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(*++it, 1);
}

TEST(linked_list, iterator_end_const)
{
    const dsa::LinkedList list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    auto it = list.end();
    EXPECT_EQ(it, dsa::LinkedList<int>::ConstIterator(nullptr));
}

TEST(linked_list, iterator_cbegin_const)
{
    dsa::LinkedList list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    auto it = list.cbegin();
    EXPECT_EQ(*it, 0);
    EXPECT_EQ(*++it, 1);
}

TEST(linked_list, iterator_cend_const)
{
    dsa::LinkedList list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    auto it = list.cend();
    EXPECT_EQ(it, dsa::LinkedList<int>::ConstIterator(nullptr));
}

TEST(linked_list, ll_equal_operator_diff_size)
{
    dsa::LinkedList<int> list = {1, 2, 3};
    dsa::LinkedList<int> expected_list = {1, 2};
    EXPECT_NE(list, expected_list);
}

TEST(linked_list, ll_equal_operator_diff_elems)
{
    dsa::LinkedList<int> list = {1, 2, 3};
    dsa::LinkedList<int> expected_list = {1, 2, 4};
    EXPECT_NE(list, expected_list);
}

TEST(linked_list, ll_stream_operator)
{
    dsa::LinkedList<int> list = {1, 2, 3};
    std::ostringstream oss;
    oss << list;
    EXPECT_EQ(oss.str(), "[1, 2, 3]");
}

TEST(linked_list, ll_stream_insertion_empty)
{
    dsa::LinkedList<int> list;
    std::ostringstream oss;
    oss << list;
    EXPECT_EQ(oss.str(), "[]");
}
