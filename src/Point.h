//
// Created by louisja1 on 18-6-26.
//

#ifndef SLICER_POINT_H
#define SLICER_POINT_H


#include <cmath>
#include <cstdio>

class Point {
private:
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
public:
    double x, y;
    Point() {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    ~Point() {}
    double len2() {
		return sqr(x) + sqr(y);
	}
	double len() {
		return sqrt(len2());
	}
	void print() {
		printf("(%.3f, %.3f)\n", x, y);
	}
    friend bool operator==(Point a, Point b) {
    	return !sgn(a.x - b.x) and !sgn(a.y - b.y);
    }
    friend Point operator+(Point a, Point b) {
    	return Point(a.x + b.x, a.y + b.y);
    }
    friend Point operator-(Point a, Point b) {
    	return Point(a.x - b.x, a.y - b.y);
    }
    friend Point operator*(Point a, double b) {
    	return Point(a.x * b, a.y * b);
    }
    friend Point operator/(Point a, double b) {
    	return Point(a.x / b, a.y / b);
    }
    friend double operator^(Point a, Point b) {
    	return a.x * b.x + a.y * b.y;
    }
    friend double operator*(Point a, Point b) {
    	return a.x * b.y - a.y * b.x;
    }
};

#endif //SLICER_POINT_H
