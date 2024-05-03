#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include "rover.h"
#include "frontcheck.h"

class processor {
private:
	int A1;
	int A2;
	int B1;
	int B2;
	rover turtle;
  FrontCheck check;
public:
	processor(int A1, int A2, int B1, int B2, rover& turtle, FrontCheck& check);
	processor();
	void route();
};