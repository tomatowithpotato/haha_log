#ifndef __HAHA_LOGUTIL_H__
#define __HAHA_LOGUTIL_H__

#include <string>
#include <string.h>
#include "base/noncopyable.h"
#include "base/ConditionVariable.h"

namespace haha{

const int kSmallBuffer = 4000;
const int kLargeBuffer = 4000*1000;

template<int SIZE>
class FixedBuffer : noncopyable
{
public:
    FixedBuffer()
        : cur_(data_)
    {
    }

    void append(const char* /*restrict*/ buf, size_t len)
    {
        // FIXME: append partially
        if (static_cast<size_t>(avail()) > len)
        {
            memcpy(cur_, buf, len);
            cur_ += len;
        }
    }

    const char* data() const { return data_; }
    int length() const { return static_cast<int>(cur_ - data_); }

    // write to data_ directly
    char* current() { return cur_; }
    int avail() const { return static_cast<int>(end() - cur_); }
    void add(size_t len) { cur_ += len; }

    void reset() { cur_ = data_; }
    void bzero() { ::bzero(data_, sizeof(data_)); }

    // for used by unit test
    std::string toString() const { return string(data_, length()); }
    std::string_view toStringView() const { return std::string_view(data_, length()); }

private:
    const char* end() const { return data_ + sizeof(data_); }

    void (*cookie_)();
    char data_[SIZE];
    char* cur_;
};

}

#endif