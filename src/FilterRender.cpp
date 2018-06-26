//
// Created by timemachine on 18-6-26.
//

#include "FilterRender.h"
#include "filter.h"
#include "Point.h"

const static double eps = 1e-8;

int sgn(double x) {
	return (x > eps) - (x < -eps);
}
int sgn(double a, double b){
	return sgn(a - b);
}
double sqr(double x) {
	return x * x;
}

struct Line {
	Point a, b;
	Line() {}
	Line(Point a, Point b) : a(a), b(b) {}
	Point v() {
		return b - a;
	}
};

bool OnLine(Point p, Line l){
	return sgn((l.a - p) * (l.b - p)) == 0 && sgn((p - l.a) ^ (l.b - l.a)) >= 0 && sgn((p - l.b) ^ (l.a - l.b)) >= 0;
}

double det(Point a, Point b, Point c){
	return (b - a) * (c - a);
}

bool InPoly(Point p, vector<Point> poly){
	int cnt = 0;
	for(int i = 0; i < poly.size(); i++){
		Point a = poly[i];
		Point b = poly[(i + 1) % poly.size()];
		if(OnLine(p, Line(a, b)))
			return true;
		int x = sgn(det(a, p, b));
		int y = sgn(a.y - p.y);
		int z = sgn(b.y - p.y);
		cnt += (x > 0 && y <= 0 && z > 0);
		cnt -= (x < 0 && z <= 0 && y > 0);
	}
	return cnt;
}

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

	unsigned char * p = data;

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

	p = data;

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

void* FilterRender::doSlice(void *data, uint width, uint height, std::vector<Point>) {
	unsigned char ***map;

	map = new unsigned char**[width];
	for (int i = 0; i < width; i++) {
		map[i] = new unsigned char*[height];
		for (int j = 0; j < height; j++) {
			map[i][j] = new unsigned char[4];
		}
	}

	unsigned char * p = data;

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

	p = data;

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

	unsigned char * p = data;

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
				map[i][j][0] = b;
				map[i][j][1] = g;
				map[i][j][2] = r;
				map[i][j][3] = a;
			}
		}
	}

	p = data;

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
