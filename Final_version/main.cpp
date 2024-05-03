#include <iostream>
#include <sstream>
#include <string>
#include "field.h"
#include "boundary.h"
#include "hill.h"
#include "control.h"
#include "stone.h"
#include "log.h"
#include "rover.h"
#include "processor.h"
#include "frontcheck.h"
using namespace std;

// Скорбилин Илья 
// 212 группа

int main() {
	string str, line, cmd, logb, logc;
	cout << "Приветсвую, дорогой пользователь! Вы запустили программу, которая производит расчет поля и строит маршрут ровера." << endl;
	cout << "Введите имя конфигурационного файла: ";
	cin >> str;
	ifstream cfg(str);
	while (getline(cfg, line)) {
		istringstream iss(line);
		iss >> str;
		if (str == "command_file") {
			iss >> str;
			if (str == "=") {
				iss >> cmd;
			}
		}
		if (str == "log_boundary") {
			iss >> str;
			if (str == "=") {
				iss >> logb;
			}
		}
		if (str == "log_control") {
			iss >> str;
			if (str == "=") {
				iss >> logc;
			}
		}
	}
	boundary *interface = new boundary(cmd, logb, logc);
	(*interface).body();



  //std::cout << "Препятствие: " << "бревно\n" << "Координаты предполагаемого центра: " << "x = 5; y = 5\n" << "Радиус (примерный): " << "r = 0.7\n\n";

  //cout << "Точки поля сохранены в файле 'field.txt'\nМаршрут ровера — в файле 'rover.txt'" << endl;
	delete interface;
}