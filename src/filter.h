//
// Created by timemachine on 18-6-25.
//

#ifndef SLICER_FILTER_H
#define SLICER_FILTER_H

#include <vector>

#include "slicerUtils.h"

char *filterIt(char* data, unsigned int width, unsigned int height, std::vector<Geometry::Point> poly);

class Filter
{
private:

public:
	//const static int8_t type = -1;
	virtual int8_t type();
};

class FilterFlip : public Filter
{
public:
	//const static int8_t type = 0;
	virtual int8_t type();
	bool isLR;
};

class FilterSlicer : public Filter
{
public:
	//const static int8_t type = 1;
	virtual int8_t type();
	std::vector<Geometry::Point> poly;
};

class FilterColor : public Filter
{
public:
	//const static int8_t type = 2;
	virtual int8_t type();
	u_int8_t r,g,b,a;
};

class FilterAuto : public Filter
{
public:
	virtual int8_t type();
};

#endif //SLICER_FILTER_H
