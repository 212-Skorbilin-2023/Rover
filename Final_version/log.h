#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;

class Log {
private:
	double x1; // координаты 
	double y1; // одного конца
	double x2; // координаты 
	double y2; // второго конца
	double R; // радиус бревна
public:
	Log() = default;
	Log(double x1, double y1, double x2, double y2, double R);
	double cylinder(double x0, double y0);
};