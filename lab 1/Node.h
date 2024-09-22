#pragma once
#include "Car.h"
#include <iostream>
#include <string>

using namespace std;

class Node : public Car
{
public:
	Node* next;
	int GetYear() const;
	int GetMileage() const;
	float GetPrice() const;
	string GetBrand() const;
	string GetModel() const;
};