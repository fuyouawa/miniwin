#pragma once

namespace fugui {
class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

class NonMoveable {
public:
    NonMoveable() = default;
    NonMoveable(NonMoveable&&) = delete;
    NonMoveable& operator=(NonMoveable&&) = delete;
};

class NonCopyMoveable: public NonCopyable, public NonMoveable
{
public:
    NonCopyMoveable() = default;
};

template<class T>
class Singleton : public NonCopyMoveable
{
public:
    static T& instance()
    {
        static T inst;
        return inst;
    }

    virtual ~Singleton() = default;

protected:
    Singleton() = default;
};
}