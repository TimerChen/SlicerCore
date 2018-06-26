//
// Created by timemachine on 18-6-27.
//

#ifndef SLICER_GEOMETRY_H
#define SLICER_GEOMETRY_H


#include "Point.h"

#include <vector>

//class Point;

namespace Geometry
{

	extern const double eps;
	int sgn(double x) ;
	int sgn(double a, double b);
	double sqr(double x) ;

	struct Line {
		Point a, b;
		Line() ;
		Line(Point a, Point b) ;
		Point v();
	};

	bool OnLine(Point p, Line l);
	double det(Point a, Point b, Point c);
	bool InPoly(Point p, std::vector<Point> poly);

};


#endif //SLICER_GEOMETRY_H
