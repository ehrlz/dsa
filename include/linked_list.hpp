#pragma once

#include <cstddef>
#include <memory>

namespace dsa
{

/**
 * A singly linked list.
 *
 * @tparam T The type of the element stored.
 */
template <typename T>
class LinkedList
{
  public:
    /**
     * Constructs an empty list.
     */
    LinkedList()
        : head_(nullptr)
    {
    }

    // TODO move semantics

    /**
     * Constructs a list from an initializer list.
     *
     * @param init Elements to insert, in order.
     */
    LinkedList(std::initializer_list<T> init)
        : head_(nullptr)
    {
        if (init.size() != 0) {
            head_ = std::make_unique<Node>(*init.begin(), nullptr);
            Node* node = head_.get();
            for (std::size_t i = 1; i < init.size(); ++i) {
                node->next = std::make_unique<Node>(init.begin()[i], nullptr);
                node = node->next.get();
            }
        }
    }

    /**
     * Appends an element at the end of the list.
     *
     * @param elem Element to append.
     *
     */
    void append(T elem)
    {
        Node* last_node = get_last_node();
        if (!last_node) {
            head_ = std::make_unique<Node>(elem, nullptr);
        } else {
            last_node->next = std::make_unique<Node>(elem, nullptr);
        }
    }

    // TODO append first

    // TODO remove

    /**
     * Counts how many elements are in the list.
     *
     * @return The number of elements.
     */
    std::size_t size()
    {
        std::size_t size = 0;

        if (!head_) {
            return size;
        }

        ++size;
        Node* node = head_->next.get();
        while (node) {
            ++size;
            node = node->next.get();
        }

        return size;
    }

    /**
     * Returns if the list has no elements.
     *
     * @return true if the list has no elements.
     */
    bool empty()
    {
        return size() == 0;
    }

    /**
     * Returns the first element.
     *
     * @return The element.
     *
     * @warning If empty() is true, the behavior is undefined.
     *          As std::forward_list::front().
     */
    T& front()
    {
        return head_->data;
    }

    /**
     * Returns the last element.
     * @return The element.
     *
     * @warning If empty() is true, the behavior is undefined.
     *          As std::forward_list::back().
     */
    T& back()
    {
        return get_last_node()->data;
    }

  private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
    };

    Node* get_last_node()
    {
        Node* curr_node = head_.get();
        if (!curr_node) {
            return curr_node;
        }

        while (curr_node->next) {
            curr_node = curr_node->next.get();
        }
        return curr_node;
    }

    std::unique_ptr<Node> head_;
};

} // namespace dsa
