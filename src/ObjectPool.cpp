#include "ObjectPool.h"

template <typename T>
ObjectPool<T>::ObjectPool(size_t size) : poolSize(size)
{
    poolMemory = new char[sizeof(T)* poolSize];
    for(size_t i=0; i<poolSize; ++i)
    {
        pool.push_back({reinterpret_cast<T*>(poolMemory + i*sizeof(T)), false}); //计算出第 i 个对象在内存中的起始地址
    }
}

template <typename T>
ObjectPool<T>::~ObjectPool()
{
    for(auto& entry : pool)
    {
        if(entry.inUse)
        {
            entry.object -> ~T();
        }
    }
    delete[] poolMemory;
}


template <typename T>
template <typename... Args>
T* ObjectPool<T>::acquireObject(Args&&... args)
{
    for(auto& entry : pool)
    {
        if(!entry.inUse)
        {
            entry.inUse = true;
            return new (entry.object) T(std::forward<Args>(args)...); //placement new，forward使用了完美转发，地址，类型，参数
        }
    }
    throw std::runtime_error("No available objects in pool");
}

template <typename T>
void ObjectPool<T>::releaseObject(T* object)
{
    for(auto& entry : pool)
    {
        if(entry.object == object)
        {
            if(entry.inUse)
            {
                object -> ~T();
                entry.inUse = false;
                return;
            }
            else
            {
                throw std::runtime_error("Object already released");
            }
        }
    }
    throw std::runtime_error("Object not from pool");
}