#include "frontcheck.h"
#define EPS 0.0001
#define TETA 0.1
#define WINDOW_SIZE 25
#define HALF_WINDOW_SIZE (WINDOW_SIZE - 1) / 2
#define MAX_SQUARE_SIZE 20
#define MIN_SQUARE_SIZE 3
#define KL_ARRAY_LENGHT MAX_SQUARE_SIZE - MIN_SQUARE_SIZE + 1
#define DELAY 5
//WINDOW_SIZE обязательно нечётный

FrontCheck::FrontCheck(int c0, int height0, int radius0, field& swamp){
  c = c0;
  height = height0;
  radius = radius0;
  this->swamp = swamp;
}

FrontCheck::FrontCheck(){
  c = 5;
  height = 0;
  radius = 0;
}


int FrontCheck::Function(int x, int y, int v1, int v2){

  double pixel[128][128];

  double window[2 * WINDOW_SIZE + 1][2 * WINDOW_SIZE + 1]; // Окно для поиска максимальной и минимальной высоты
  double square[2 * MAX_SQUARE_SIZE + 1][2 * MAX_SQUARE_SIZE + 1]; // Квадрат для определения типа препятствия
  int KL_array[KL_ARRAY_LENGHT][2]; // вспомогательный массив

  int centre_window_x = x + (DELAY + WINDOW_SIZE + 1) * v1; // Координаты 
  int centre_window_y = y + (DELAY + WINDOW_SIZE + 1) * v2; // центра окна
  double cur_height, max_height, min_height, delta_plus, delta_minus; // текущая высота, максимальная высота, минимальная высот, разница высоты вверх и вниз
  int max_x, max_y, min_x, min_y;
  int k=0, l=0; //Счетчик клеток равных нулю и почти равных нулю, для определения отсутствия препятсвий

  


  for (int i = 0; i < 128; i++){
    for (int j = 0; j < 128; j++){
      pixel[i][j] = double(swamp.Pixel[i][j] * 10) / 127;
    }
  }

  
  

  cur_height = swamp.Pixel[x][y];
  max_height = cur_height;
  min_height = cur_height;
  max_x = min_x = x;
  max_y = min_y = y;

  
  
  

  for (int i = -WINDOW_SIZE; i < WINDOW_SIZE + 1; i++){
    for (int j = -WINDOW_SIZE; j < WINDOW_SIZE + 1; j++){
      window[i + WINDOW_SIZE][j + WINDOW_SIZE] = pixel[centre_window_x + i][centre_window_y + j]; 
      if (window[i + WINDOW_SIZE][j + WINDOW_SIZE] > max_height){
        max_height = window[i + WINDOW_SIZE][j + WINDOW_SIZE];
        max_x = centre_window_x + i;
        max_y = centre_window_y + j;
      }
      if (window[i + WINDOW_SIZE][j + WINDOW_SIZE] < min_height){
        min_height = window[i + WINDOW_SIZE][j + WINDOW_SIZE];
        min_x = centre_window_x + i;
        min_y = centre_window_y + j;
      }
    }
  }

  
  delta_plus = max_height - cur_height;
  delta_minus = cur_height - min_height;

  if (delta_plus < TETA && delta_minus < TETA){
  c = 5;
  std::cout << "Препятствий нет";
  return c;
  }

  int flag_hill = 0, flag_stone = 0, flag_tree = 0;
  double max_ring = 0, next_max_ring = 0;
  for (int m = MIN_SQUARE_SIZE; m <= MAX_SQUARE_SIZE; m++){
    k = 0;
    l = 0;
    next_max_ring = 0;
    for (int i = -m; i < m + 1; i++){
      for (int j = -m; j < m + 1; j++){
        square[m + i][m + j] = pixel[max_x + i][max_y + j];
        if (square[m + i][m + j] < EPS) {
          k++;
        }
        if (square[m + i][m + j] < TETA){
          l++;
        }
        if (i == -m || i == m || j == -m || j == m){
          if (square[m + i][m + j] > max_ring) next_max_ring = square[m + i][m + j];
        }
      }
    }
    KL_array[m - MIN_SQUARE_SIZE][0] = k;
    KL_array[m - MIN_SQUARE_SIZE][1] = l;
   
    if (!flag_stone){
      if (next_max_ring < max_ring) flag_stone = 1;
    }
    max_ring = next_max_ring;
    std::cout << m << " " << k << " " << l << " " << max_ring << std::endl;
  } 

  
  //int radius;

  for (int i = 0; i < KL_ARRAY_LENGHT; i++){
    if (KL_array[i][1] == 0)
      continue;
    else if (KL_array[i][1] - KL_array[i][0] > 2 * (i + MIN_SQUARE_SIZE)){
      flag_hill = 1;
      flag_stone = 0;
      break;
    }
  }

  

  if (!flag_hill && !flag_stone) flag_tree = 1;

  if (flag_hill){
    c = 1;
    std::cout << "Перед нами гора\n";
  }if (flag_stone){
    c = 2;
    std::cout << "Перед нами камень\n";
  }if (c==3){
    std::cout << "Перед нами яма\n";
  }if (flag_tree){
    c = 4;
    std::cout << "Перед нами бревно\n";
  }
  return c;
}
