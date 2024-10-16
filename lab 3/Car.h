#pragma once
#include <iostream>
#include <string>

class Car
{
protected:
	int yearOfProduction;
	int mileage;
	float price;
	std::string brand;
	std::string model;
public:
	virtual ~Car() = default;
	virtual void print() = 0;
	void executeQuery(const char* SQL) const;
	int findIDinDB(int index, const std::string& tableName) const;
};