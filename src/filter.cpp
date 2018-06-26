//
// Created by timemachine on 18-6-26.
//

#include "filter.h"

int8_t Filter::type() {
	return -1;
}

int8_t FilterFlip::type() {
	return 0;
}

int8_t FilterSlicer::type() {
	return 1;
}

int8_t FilterColor::type() {
	return 2;
}

int8_t FilterAuto::type() {
	return 3;
}