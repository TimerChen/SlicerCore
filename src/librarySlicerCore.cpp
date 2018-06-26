#include "librarySlicerCore.h"
#include "configManager.h"
#include "SlicerCore.h"

#include <iostream>

extern "C"
void* slicer_connect(int64_t id, void* data, uint width, uint height)
{
    //std::cout << id;
    if(id == 0)
    {
        //init
	    SlicerCore::initFolder();
	    return NULL;
    }else
    {
        return SlicerCore::update(id, data, width, height);
    }
}

bool test()
{
	SlicerCore::test();
}