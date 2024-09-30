#pragma once
#include "Car.h"
#include <iostream>
#include <string>

using namespace std;

class Node : public Car
{
public:
	Node* next;
	int getYear() const;
	int getMileage() const;
	float getPrice() const;
	string getBrand() const;
	string getModel() const;
};