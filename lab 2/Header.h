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
void compareAndPrintForPrice(float a, float b);
void compareAndPrintForMile(int a, int b);
void compareAndPrintForYear(int a, int b);
void compareCars(List& list);