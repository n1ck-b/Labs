#pragma once
#include "Car.h"
#include "Node.h"
#include <iostream>
#include <string>

using namespace std;

class List : public Car
{
private:
	Node* first;
	Node* last;
	int num;
public:
	List();
	~List();
	int getNum() const;
	bool isEmpty() const;
	void push(int year, int mileage, float price, const string& brand, const string& model);
	void print();
	void removeByIndex(int index);
	Node* operator [] (int index);
	void searchByParameter(int choice, int year, int mileage, float priceLow, float priceHigh, const string& brand, const string& model);
};