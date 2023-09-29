#include <iostream>
#include <fstream>
#include <math.h>
#include <random>
#include <time.h>
#include <vector>


// Холмик
class Hill
{
private:
  double x; // координаты
  double y; // неровности
  double sigma; // средне квадратичное отклонение
  double hight; // "высота" холма
public:
  Hill(double size_x, double size_y);
  Hill(double x0, double y0, 
       double sigma0, double hight0):
       x(x0), y(y0), hight(hight0)
       {sigma = abs(sigma0);}

  // Нормальное распределение в точке относительно холма
  double Gauss(double x0, double y0) const;
};

class Stoun
{
private:
  double x;
  double y;
  double r;
public:
  Stoun(double size_x, double size_y);
  Stoun(double x0, double y0, 
        double r0): x(x0), y(y0), r(r0){}

  double get_x() const {return x;}
  double get_y() const {return y;}
  double get_r() const {return r;}
  double dist(double x0, double y0) const;
};

class Log
{
private:
  double x1;
  double y1;
  double x2;
  double y2;
  double r;
public:
  Log(double size_x, double size_y);
  Log(double x01, double y01, 
      double x02, double y02, 
      double r0): x1(x01), y1(y01), 
                  x2(x02), y2(y02), r(r0){}

  double get_x1() const {return x1;}
  double get_y1() const {return y1;}
  double get_x2() const {return x2;}
  double get_y2() const {return y2;}
  double get_r() const {return r;}
  double dist(double x0, double y0) const;
};

// Бездорожье
class NoWay
{
private:
  double size_x; // размеры 
  double size_y; // поверхности
  std::vector<Hill> hills; // вектор холмов
  std::vector<Stoun> stouns;
  std::vector<Log> logs;
  int count_hills; // количество холмов
  int count_stouns;
  int count_logs;
public:
  NoWay() = default;
  NoWay(double x, double y, int count_hills = 0, 
        int count_stouns = 0, int count_logs = 0);

  // Вывод поверхности в файл для GNUplot
  void print(std::ofstream &file1, std::ofstream &file2, 
             std::ofstream &file3) const;
};

/*class Rover
{
private:
  double x;
  double y;
  std::vector<double> rotation;
  double speed;
};*/

// Двумерная функция Гаусса о нормальном распределении
double f(double x, double y, Hill H);

// Задача про ровер на бездорожье
// Скорбилин Илья
// 112 группа 
int main() 
{
  srand(time(NULL));
  NoWay shrek(25, 25, 25, 10, 5);
  std::ofstream file1("hills.txt");
  std::ofstream file2("stouns.txt");
  std::ofstream file3("logs.txt");
  shrek.print(file1, file2, file3);
  file1.close();
  file2.close();
  file3.close();
  return 0;
}

Hill::Hill(double size_x, double size_y)
{
  x = random() / double(RAND_MAX) * size_x - size_x/2;
  y = random() / double(RAND_MAX) * size_y - size_y/2;
  sigma = random() / double(RAND_MAX) * 1.9 + 0.1;
  hight = random() / double(RAND_MAX) * 10 - 5;
}

Stoun::Stoun(double size_x, double size_y)
{
  x = random() / double(RAND_MAX) * size_x - size_x/2;
  y = random() / double(RAND_MAX) * size_y - size_y/2;
  r = random() / double(RAND_MAX) * 1 + 0.5;
}

Log::Log(double size_x, double size_y)
{
  x1 = random() / double(RAND_MAX) * size_x - size_x/2;
  y1 = random() / double(RAND_MAX) * size_y - size_y/2;
  r = random() / double(RAND_MAX) * 4.5 + 0.5;
  double lenght = (random() / double(RAND_MAX) * 5 + 1) * r;
  double direction = random() / double(RAND_MAX) * 2;
  x2 = x1 + lenght * cos(direction * M_PI);
  y2 = y1 + lenght * sin(direction * M_PI);
}

NoWay::NoWay(double x, double y, int count_hills, 
             int count_stouns, int count_logs): 
             size_x(x), size_y(y), count_hills(count_hills), 
             count_stouns(count_stouns), count_logs(count_logs)
{
  for(int i = 0; i < count_hills; i++)
  {
    hills.push_back(Hill(x, y));
  }
  for(int i = 0; i < count_stouns; i++)
  {
    stouns.push_back(Stoun(x, y));
  }
  for(int i = 0; i < count_logs; i++)
  {
    logs.push_back(Log(x, y));
  }
}


double Hill::Gauss(double x0, double y0) const
{
  double e = exp(-((x - x0) * (x - x0) + (y - y0) * (y - y0)) / 2 * sigma * sigma);
  return (hight * e) / (sigma * sqrt(2 * M_PI));
}

void NoWay::print(std::ofstream &file1, std::ofstream &file2, 
                  std::ofstream &file3) const
{
  double z;
  for (double i = -size_x/2; i <= size_x/2; i+=size_x/40)
  {
    for (double j = -size_y/2; j <= size_y/2; j+=size_y/40)
    {
      z = 0;
      for (int k = 0; k < count_hills; k++)
      {
        z+=hills[k].Gauss(i, j);
      }
      file1 << i << " " << j << " " << z << "\n";
    }
    file1 << "\n";
  }

  
  for (int k = 0; k < count_stouns; k++)
  {
    z = 0;
    for (int m = 0; m < count_hills; m++)
    {
      z+=hills[m].Gauss(stouns[k].get_x(), stouns[k].get_y());
    }
    for (double i = stouns[k].get_r(); i > 0; i-=stouns[k].get_r()/5)
    {
      for (double j = 0; j <= 2.1; j+=0.1)
      {
        file2 << stouns[k].get_x() + i * cos(j * M_PI) << 
          " " << stouns[k].get_y() + i * sin(j * M_PI) << 
          " " << sqrt(stouns[k].get_r() * stouns[k].get_r() - i * i) + z << "\n";
      }
      file2 << "\n";
    }
    file2 << "\n";
  }
  double z1, z2, a, b, l;
  for (int k = 0; k < count_logs; k++)
  {
    z1 = 0; 
    z2 = 0;
    for (int m = 0; m < count_hills; m++)
    {
      z1+=hills[m].Gauss(logs[k].get_x1(), logs[k].get_y1());
      z2+=hills[m].Gauss(logs[k].get_x2(), logs[k].get_y2());
    }
    a = logs[k].get_y1() - logs[k].get_y2();
    b = logs[k].get_x2() - logs[k].get_x1();
    l = sqrt(a * a + b * b);
    for (double i = -logs[k].get_r(); i <= logs[k].get_r(); i+=logs[k].get_r()/10)
    {
      for (double d = 0; d <= 1; d += 0.25) {
        file3 << logs[k].get_x1() + a * i / l << 
          " " << logs[k].get_y1() + b * i / l << 
          " " << (sqrt(logs[k].get_r() * logs[k].get_r() - i * i) + z1) * d << "\n";
      }
      for (double j = 0; j <= 1; j+=0.05)
      {
        file3 << logs[k].get_x1() + a * i / l + b * j << 
          " " << logs[k].get_y1() + b * i / l - a * j << 
          " " << sqrt(logs[k].get_r() * logs[k].get_r() - i * i) + (z2 - z1) * j << "\n";
      }
      for (double d = 1; d >= 0; d -= 0.25) {
        file3 << logs[k].get_x2() + a * i / l << 
          " " << logs[k].get_y2() + b * i / l << 
          " " << (sqrt(logs[k].get_r() * logs[k].get_r() - i * i) + z2) * d << "\n";
      }
      file3 << "\n";
    }
    file3 << "\n";
  }
}