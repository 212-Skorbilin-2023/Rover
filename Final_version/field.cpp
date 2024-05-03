#include "field.h"

field::field() {
	x = 0;
	y = 0;
	Pixel[0][0] = 0;
}

field::field(double x, double y) {
	this->x = x;
	this->y = y;
	Pixel[0][0] = 0;
}

void field::one_more(){
  //B.push_back(Log(1.5, 1.5, 8.5, 8.5, 0.7)); // бревно
  // G.push_back(Hill(x, y, disx, disy, h)); // холм (яма)
  /*K.push_back(Stone(5, 5, 0.7)); 
  K.push_back(Stone(6.5, 8.5, 0.5));
  K.push_back(Stone(8, 5, 1.5));
  B.push_back(Log(7.5, 1.5, 8.5, 3.5, 0.3)); 
  G.push_back(Hill(1.5, 6.5, 0.5, 0.5, 1)); */



  B.push_back(Log(4, 1, 1, 2, 0.5)); 
 // B.push_back(Log(7, 3.5, 3, 3.5, 1.5)); 
 // B.push_back(Log(2, 5, 3, 9, 0.4)); 
  B.push_back(Log(4.5, 6, 6, 7, 0.7)); 
  B.push_back(Log(9, 6, 6, 9, 0.5)); 


  
  G.push_back(Hill(6, 5, 1, 1, 1.5)); 
  G.push_back(Hill(1, 6, 0.5, 0.5, 2));
  G.push_back(Hill(8.5, 7, 0.7, 0.8, 3));
  G.push_back(Hill(6, 5.6, 0.7, 0.8, -2)); 
  G.push_back(Hill(1.5, 9.5, 0.7, 0.5, 3));
  G.push_back(Hill(6.5, 8.5, 1, 1, 6));
  G.push_back(Hill(7, 3, 1, 1, 6));

  
  K.push_back(Stone(8, 8, 0.5)); 
  K.push_back(Stone(1.5, 3.5, 1));
  K.push_back(Stone(4.5, 2.5, 1));
  //K.push_back(Stone(6.5, 6, 0.5));
  //K.push_back(Stone(1, 2, 0.6)); 
  K.push_back(Stone(8.5, 9, 0.5));
  K.push_back(Stone(4.5, 0.5, 0.5));

  
  // B.push_back(Log(x, y, x2, y2, R)); // бревно
}

void field::generate(int g, int k, int b) {
	double x, y, dispx, dispy, h, R, x2, y2;
	int i;
	srand(time(NULL));
	for (i = 0; i < g; i++) {
		x = double(rand() % 10000) / 10000 * this->x;
		y = double(rand() % 10000) / 10000 * this->y;
		dispx = double(rand() % 10000) / 10000 + 0.1;
		dispy = double(rand() % 10000) / 10000 + 0.1;
		h = (double(rand() % 10000) / 10000 - 0.3) * sqrt(this->x * this->y);
		G.push_back(Hill(x, y, dispx, dispy, h));
	}
	for (i = 0; i < k; i++) {
		x = double(rand() % 10000) / 10000 * this->x;
		y = double(rand() % 10000) / 10000 * this->y;
		R = double(rand() % 10000) / 10000;
		K.push_back(Stone(x, y, R));
	}
	for (i = 0; i < b; i++) {
		x = double(rand() % 10000) / 10000 * this->x;
		y = double(rand() % 10000) / 10000 * this->y;
		x2 = double(rand() % 10000) / 10000 * this->x;
		y2 = double(rand() % 10000) / 10000 * this->y;
		R = double(rand() % 10000) / 20000 + 0.1;
		B.push_back(Log(x, y, x2, y2, R));
	}
}

void field::calculate() {
	unsigned int k;
	double h;
  //ofstream fout("field.txt");
	ofstream fout("field.txt"); // здесь нужно менять имя файла
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			double x = i * this->x / 128;
			double y = j * this->y / 128;
			h = 0;
			for (k = 0; k < G.size(); k++) {
				h += G[k].gauss(x, y);
			}
			for (k = 0; k < K.size(); k++) {
				h += K[k].sphere(x, y);
			}
			for (k = 0; k < B.size(); k++) {
				h += B[k].cylinder(x, y);
			}
			fout << x << " " << y << " " << h << endl;
			Pixel[i][j] = 128 * h / sqrt(this->x * this->y);
		}
		fout << endl;
	}
}

void field::load(string filename)
{
  double x, y, h;
  string line;
  ifstream fin(filename);
  for (int i = 0; i < 128; i++) {
    for (int j = 0; j < 128; j++) {
      getline(fin, line);
      istringstream iss(line);
      iss >> x >> y >> h;
      Pixel[i][j] = 128 * h / sqrt(x * y);
    }
    getline(fin, line);
  }
}