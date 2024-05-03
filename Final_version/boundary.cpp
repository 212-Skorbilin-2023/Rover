#include "boundary.h"

boundary::boundary(string cmd, string logb, string logc) {
	this->cmd = cmd;
	this->logb = logb;
	this->server = control(logc);
}

void boundary::body() {
	string str, line;
	double x = 10, y = 10, alpha = 0, beta = 0;
	int g = 0, k = 0, b = 0, i = 0;
	int hight = 0, clearance = 0, speed = 0, A1 = 0, A2 = 0, B1 = 0, B2 = 0;
	ofstream logb(this->logb);
	ifstream cmd(this->cmd);
	while (getline(cmd, line)) {
		istringstream iss(line);
		iss >> str;
		if (str == "field") {
			iss >> x;
			iss >> y;
			logb << "Создание поля" << endl;
			i++;
		}
		if (str == "generate") {
			iss >> g;
			iss >> k;
			iss >> b;
			logb << "Генерация поля" << endl;
			i++;
		}
		if (str == "calculate") {
			logb << "Подсчёт и сохранение поля" << endl;
			i++;
		}
    if (str == "load") {
      logb << "Загрузка поля" << endl;
      i++;
    }
		if (str == "rover") {
			iss >> hight;
			iss >> clearance;
			iss >> alpha;
			iss >> beta;
			iss >> speed;
			logb << "Создание ровера" << endl;
			i++;
		}
		if (str == "processor") {
			iss >> A1;
			iss >> A2;
			iss >> B1;
			iss >> B2;
			logb << "Инициализация процессора" << endl;
			i++;
		}
	}
	if (i < 5) {
		logb << "ОШИБКА в командном файле слишком мало команд" << endl;
	}
	server.body(x, y, g, k, b, hight, clearance, alpha, beta, A1, A2, B1, B2);
}