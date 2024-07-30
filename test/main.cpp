#include <iostream>
#include "ObjectPool.h"
#include "ExampleObject.h"

int main()
{
    ObjectPool<ExampleObject> pool(5);

    ExampleObject* obj1 = pool.acquireObject(1);
    ExampleObject* obj2 = pool.acquireObject(2);

    obj1->doSomething();
    obj2->doSomething();

    pool.releaseObject(obj1);
    pool.releaseObject(obj2);

    try
    {
        pool.releaseObject(obj1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}