#pragma once
#include <cmath>
using namespace std;

class Stone {
private:
	double x; // координаты
	double y; // камня
	double R; // радиус
public:
	Stone() = default;
	Stone(double x, double y, double R);
	double sphere(double x0, double y0);
};