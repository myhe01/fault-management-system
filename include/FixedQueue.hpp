/**
 * File:    FixedQueue.hpp
 * Purpose: Fixed queue header-only class declarations and definitions.
 * Creator: Brendan College
 */

#ifndef FMS_INCLUDE_FIXEDQUEUE_
#define FMS_INCLUDE_FIXEDQUEUE_

#include <queue>
#include <deque>
#include <iostream>

namespace fms {

template <typename T, std::size_t N>
class FixedQueue
{
public:
    bool push(const T& val)
    {
        if (full())
        {
            return false;
        }

        data_[tail_] = val;
        tail_        = (tail_ + 1) % N;
        size_++;
        return true;
    }

    bool pop(T& out)
    {
        if (empty())
        {
            return false;
        }

        out = data_[head_];
        head_ = (head_ + 1) % N;
        size_--;
        return true;
    }

    bool peek(T& out) const
    {
        if (empty())
        {
            return false;
        }
        out = data_[head_];
        return true;
    }

    bool empty() const
    {
        return (size_ == 0);
    }

    bool full() const
    {
        return (size_ == N);
    }

    std::size_t size() const
    {
        return size_;
    }

    constexpr std::size_t capacity() const
    {
        return N;
    }

private:
    std::array<T, N> data_{};
    std::size_t head_ = 0;
    std::size_t tail_ = 0;
    std::size_t size_ = 0;
};

} // namespace fms

#endif // FMS_INCLUDE_FIXEDQUEUE_