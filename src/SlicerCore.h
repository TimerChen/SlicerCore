//
// Created by timemachine on 18-6-26.
//

#ifndef SLICER_CORE_H
#define SLICER_CORE_H

#include <algorithm>
#include "slicerUtils.h"

class SlicerCore
{
public:
	static void initFolder();

	static void* update(u_int64_t id, void *data, uint width, uint height);

	static bool test();

private:
	static Config updateFromFile(uint id);
};


#endif //SLICER_CORE_H
