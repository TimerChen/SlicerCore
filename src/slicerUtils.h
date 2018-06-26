//
// Created by timemachine on 18-6-25.
//

#ifndef SLICER_SLICERUTILS_H
#define SLICER_SLICERUTILS_H


#include <algorithm>

#include "Point.h"



class Filter;

struct Config
{
	uint nFilters;
	Filter **filters;
};

#endif //SLICER_SLICERUTILS_H
