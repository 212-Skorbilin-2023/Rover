#include "control.h"

control::control(string logc) {
	this->logc = logc;
}

void control::body(double x, double y, int g, int k, int b, int hight, int clearance, double alpha, double beta, int A1, int A2, int B1, int B2) {
	ofstream logc(this->logc);
  swamp = new field(x, y);
	logc << "Поле успешно создано" << endl;
  (*swamp).generate(g, k, b);
	logc << "Поле успешно сгенерировано" << endl;
  (*swamp).calculate();
	logc << "Поле успешно обсчитано и сохранено" << endl;
  bug = new rover(hight, clearance, alpha, beta, *swamp);
	logc << "Ровер успешно создан" << endl;
  proc = new processor(A1, A2, B1, B2, *bug);
	logc << "Процессор успешно инициализирован" << endl;
	
	(*proc).route();
	delete swamp;
	delete bug;
	delete proc;
}