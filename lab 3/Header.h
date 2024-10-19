#pragma once
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

using namespace std;

int mainMenu();
int subMenu();
template <typename T> void carDataInput(T& carClass);
int tableRowCount(int& count, const string& tableName);
void dbRowsCount(int& hybridCount, int& combustionCount, int& electricCount);
void addOneCar();
void catalogOutput();
void checkCatalogIndex(int type, int catalogIndex, int electricCount, int combustionCount, int hybridCount);
void updateCarInfo();
void deleteOneCar();
void searchForCar();
template <typename T> void compareAndPrint(T val1, T val2, bool isReverse, const string& msg);
void compareCars();
template <typename T> void inputDataInRange(const string& msg, T& min, T& max);
template <typename T> void compareCarsToParameters(int type, vector <T> carObj, vector <float> vectorFloat);
