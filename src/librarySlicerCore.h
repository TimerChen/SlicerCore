#ifndef SLICERCORE_LIBRARY_H
#define SLICERCORE_LIBRARY_H

#include <algorithm>

extern "C"
void* slicer_connect(int64_t id, void* data, uint width, uint height);
//bool test();
#endif