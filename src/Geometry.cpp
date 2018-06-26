//
// Created by timemachine on 18-6-27.
//

#include "Geometry.h"
#include "Point.h"

namespace Geometry
{

	const double eps = 1e-8;

	int sgn(double x) {
		return (x > eps) - (x < -eps);
	}
	int sgn(double a, double b){
		return sgn(a - b);
	}
	double sqr(double x) {
		return x * x;
	}
	Line::Line() {}
	Line::Line(Point a, Point b) : a(a), b(b) {}
	Point Line::v() {return b - a;}

	bool OnLine(Point p, Line l){
		return sgn((l.a - p) * (l.b - p)) == 0 && sgn((p - l.a) ^ (l.b - l.a)) >= 0 && sgn((p - l.b) ^ (l.a - l.b)) >= 0;
	}

	double det(Point a, Point b, Point c){
		return (b - a) * (c - a);
	}

	bool InPoly(Point p, std::vector<Point> poly){
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

};