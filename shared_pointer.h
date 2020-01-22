#include <functional>
#include "ControlBlock.h"

template <typename T>
class shared_pointer
{
private:
    ControlBlock<T> *cb = nullptr;

public:
    shared_pointer()
    {
        cb = new ControlBlock<T>();
    }

    shared_pointer(T *&pointer)
    {
        cb = new ControlBlock<T>(pointer);
    }

    shared_pointer(shared_pointer &sp)
    {
        cb = sp.cb;
        cb->sp_count++;
    }

    shared_pointer(const shared_pointer &sp)
    {
        cb = sp.cb;
        cb->sp_count++;
    }

    shared_pointer(shared_pointer &&sp)
    {
        cb = std::move(sp.cb);
        sp.cb = nullptr;
    }

    shared_pointer<T> &operator=(shared_pointer &sp)
    {
        if (this != &sp)
        {
            delete cb;
            cb = sp.cb;
            cb->sp_count++;
        }

        return *this;
    }

    shared_pointer<T> &operator=(const shared_pointer &sp)
    {
        if (this != &sp)
        {
            delete cb;
            cb = sp.cb;
            cb->sp_count++;
        }

        return *this;
    }

    shared_pointer<T> &operator=(shared_pointer &&sp)
    {
        if (this != &sp)
        {
            delete cb;
            cb = std::move(sp.cb);
            sp.cb = nullptr;
        }

        return *this;
    }

    T *get() const
    {
        if (cb != nullptr)
        {
            return cb->object;
        }
        else
        {
            return nullptr;
        }
    }

    T &operator*() const
    {
        return *(get());
    }

    T *operator->() const
    {
        return get();
    }

    unsigned int use_count() const
    {
        if (cb != nullptr)
        {
            return cb->sp_count;
        }
        else
        {
            return 0;
        }
    }

    ~shared_pointer<T>()
    {

        if (cb != nullptr)
        {
            if (use_count() <= 1)
            {
                delete cb;
                cb = nullptr;
            }
            else
            {
                cb->sp_count--;
            }
        }
    }
};

template <typename T, typename... Args>
static shared_pointer<T> make_shared(Args &&... args)
{
    T *pointer = new T(args...);
    return shared_pointer<T>(pointer);
}