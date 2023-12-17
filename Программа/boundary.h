#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "control.h"
using namespace std;

class boundary {
private:
	string cmd; // название команды
	string logb; // имя лог файла
	control server; // объект класса control
public:
	boundary(string cmd, string logb, string logc);
	void body();
};