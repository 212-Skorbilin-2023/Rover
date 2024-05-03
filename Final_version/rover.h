#pragma once
#include "field.h"

class rover {
private:
	int hight; // высота ровера
	int clearance; // клиренс
	double alpha; // пороговые
	double beta; // углы
public:
	field swamp;
	rover(int heading, int clearance, double alpha, double beta, field& swamp);
	rover();
	int sensor(int x0, int y0, int x, int y);
	int angles(int x0, int y0, int x, int y);
};