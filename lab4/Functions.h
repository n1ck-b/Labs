#pragma once
//#pragma execution_character_set("utf-8")
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "sqlite/sqlite3.h"
#include <Windows.h>
#include "Car.h"
#include "ElectricEngineCar.h"
#include "CombustionEngineCar.h"
#include "HybridEngineCar.h"
#include "Repository.h"
#include <typeinfo>
#include <vector>

using namespace std;

int tableRowCount(int& count, const string& tableName);
void dbRowsCount(int& hybridCount, int& combustionCount, int& electricCount);
