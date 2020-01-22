#include <iostream>
#include <assert.h>
#include "shared_pointer.h"

struct S
{
    int *arr;
    S() : arr(new int(0)){ std::cout << "default S ctor \n"; }
    S(S &copy) { std::cout << "default S copy ctor \n"; }
    S(const S &copy) { std::cout << "default S const copy ctor \n"; }
    S(S &&move) { std::cout << "default S move ctor \n"; }
    ~S()
    {
        delete arr;
        arr = nullptr;
        std::cout << "default S dtor \n";
    }
};

auto main() -> int
{
    shared_pointer<S> sp_1 = make_shared<S>();
    assert(sp_1.use_count() == 1);

    shared_pointer<S> sp_2 = sp_1;
    assert(sp_1.use_count() == 2);

    return 0;
}