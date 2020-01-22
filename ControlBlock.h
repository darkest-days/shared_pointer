template <typename T>
class ControlBlock
{
public:
    T *object;
    unsigned int sp_count;

    //TODO: Add custom deleter/allocator functionality
    // std::function<void()> allocator;
    // std::function<void()> deleter;

    ControlBlock<T>()
    {
        object = nullptr;
        sp_count = 0;
        // allocator = [](T *pointer) { pointer = new T(); };
        // deleter = [](T *pointer) { delete pointer; };
    }

    ControlBlock(T *&obj_pointer)
    {
        object = obj_pointer;
        sp_count = 1;
    }

    ~ControlBlock()
    {
        if (object != nullptr)
        {
            delete object;
            object = nullptr;
           
        }
    }
};