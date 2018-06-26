//
// Created by timemachine on 18-6-26.
//

#include "FilterRender.h"
#include "filter.h"
#include "Point.h"
#include "Geometry.h"

using namespace Geometry;

void* FilterRender::render(void *data, uint width, uint height, Config *config) {
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

		}

	}
	return data;
}

void swap(unsigned char &a, unsigned char &b) {
	unsigned char t = a;
	a = b;
	b = t;
}

void* FilterRender::doFlip(void *data, uint width, uint height, bool isLR) {
	unsigned char ***map;

	map = new unsigned char**[width];
	for (int i = 0; i < width; i++) {
		map[i] = new unsigned char*[height];
		for (int j = 0; j < height; j++) {
			map[i][j] = new unsigned char[4];
		}
	}

	unsigned char * p = (unsigned char*)data;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < 4; k++) {
				map[i][j][k] = *(p + k);
				// b g r a
			}
			p += 4;
		}
	}

	if (isLR) {
		for (int i = 0; i < width / 2; i++) {
			for (int j = 0; j < height; j++) {
				for (int k = 0; k < 4; k++) {
					swap(map[i][j][k], map[width - i][j][k]);
				}
			}
		}
	} else {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height / 2; j++) {
				for (int k = 0; k < 4; k++) {
					swap(map[i][j][k], map[i][height - j][k]);
				}
			}
		}
	}

	p = (unsigned char*)data;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < 4; k++) {
				*(p + k) = map[i][j][k];
			}
			p += 4;
		}
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			delete [] map[i][j];
		}
		delete [] map[i];
	}
	delete [] map;
	map = NULL;
}

void* FilterRender::doSlice(void *data, uint width, uint height, std::vector<Point> poly) {
	unsigned char ***map;

	map = new unsigned char**[width];
	for (int i = 0; i < width; i++) {
		map[i] = new unsigned char*[height];
		for (int j = 0; j < height; j++) {
			map[i][j] = new unsigned char[4];
		}
	}

	unsigned char * p = (unsigned char*)data;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < 4; k++) {
				map[i][j][k] = *(p + k);
				// b g r a
			}
			p += 4;
		}
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (!InPoly(Point(i, j), poly)) {
				map[i][j][0] = 255;
				map[i][j][1] = 255;
				map[i][j][2] = 255;
			}
		}
	}

	p = (unsigned char*)data;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < 4; k++) {
				*(p + k) = map[i][j][k];
			}
			p += 4;
		}
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			delete [] map[i][j];
		}
		delete [] map[i];
	}
	delete [] map;
	map = NULL;
}

void* FilterRender::doColor(void *data, uint width, uint height, double r, double g, double b, double a) {
	unsigned char ***map;

	map = new unsigned char**[width];
	for (int i = 0; i < width; i++) {
		map[i] = new unsigned char*[height];
		for (int j = 0; j < height; j++) {
			map[i][j] = new unsigned char[4];
		}
	}

	unsigned char * p = (unsigned char*)data;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < 4; k++) {
				map[i][j][k] = *(p + k);
				// b g r a
			}
			p += 4;
		}
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
				map[i][j][0] = b;
				map[i][j][1] = g;
				map[i][j][2] = r;
				map[i][j][3] = a;
		}
	}

	p = (unsigned char*)data;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < 4; k++) {
				*(p + k) = map[i][j][k];
			}
			p += 4;
		}
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			delete [] map[i][j];
		}
		delete [] map[i];
	}
	delete [] map;
	map = NULL;
}
