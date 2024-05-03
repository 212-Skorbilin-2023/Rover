#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "field.h"

using namespace std;

// Класс определяющий тип препятствия перед ровером
// Скорбилин Илья и Челышев Сергей
// 212 группа
class FrontCheck{ 
int c; // Для передачи тем, кто будет строить объезд, что за препятсвие (5, если нет препятствия, 1, 2, 3, 4 — соответсвенно гора, камень, яма и бревно)
double height, radius; // Высота и радиуса найденного препятствия
public:
field swamp;
FrontCheck();
FrontCheck(int c0, int height0, int radius0, field& swamp);
/* 
Функция возвращает тип препятствия
На вход принимает координаты ровера (х и y)
и вектор направления ровера (v1, v2) (например 1, 0)
*/
int Function(int x, int y, int v1, int v2); 
};
/*
1 — гора
2 — камень
3 — яма
4 — бревно
5 — нет препятствия
*/