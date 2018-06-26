//
// Created by timemachine on 18-6-27.
//

#include "Point.h"
#include "Geometry.h"

namespace Geometry{
	Point::Point() {}
	Point::Point(double _x, double _y) : x(_x), y(_y) {}
	Point::~Point() {}
	double Point::len2() {
		using namespace Geometry;
		return sqr(x) + sqr(y);
	}
	double Point::len() {
		return sqrt(len2());
	}
	void Point::print() {
		printf("(%.3f, %.3f)\n", x, y);
	}

	bool operator==(Point a, Point b) {
		//using namespace Geometry;
		return !sgn(a.x - b.x) and !sgn(a.y - b.y);
	}
	Point operator+(Point a, Point b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	Point operator-(Point a, Point b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	Point operator*(Point a, double b) {
		return Point(a.x * b, a.y * b);
	}
	Point operator/(Point a, double b) {
		return Point(a.x / b, a.y / b);
	}
	double operator^(Point a, Point b) {
		return a.x * b.x + a.y * b.y;
	}
	double operator*(Point a, Point b) {
		return a.x * b.y - a.y * b.x;
	}
}


