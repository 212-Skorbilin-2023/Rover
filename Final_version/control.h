#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "field.h"
#include "rover.h"
#include "processor.h"
#include "frontcheck.h"
using namespace std;

class control {
private:
	string logc; // имя лог файла
	field* swamp; // поле
	rover* bug; // ровер
	processor* proc; // процессор
  FrontCheck* check;
public:
	control() = default;
	control(string logc);
	void body(double x, double y, int g, int k, int b, int hight, int clearance, double alpha, double beta, int A1, int A2, int B1, int B2);
};