#pragma once
#include <time.h>
#include <fstream>
#include <vector>
#include "stone.h"
#include "log.h"
#include "hill.h"
using namespace std;

class field {
private:
	double x; // размеры
	double y; // поля
public:
	vector <Hill> G;
	vector <Stone> K;
	vector <Log> B;
	int Pixel[128][128]; // массив пикселей
	field();
	field(double x, double y);
	void generate(int g, int k, int b);
	void calculate();
};