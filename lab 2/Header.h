#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Car.h"
#include "List.h"
#include "Node.h"

using namespace std;

int mainMenu();
int subMenu();
void addOneCar(List& list);
void catalogOutput(List& list);
void updateCarInfo(List& list);
void deleteOneCar(List& list);
void searchForCar(List& list);
bool match(const Node* current, int choice, int year, int mileage, float priceLow, float priceHigh, const string& brand, const string& model);
void readFromFile(List& list);
void writeToFile(List& list);
void rewriteToFile(List& list);
void compareCars(List& list);
void operator == (const Node& car1, const Node& car2);