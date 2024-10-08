#pragma once
#include "Car.h"
#include "Node.h"
#include <iostream>
#include <string>

class List
{
private:
	Node* first = nullptr;
	Node* last = nullptr;
	int num = 0;
public:
	~List();
	int getNum() const;
	bool isEmpty() const;
	void push(int year = 0, int mileage = 0, float price = 0, const std::string& brand = " ", const std::string& model = " ");
	void print();
	void removeByIndex(int index);
	Node* operator [] (int index);
	void searchByParameter(int choice, const int* year, const int* mileage, const float* price, const std::string& brand, const std::string& model);
};