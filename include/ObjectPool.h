#pragma once

#include <vector>
#include <memory>
#include <new>
#include <stdexcept>

template <typename T>
class ObjectPool
{
public:
    ObjectPool(size_t size);
    ~ObjectPool();

    template <typename... Args>
    T* acquireObject(Args&&... args);

    void releaseObject(T* object);

private:
    struct PoolEntry
    {
        T* object;
        bool inUse;
    };

    std::vector<PoolEntry> pool;
    size_t poolSize;
    char* poolMemory;
};
