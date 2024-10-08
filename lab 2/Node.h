#pragma once
#include "Header.h"

class Node
{
public:
	Car car;
	Node* next;
	friend bool operator == (const Node& car1, const Node& car2)
	{
		return car1.car.getYear() == car2.car.getYear() && car1.car.getMile() == car2.car.getMile() && car1.car.getPrice() == car2.car.getPrice() && car1.car.getBrand() == car2.car.getBrand() && car1.car.getModel() == car2.car.getModel();
	}
};