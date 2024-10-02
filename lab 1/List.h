#pragma once
#include "Car.h"
#include "Node.h"
#include <iostream>
#include <string>


class List : public Car
{
private:
	Node* first = nullptr;
	Node* last = nullptr;
	int num = 0;
public:
	~List();
	int getNum() const;
	bool isEmpty() const;
	void push(int year, int mileage, float price, const string& brand, const string& model);
	void print();
	void removeByIndex(int index);
	Node* operator [] (int index);
	void searchByParameter(int choice, int year, int mileage, float priceLow, float priceHigh, const string& brand, const string& model);
};