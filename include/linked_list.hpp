#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <stdexcept>

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
        : head_(nullptr), size_(0)
    {
    }

    /**
     * Construct a list copying the content of another LinkedList.
     *
     * @param other LinkedList to copy.
     *
     * @note O(n) cost. Copies each element of other list.
     */
    LinkedList(const LinkedList& other)
        : head_(nullptr), size_(0)
    {
        if (!other.head_) {
            return;
        }

        head_ = std::make_unique<Node>(other.head_->data, nullptr);
        Node* dst = head_.get();
        Node* src = other.head_->next.get();
        while (src) {
            dst->next = std::make_unique<Node>(src->data, nullptr);
            dst = dst->next.get();
            src = src->next.get();
        }
        size_ = other.size_;
    }

    /**
     * Construcs a list by copying the content of the asigned LinkedList.
     *
     * @param other LinkedList asigned to copy.
     *
     * @note O(n) cost. Copies each element of other list.
     */
    LinkedList& operator=(const LinkedList& other)
    {
        LinkedList tmp(other);
        std::swap(head_, tmp.head_);
        size_ = other.size_;
        return *this;
    }

    /**
     * Constructs a list by taking ownership of another list's elements.
     *
     * @param other List to move from. Left in an invalid state.
     *
     * @note O(1) cost. No copy, only pointers are managed.
     */
    LinkedList(LinkedList&& other) noexcept
        : head_(std::move(other.head_)), size_(other.size_)
    {
        other.size_ = 0;
    }

    /**
     * Constructs a list by taking ownership of the asigned list's elements.
     *
     * @param other List to move from. Left in an invalid state.
     *
     * @note O(1) cost. No copy, only pointers are managed.
     */
    LinkedList& operator=(LinkedList&& other) noexcept
    {
        // comparing adresses
        if (this != &other) {
            head_ = std::move(other.head_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }

    /**
     * Constructs a list from an initializer list.
     *
     * @param init Elements to insert, in order.
     */
    LinkedList(std::initializer_list<T> init)
        : head_(nullptr), size_(0)
    {
        if (init.size() != 0) {
            head_ = std::make_unique<Node>(*init.begin(), nullptr);
            Node* node = head_.get();
            for (std::size_t i = 1; i < init.size(); ++i) {
                node->next = std::make_unique<Node>(init.begin()[i], nullptr);
                node = node->next.get();
            }
            size_ = init.size();
        }
    }

    /**
     * Appends an element at the end of the list.
     *
     * @param elem Element to append.
     */
    void append_last(T elem)
    {
        Node* last_node = get_node(size() - 1);
        if (!last_node) {
            head_ = std::make_unique<Node>(elem, nullptr);
        } else {
            last_node->next = std::make_unique<Node>(elem, nullptr);
        }
        ++size_;
    }

    /**
     * Appends an element at the beginning of the list.
     *
     * @param elem Element to append.
     */
    void append_first(T elem)
    {
        std::unique_ptr<Node> new_n;
        if (empty()) {
            new_n = std::make_unique<Node>(elem, nullptr);
        } else {
            new_n = std::make_unique<Node>(elem, std::move(head_));
        }
        head_ = std::move(new_n);
        ++size_;
    }

    /**
     * Appends an element at a defined position.
     *
     * @param index Position to include the element.
     *              Displaces every other element after it one position.
     * @param elem Element to append.
     *
     * @throws std::out_of_range Throwed if index is negative or bigger
     *                           than the last position.
     */
    void append(std::size_t index, T elem)
    {
        if (empty() || index > size() - 1) {
            throw std::out_of_range("Element to append out of bounds");
        }
        Node* node = get_node(index - 1);
        auto new_node = std::make_unique<Node>(elem, std::move(node->next));
        node->next = std::move(new_node);
        ++size_;
    }

    /**
     * Removes all the elements.
     */
    void clear()
    {
        head_ = nullptr;
        size_ = 0;
    }

    /**
     * Removes the element in a position.
     *
     * @param index Position of the element to remove.
     *
     * @throws std::out_of_range Throwed if the list is empty or index
     *                           is bigger than the last position.
     */
    void remove(std::size_t index)
    {
        if (empty() || index > size() - 1) {
            throw std::out_of_range("Element to remove out of bounds");
        }

        if (index == 0) {
            pop();
        } else {
            Node* prev_node = get_node(index - 1);
            Node* node_to_delete = get_node(index);
            prev_node->next = std::move(node_to_delete->next);
            node_to_delete = nullptr;
            --size_;
        }
    }

    /**
     * Removes the first element.
     *
     * @throws std::out_of_range Throwed if the list is empty.
     */
    void pop()
    {
        if (empty()) {
            throw std::out_of_range("Element to remove out of bounds");
        }
        head_ = std::move(head_.get()->next);
        --size_;
    }

    /**
     * Adds an element building it at the end of the list.
     *
     * @param args Arguments of the element to build.
     */
    template <typename... Args>
    void emplace_last(Args&&... args)
    {
        Node* node = get_node(size() - 1);
        node->next = std::make_unique<Node>(std::forward<Args>(args)..., nullptr);
        ++size_;
    }

    /**
     * Adds an element building it at the beginning of the list.
     *
     * @param args Arguments of the element to build.
     */
    template <typename... Args>
    void emplace_first(Args&&... args)
    {
        head_ = std::make_unique<Node>(std::forward<Args>(args)..., std::move(head_));
        ++size_;
    }

    /**
     * Adds an element building it in a certain position.
     *
     * @param index Position where the element is included.
     * @param args Arguments of the element to build.
     *
     * @throws std::out_of_range Throwed if the list is empty or the index
     *                           is bigger than the last position.
     */
    template <typename... Args>
    void emplace(std::size_t index, Args&&... args)
    {
        if (empty() || index > size() - 1) {
            throw std::out_of_range("Element to empalce out of bounds");
        }

        Node* node = get_node(index - 1);
        node->next = std::make_unique<Node>(std::forward<Args>(args)..., std::move(node->next));
        ++size_;
    }

    /**
     * Access the element counter that is updated when an element is added
     * or removed.
     *
     * @return The number of elements.
     */
    [[nodiscard]] std::size_t size() const
    {
        return size_;
    }

    /**
     * Returns if the list has no elements.
     *
     * @return true if the list has no elements.
     */
    [[nodiscard]] bool empty() const
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
    [[nodiscard]] T& front() const
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
    [[nodiscard]] T& back() const
    {
        return get_node(size() - 1)->data;
    }

    /**
     * Compares two LinkedLists for equality.
     *
     * Two lists are equal if they contain the same number of elements and
     * each pair of corresponding elements, taken in order, compares equal
     * via T's operator==.
     *
     * @param lhs First LinkedList to compare.
     * @param rhs Second LinkedList to compare.
     * @return true if the lists are equal, false otherwise.
     *
     * @note friend declaration allows comparisons as {1,2,3}==list
     */
    [[nodiscard]] friend bool operator==(const LinkedList& lhs, const LinkedList& rhs)
    {
        if (lhs.size() != rhs.size()) {
            return false;
        }

        Node* l_node = lhs.head_.get();
        Node* r_node = rhs.head_.get();
        while (l_node) {
            if (l_node->data != r_node->data) {
                return false;
            }
            l_node = l_node->next.get();
            r_node = r_node->next.get();
        }
        return true;
    }

    /**
     * Writes the list's elements to a stream, space-separated.
     *
     * @param os Output stream.
     * @param list List to print.
     * @return The stream, for chaining.
     */
    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list)
    {
        os << "[";
        const Node* node = list.head_.get();
        bool first = true;
        while (node) {
            if (!first) {
                os << ", ";
            }
            os << node->data;
            first = false;
            node = node->next.get();
        }
        os << "]";
        return os;
    }

  private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
    };

    /**
     * Obtains the a node of the list.
     *
     * @param index The position to obtain.
     * @return The last node or nullptr is the list is empty.
     *
     * @note Doesn't validate the index argument.
     */
    Node* get_node(std::size_t index) const
    {
        if (empty()) {
            return nullptr;
        }

        Node* curr_node = head_.get();
        for (std::size_t i = 0; i < index; ++i) {
            curr_node = curr_node->next.get();
        }
        return curr_node;
    }

    std::unique_ptr<Node> head_;
    std::size_t size_;
};

} // namespace dsa
