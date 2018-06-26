//
// Created by timemachine on 18-6-25.
//

#include <algorithm>

#include "filter.h"
#include "slicerUtils.h"
#include "configManager.h"

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


std::set<int64_t> ConfigManager::idSet = std::set<int64_t >();

void ConfigManager::storeConfig(int64_t id, Config config) {
	idSet.insert(id);

	std::stringstream ss;
	ss << getenv("HOME") << "/.slicer/" << id;
	std::string str;
	ss >> str;
	std::ofstream fout(str, std::iostream::binary);
	fout.write((char*)&config.nFilters, sizeof(config.nFilters));
	for(int i=0;i<config.nFilters;++i)
	{
		ConfigManager::storeFilter(fout, config.filters[i]);
	}
	fout.close();
}

void ConfigManager::storeFilter(std::ofstream &out, Filter* filter) {
	int8_t type = filter->type();
	out.write((char*)&type, sizeof(type));
	switch (type)
	{
		case 0: //flip
			ConfigManager::storeFilter(out, (FilterFlip*)filter);
			break;
		case 1: //slicer
			ConfigManager::storeFilter(out, (FilterSlicer*)filter);
			break;
		case 2: //color
			ConfigManager::storeFilter(out, (FilterColor*)filter);
			break;
		case 3: //auto
			ConfigManager::storeFilter(out, (FilterAuto*)filter);
			break;
	}
}

void ConfigManager::storeFilter(std::ofstream &out, FilterFlip* filter) {
	out.write((char*)&filter->isLR, sizeof(filter->isLR));
}

void ConfigManager::storeFilter(std::ofstream &out, FilterSlicer* filter) {
	uint32_t n = filter->poly.size();
	out.write((char*)&n, sizeof(n));
	for(int i=0;i<n;++i)
	{
		double x,y;
		x = filter->poly[i].x;
		y = filter->poly[i].y;
		out.write((char*)&x, sizeof(x));
		out.write((char*)&y, sizeof(y));
	}
}

void ConfigManager::storeFilter(std::ofstream &out, FilterColor* filter) {
	out.write((char*)&filter->r, sizeof(filter->r));
	out.write((char*)&filter->g, sizeof(filter->g));
	out.write((char*)&filter->b, sizeof(filter->b));
	out.write((char*)&filter->a, sizeof(filter->a));

}


Config ConfigManager::loadConfig(int64_t id) {
	std::stringstream ss;
	ss << getenv("HOME") << "/.slicer/" << id;
	std::string str;
	ss >> str;

	//std::cerr << str << std::endl;

	Config config;

	//first load?
	if(idSet.find(id) == idSet.end())
	{
		idSet.insert(id);
		std::ofstream ffout(str, std::iostream::binary);
		uint val = 0;
		ffout.write((char*)&val, sizeof(val));
		ffout.close();
	}


	std::ifstream fin(str, std::iostream::binary);

	fin.read((char*)&config.nFilters, sizeof(config.nFilters));
	config.filters = new Filter*[config.nFilters];
	for(int i=0;i<config.nFilters;++i)
	{
		config.filters[i] = ConfigManager::loadFilter(fin);
	}
	fin.close();
	return config;
}

Filter* ConfigManager::loadFilter(std::ifstream &in) {
	u_int8_t type;
	in.read((char*)&type, sizeof(type));
	Filter* ret;
	switch (type)
	{
		case 0: //flip
		{
			FilterFlip* filter = new FilterFlip();
			ConfigManager::loadFilter(in, filter);
			ret = filter;
			break;
		}
		case 1: //slicer
		{
			FilterSlicer* filter = new FilterSlicer();
			ConfigManager::loadFilter(in, filter);
			ret = filter;
			break;
		}
		case 2: //color
		{
			FilterColor* filter = new FilterColor();
			ConfigManager::loadFilter(in, filter);
			ret = filter;
			break;
		}

		case 3:
			FilterAuto* filter = new FilterAuto;
			ConfigManager::loadFilter(in, filter);
			ret = filter;
			break;
	}
	return ret;
}

void ConfigManager::loadFilter(std::ifstream &in, FilterFlip *filter) {
	in.read((char*)&filter->isLR, sizeof(filter->isLR));
}

void ConfigManager::loadFilter(std::ifstream &in, FilterSlicer *filter) {
	uint32_t n;
	in.read((char*)&n, sizeof(n));
	filter->poly = std::vector<Geometry::Point>(n);
	for(int i=0;i<n;++i)
	{
		double x,y;
		in.read((char*)&x, sizeof(x));
		in.read((char*)&y, sizeof(y));
		filter->poly[i].x = x;
		filter->poly[i].y = y;
	}
}

void ConfigManager::loadFilter(std::ifstream &in, FilterColor *filter) {
	in.read((char*)&filter->r, sizeof(filter->r));
	in.read((char*)&filter->g, sizeof(filter->g));
	in.read((char*)&filter->b, sizeof(filter->b));
	in.read((char*)&filter->a, sizeof(filter->a));
}


void ConfigManager::loadFilter(std::ifstream &in, FilterAuto* filter)
{

}
void ConfigManager::storeFilter(std::ofstream &out, FilterAuto* filter)
{

}

bool ConfigManager::test()
{
	int n = 4;
	Config config, config1;
	config.nFilters = n;
	FilterSlicer *fslicer = new FilterSlicer();
	FilterFlip *fflip = new FilterFlip();
	FilterAuto *fauto = new FilterAuto();
	FilterColor *fcolor = new FilterColor();

	std::vector<Geometry::Point> poly;
	int size_poly = 3;
	poly = std::vector<Geometry::Point>(size_poly);
	for(int i=0;i<size_poly;++i)
	{
		poly[i].x = 1.*rand()/rand();
		poly[i].y = 1.*rand()/rand();
	}

	fslicer->poly = poly;
	fflip->isLR = true;
	fcolor->r = 4;
	fcolor->g = 2;
	fcolor->b = 0;
	fcolor->a = 233;

	config.filters = new Filter*[n];
	config.filters[0] = fslicer;
	config.filters[1] = fflip;
	config.filters[2] = fcolor;
	config.filters[3] = fauto;

	long long id = (long long)new int();

	storeConfig(0,config);
	config1 = loadConfig(0);
	storeConfig(1,config1);


}