#include "library.h"

#include <iostream>

void hello() {
    std::cout << "Hello, World!" << std::endl;
}

void slicer_connect(long long id, char* data, unsigned int width, unsigned int length)
{
    std::cout << "slicer_connect ok.";
}