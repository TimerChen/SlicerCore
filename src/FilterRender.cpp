//
// Created by timemachine on 18-6-26.
//

#include "FilterRender.h"
#include "filter.h"
#include "Point.h"
#include "Geometry.h"

#include <algorithm>
#include <iostream>

#include <time.h>

using namespace Geometry;

const int threshold = 30;

void* FilterRender::render(void *data, uint width, uint height, Config *config) {

	//data = FilterRender::doColor(data, width, height, time(0)%255, time(0)*2%255, time(0)*3%255, 255);

	if(config == NULL) return data;
	int n = config->nFilters;

	for(int i=0;i<n;++i)
	{
		switch (config->filters[i]->type())
		{
			case 0:
			{
				FilterFlip *f = (FilterFlip*)config->filters[i];
				data = FilterRender::doFlip(data, width, height, f->isLR);
				break;
			}
			case 1:
			{
				FilterSlicer *f = (FilterSlicer*)config->filters[i];
				data = FilterRender::doSlice(data, width, height, f->poly);
				break;
			}
			case 2:
			{
				FilterColor *f = (FilterColor*)config->filters[i];
				data = FilterRender::doColor(data, width, height, f->r, f->g, f->b, f->a);
				break;
			}
			case 3:
			{
				FilterAuto *f = (FilterAuto*)config->filters[i];
				data = FilterRender::doAuto(data, width, height);
				break;
			}

		}

	}
	return data;
}

void swap(unsigned char &a, unsigned char &b) {
	unsigned char t = a;
	a = b;
	b = t;
}

bool equal(unsigned char a[4], unsigned char b[4]) {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += abs(a[i] - b[i]);
	}
	return sum <= threshold;
}

void* FilterRender::doFlip(void *data, uint width, uint height, bool isLR) {
	unsigned char ***map;

	map = new unsigned char**[height];
	for (int i = 0; i < height; i++) {
		map[i] = new unsigned char*[width];
		for (int j = 0; j < width; j++) {
			map[i][j] = new unsigned char[4];
		}
	}

	unsigned char * p = (unsigned char*)data;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < 4; k++) {
				map[i][j][k] = *(p + k);
				// b g r a
			}
			p += 4;
		}
	}

	if (isLR) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width / 2; j++) {
				for (int k = 0; k < 4; k++) {
					swap(map[i][j][k], map[i][width - j][k]);
				}
			}
		}
	} else {
		for (int i = 0; i < height / 2; i++) {
			for (int j = 0; j < width; j++) {
				for (int k = 0; k < 4; k++) {
					swap(map[i][j][k], map[height - i][j][k]);
				}
			}
		}
	}

	p = (unsigned char*)data;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < 4; k++) {
				*(p + k) = map[i][j][k];
			}
			p += 4;
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete [] map[i][j];
		}
		delete [] map[i];
	}
	delete [] map;
	map = NULL;
}

void* FilterRender::doSlice(void *data, uint width, uint height, std::vector<Point> poly) {
	unsigned char ***map;

	map = new unsigned char**[height];
	for (int i = 0; i < height; i++) {
		map[i] = new unsigned char*[width];
		for (int j = 0; j < width; j++) {
			map[i][j] = new unsigned char[4];
		}
	}

	unsigned char * p = (unsigned char*)data;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < 4; k++) {
				map[i][j][k] = *(p + k);
				// b g r a
			}
			p += 4;
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (!InPoly(Point(i, j), poly)) {
				for (int k = 0; k < 4; k++) {
					map[i][j][k] = 0;
				}
			}
		}
	}

	p = (unsigned char*)data;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < 4; k++) {
				*(p + k) = map[i][j][k];
			}
			p += 4;
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete [] map[i][j];
		}
		delete [] map[i];
	}
	delete [] map;
	map = NULL;
}

