//
// Created by timemachine on 18-6-26.
//

#ifndef SLICER_FILTERRENDER_H
#define SLICER_FILTERRENDER_H


#include <algorithm>
#include <vector>

#include "slicerUtils.h"

struct Config;

class FilterRender {
public:
	static void* render(void *data, uint width, uint height, Config* config);

private:
	static void* doFlip(void *data, uint width, uint height, bool isLR);
	static void* doSlice(void *data, uint width, uint height, std::vector<Geometry::Point>);
	static void* doColor(void *data, uint width, uint height, u_int8_t r, u_int8_t g, u_int8_t b ,u_int8_t a);
	static void* doAuto(void *data, uint width, uint height);
};


#endif //SLICER_FILTERRENDER_H
