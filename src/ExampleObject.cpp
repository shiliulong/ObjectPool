#include "ExampleObject.h"


ExampleObject::ExampleObject(int value) : value(value)
{
    std::cout << "ExampleObject constructed with value: " << value << std::endl;
}

ExampleObject::~ExampleObject()
{
    std::cout << "ExampleObject destructed with value: " << value << std::endl;
}


void ExampleObject::doSomething() const
{
    std::cout << "ExampleObject with value " << value << " is doing something." << std::endl;
}