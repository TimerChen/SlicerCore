//
// Created by timemachine on 18-6-25.
//

#ifndef SLICER_CONFIGMANAGER_H
#define SLICER_CONFIGMANAGER_H

#include "slicerUtils.h"
#include "filter.h"

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <vector>
#include <map>

#include <iostream>
#include <fstream>
#include <set>

/*
 * config files: ~/.slicer/<id>
 *
 * ======================
 * format of config files
 * ======================
 *
 *      @uint n:number of filters
 *
 *      [filters]*n
 *
 * [one filter]:
 *
 *      @int8_t type: 0-flip 1-slice 2-color 3-auto
 *
 *      [when type=0]
 *
 *          @bool isLR: is Left-Right flip or not
 *
 *      [when type=1]
 *
 *          @u_int32_t nn: number of points of the polygon
 *
 *          [points]*nn
 *
 *          [one point]:
 *
 *              @double x
 *              @double y
 *
 *      [when type=2]
 *
 *          @u_int8_t r     : Red(0~255)
 *          @u_int8_t g     : Green(0~255)
 *          @u_int8_t b     : Blue(0~255)
 *          @u_int8_t alpha : Opacity(0~255)
 *
 *      [when type=3]
 *
 *          (nothing...)
 *
 */

class ConfigManager
{
public:
	//static std::map<int64_t, Config> configMap;
	static std::set<int64_t> idSet;// = std::set<int64_t >();

	static Config loadConfig(int64_t id);
	static void storeConfig(int64_t id, Config config);


	static Filter* loadFilter(std::ifstream &in);
	static void storeFilter(std::ofstream &out, Filter* filter);

	static void loadFilter(std::ifstream &in, FilterFlip* filter);
	static void loadFilter(std::ifstream &in, FilterSlicer* filter);
	static void loadFilter(std::ifstream &in, FilterColor* filter);

	static void storeFilter(std::ofstream &out, FilterFlip* filter);
	static void storeFilter(std::ofstream &out, FilterSlicer* filter);
	static void storeFilter(std::ofstream &out, FilterColor* filter);

	static void loadFilter(std::ifstream &in, FilterAuto* filter);
	static void storeFilter(std::ofstream &out, FilterAuto* filter);

	static bool test();




};


#endif //SLICER_CONFIGMANAGER_H
