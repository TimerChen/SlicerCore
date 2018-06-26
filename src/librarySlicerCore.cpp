#include "librarySlicerCore.h"
#include "configManager.h"
#include "SlicerCore.h"

#include <iostream>

void* slicer_connect(int64_t id, void* data, uint width, uint height)
{
    //std::cout << id;
    if(id == -1)
    {
        //init
	    SlicerCore::initFolder();
	    return NULL;
    }else
    {
        return SlicerCore::update(id, data, width, height);
    }
}