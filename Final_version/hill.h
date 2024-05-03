#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

class Hill {
private:
	double x; // координаты
	double y; // гаусяна
	double dispx; //
	double dispy; // дисперсия
	double dispxy; //
	double h; // высота
public:
	Hill() = default;
	Hill(double x, double y, double dispx, double dispy, double h);
	double gauss(double x0, double y0);
};