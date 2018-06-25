//
// Created by timemachine on 18-6-25.
//

#include <algorithm>

#include "filter.h"

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
	std::stringstream ss;
	ss << "~/.slicer/" + id;
	std::string str;
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
	ss << "~/.slicer/" + id;
	std::string str;
	ss >> str;

	//first load?
	if(idSet.find(id) == idSet.end())
	{
		idSet.insert(id);
		std::ofstream ffout(str, std::iostream::binary);
		uint val = 0;
		ffout.write((char*)&val, sizeof(val));
	}


	std::ifstream fin(str, std::iostream::binary);
	Config config;
	fin.read((char*)&config.nFilters, sizeof(config.nFilters));
	config.filters = new Filter*[config.nFilters];
	for(int i=0;i<config.nFilters;++i)
	{
		ConfigManager::loadFilter(fin, config.filters[i]);
	}
	fin.close();
	return config;
}

void ConfigManager::loadFilter(std::ifstream &in, Filter *filter) {
	u_int8_t type;
	in.read((char*)&type, sizeof(type));
	switch (type)
	{
		case 0: //flip
			ConfigManager::loadFilter(in, (FilterFlip*)filter);
			break;
		case 1: //slicer
			ConfigManager::loadFilter(in, (FilterSlicer*)filter);
			break;
		case 2: //color
			ConfigManager::loadFilter(in, (FilterColor*)filter);
			break;
	}
}

void ConfigManager::loadFilter(std::ifstream &in, FilterFlip *filter) {
	in.read((char*)&filter->isLR, sizeof(filter->isLR));
}

void ConfigManager::loadFilter(std::ifstream &in, FilterSlicer *filter) {
	uint32_t n;
	in.read((char*)&n, sizeof(n));
	filter->poly = std::vector<Point>(n);
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
