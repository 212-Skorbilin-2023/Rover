#include "control.h"

control::control(string logc) {
	this->logc = logc;
}

void control::body(double x, double y, int g, int k, int b, int hight, int clearance, double alpha, double beta, int A1, int A2, int B1, int B2) {
	ofstream logc(this->logc);
  swamp = new field(x, y);
	logc << "Поле успешно создано" << endl;

  // генерация и обсчёт поля
  /*
  (*swamp).generate(g, k, b);
	logc << "Поле успешно сгенерировано" << endl;
  (*swamp).calculate();
	logc << "Поле успешно обсчитано и сохранено" << endl;
  */

  // загрузка из файла
  
  //(*swamp).load("B_1.5_1.5_8.5_8.5_0.7.txt");
  //(*swamp).load("G_0.5_1.5_2.txt");
  //(*swamp).load("K_1.5.txt");
  //(*swamp).load("B_4.9_4.9_5.1_5.1_5.txt");
  //(*swamp).load("K_2.5.txt");
  

  

  // добавление одного (можно и не одного) препятствия и обсчёт поля
  (*swamp).one_more();
  (*swamp).calculate();

  
  bug = new rover(hight, clearance, alpha, beta, *swamp);
	logc << "Ровер успешно создан" << endl;
  check = new FrontCheck(0, 0, 0, *swamp);
  proc = new processor(A1, A2, B1, B2, *bug, *check);
	logc << "Процессор успешно инициализирован" << endl;
	
	(*proc).route();
	delete swamp;
	delete bug;
	delete proc;
  
}