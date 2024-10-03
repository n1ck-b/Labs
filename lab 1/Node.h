#pragma once
#include "Car.h"
#include <iostream>
#include <string>

class Node
{
public:
	Car car;
	Node* next;
	int getYear() const;
	int getMileage() const;
	float getPrice() const;
	std::string getBrand() const;
	std::string getModel() const;
};