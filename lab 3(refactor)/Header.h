#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "sqlite/sqlite3.h"
#include "Car.h"
#include "ElectricEngineCar.h"
#include "CombustionEngineCar.h"
#include "HybridEngineCar.h"

using namespace std;

int mainMenu();
int subMenu();
void carDataInput(bool isFull, int& type, int& year, int& mileage, float& price, string& brand, string& model);
int tableRowCount(int& count, const string& tableName);
void dbRowsCount(int& hybridCount, int& combustionCount, int& electricCount);
void addOneCar();
void catalogOutput();
void checkCatalogIndex(int type, int catalogIndex, int electricCount, int combustionCount, int hybridCount);
void updateCarInfo();
void deleteOneCar();
void searchForCarInDB(const string& tableName, const string& parameter1, const string& parameter2, const string& fieldName, int type);
void searchForCar();
template <typename T> void compareAndPrint(T val1, T val2, bool isReverse, const string& msg);
void compareCars();
void carDataInput(bool isFull, int& type, int& year, int& mileage, float& price, string& brand, string& model);
template <typename T> void inputDataInRange(const string& msg, T& min, T& max);