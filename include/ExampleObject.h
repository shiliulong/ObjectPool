#pragma once

#include <iostream>

class ExampleObject
{
public:
    ExampleObject(int value);
    ~ExampleObject();

    void doSomething() const;

private:
    int value;
};