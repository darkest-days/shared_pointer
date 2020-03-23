template <typename T>
class ControlBlock
{
public:
    T *object;
    unsigned int sp_count;

    //TODO: Add custom allocator functionality
    // std::function<void()> allocator;
    std::function<void(T*)> deleter = [](T *pointer) { delete pointer; };

    ControlBlock<T>()
    {
        object = nullptr;
        sp_count = 0;
        // allocator = [](T *pointer) { pointer = new T(); };
    }

    ControlBlock(T *&obj_pointer)
    {
        object = obj_pointer;
        sp_count = 1;
    }

    template <class D>
    ControlBlock(T *&obj_pointer, D _deleter)    
    {
        object = obj_pointer;        
        deleter = _deleter;
        sp_count = 1;
    }

    ~ControlBlock()
    {
        if (object != nullptr)
        {            
            deleter(object);
            object = nullptr;
           
        }
    }
};