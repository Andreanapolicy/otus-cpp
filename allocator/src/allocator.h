#pragma once
#include <cstddef>
#include <memory>

template <typename M>
struct Chunk
{
    ~Chunk() { std::free(start); }
    
    M* start;
    size_t end;
};

template <int S, typename T>
class Alloc
{
public:
    using value_type = T;
    using size_type = size_t;

    template <typename U>
    struct rebind {
        using other = Alloc<S, U>;
    };

    Alloc()
        : m_data{nullptr, 0}
    {}

    ~Alloc() = default;

    template <typename U>
    Alloc(const Alloc<S, U>&) {}

    T *allocate(const size_type& elements)
    {
        if (m_data.start == nullptr)
        {
            m_data.start = reinterpret_cast<T*>(std::malloc(sizeof(T) * S));
            m_data.end = S;
        }
        else if (m_offset + elements < m_data.end)
        {
            m_offset += elements;
        }
        else
        {
            throw std::bad_alloc();
        }

        return &m_data.start[m_offset];
    }

    void deallocate(T *, size_type) {}
    
    size_type max_size() const
    {
        return S;
    }

private:
    Chunk<T> m_data;
    size_type m_offset = 0;
};

template <int S, class T, class U>
constexpr bool operator==(const Alloc<S, T> &, const Alloc<S, U> &) noexcept
{
  return false;
}

template <int S, class T, class U>
constexpr bool operator!=(const Alloc<S, T> &, const Alloc<S, U> &) noexcept
{
  return false;
}