void* FilterRender::doColor(void *data, uint width, uint height, u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a) {
	//std::cerr << "fuckyou" << std::endl;
	unsigned char ***map;

	map = new unsigned char**[height];
	for (int i = 0; i < height; i++) {
		map[i] = new unsigned char*[width];
		for (int j = 0; j < width; j++) {
			map[i][j] = new unsigned char[4];
		}
	}

	unsigned char * p = (unsigned char*)data;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < 4; k++) {
				map[i][j][k] = *(p + k);
				// b g r a
			}
			p += 4;
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			double nw_sum = (1.*map[i][j][0] + map[i][j][1] + map[i][j][2])/(r+g+b);
				map[i][j][0] = std::min(255., nw_sum*b);
				map[i][j][1] = std::min(255., nw_sum*g);
				map[i][j][2] = std::min(255., nw_sum*r);
		}
	}

	p = (unsigned char*)data;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < 4; k++) {
				*(p + k) = map[i][j][k];
			}
			p += 4;
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete [] map[i][j];
		}
		delete [] map[i];
	}
	delete [] map;
	map = NULL;
}

void* FilterRender::doAuto(void *data, uint width, uint height) {
	unsigned char ***map;
	int *le;
	int *ri;
	bool *all;

	map = new unsigned char**[height];
	le = new int[height];
	ri = new int[height];
	all = new bool[height];

	for (int i = 0; i < height; i++) {
		map[i] = new unsigned char*[width];
		for (int j = 0; j < width; j++) {
			map[i][j] = new unsigned char[4];
		}
	}

	unsigned char * p = (unsigned char*)data;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < 4; k++) {
				map[i][j][k] = *(p + k);
				// b g r a
			}
			p += 4;
		}
	}

	const int margin = 5;

	for (int i = 0; i < height; i++) {
		bool flag = true;
		le[i] = 0;
		ri[i] = width;
		for (int j = 0; j < margin; j++) {
			if (equal(map[i][0], map[i][j])) {
				le[i] = j;
			} else {
				flag = false;
				break;
			}
		}
		if (!flag) continue;
		for (int j = 0; j < width - margin; j++) {
			if (equal(map[i][j], map[i][j + margin])) {
				le[i] = j;
			} else {
				break;
			}
		}
		for (int j = width - 1; j >= le[i]; j--) {
			if (equal(map[i][j], map[i][j - margin])) {
				ri[i] = j;
			} else {
				break;
			}
		}
	}

	for (int i = 0; i < height; i++) {
		if (le[i] >= ri[i]) {
			all[i] = true;
		} else {
			all[i] = false;
		}
	}

	int i, j;
	for (i = 0; i < height; i = j + 1) {
		j = i;
		int common = le[i];
		for (; j < height; j ++) {
			if (all[j]) {
				break;
			}
			if (le[j] < common) {
				common = le[j];
			}
		}
		for (int k = i; k < j; k++) {
			if (all[k]) continue;
			le[k] = common;
		}
	}

	for (i = 0; i < height; i = j + 1) {
		j = i;
		int common = ri[i];
		for (; j < height; j ++) {
			if (all[j]) {
				break;
			}
			if (ri[j] > common) {
				common = ri[j];
			}
		}
		for (int k = i; k < j; k++) {
			if (all[k]) continue;
			ri[k] = common;
		}
	}

	for (int i = 0; i < height; i++) {
		if (!all[i]) break;
		le[i] = width;
		ri[i] = 0;
		all[i] = false;

	}

	for (int i = height - 1; i >= 0; i--) {
		if (!all[i]) break;
		le[i] = width;
		ri[i] = 0;
		all[i] = false;
	}

	for (int i = 1; i < height; i++) {
		if (all[i]) {
			le[i] = le[i - 1];
			ri[i] = ri[i - 1];
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < le[i]; j++) {
			for (int k = 0; k < 4; k++) {
				map[i][j][k] = 255;
			}
		}
		for (int j = width - 1; j >= ri[i]; j--) {
			for (int k = 0; k < 4; k++) {
				map[i][j][k] = 0;
			}
		}
	}

	p = (unsigned char*)data;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			for (int k = 0; k < 4; k++) {
				*(p + k) = map[i][j][k];
			}
			p += 4;
		}
	}

	delete [] le;
	delete [] ri;
	delete [] all;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete [] map[i][j];
		}
		delete [] map[i];
	}
	delete [] map;
	map = NULL;
}
