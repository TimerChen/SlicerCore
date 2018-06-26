//
// Created by louisja1 on 18-6-26.
//

#ifndef SLICER_POINT_H
#define SLICER_POINT_H


#include <cmath>
#include <cstdio>

//#include "Geometry.h"

namespace Geometry
{

	class Point {
	public:
		double x, y;
		Point();
		Point(double _x, double _y);
		~Point();
		double len2();
		double len();
		void print();
	};

	bool operator==(Point a, Point b);
	Point operator+(Point a, Point b);
	Point operator-(Point a, Point b);
	Point operator*(Point a, double b);
	Point operator/(Point a, double b);
	double operator^(Point a, Point b);
	double operator*(Point a, Point b);
}


#endif //SLICER_POINT_H
