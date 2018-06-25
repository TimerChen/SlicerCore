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
	static void* doSlice(void *data, uint width, uint height, std::vector<Point>);
	static void* doColor(void *data, uint width, uint height, double r, double g, double b ,double a);
};


#endif //SLICER_FILTERRENDER_H
