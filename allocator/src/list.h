#pragma once
#include <memory>

template <class T>
struct Node
{
    T data;
    Node* next;
};

template <typename T, typename Allocator>
class MyList
{
public:
    using pointer = Node<T>*;
    using allocator_type = Allocator;
    using allocator_traits = std::allocator_traits<allocator_type>;

    MyList() 
        : m_last{nullptr}
        , m_first{nullptr}
        , m_size{0}
    {}

    void push_back(const T &val) 
    {
        pointer node(m_allocTrait.allocate(m_alloc, 1));
        m_allocTrait.construct(m_alloc, node, val);

        if (m_last == nullptr) {
            m_last = node;
            m_first = node;
        } 
        else
        {
            m_last->next = node;
            m_last = node;
        }

        ++m_size;
    }

    size_t size() const { return m_size; }

    class Iterator
    {
    public:
        Iterator(pointer data) : m_data{data} {}

        Iterator &operator++()
        {
            m_data = m_data->next;
            return *this;
        }

        T &operator*() { return m_data->val; }

        bool operator==(const Iterator &b) { return m_data == b.m_data; }

        bool operator!=(const Iterator &b) { return m_data != b.m_data; }

    private:
        pointer data;
    };

    Iterator begin() { return Iterator(m_first); }
    Iterator end() { return Iterator(m_last->next); }

private:
    pointer m_last;
    pointer m_first;
    size_t m_size;
    allocator_type m_alloc;
    allocator_traits m_allocTrait;
};