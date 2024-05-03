#include "stone.h"

Stone::Stone(double x, double y, double R) {
	this->x = x;
	this->y = y;
	this->R = R;
}

double Stone::sphere(double x0, double y0) {
	if (R * R - (x - x0) * (x - x0) - (y - y0) * (y - y0) > 0) {
		return sqrt(R * R - (x - x0) * (x - x0) - (y - y0) * (y - y0));
	}
	return 0;
}