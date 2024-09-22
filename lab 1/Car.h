#pragma once
#include <iostream>
#include <string>

using namespace std;

class Car
{
protected:
	int yearOfProduction;
	int mileage;
	float price;
	string brand;
	string model;
public:
	void setYear(int year);
	void setMileage(int mile);
	void setPrice(float pr);
	void setBrand(const string& br);
	void setModel(const string& md);
	void setObject(int year, int mile, float pr, const string& br, const string& md);
	void readObject() const;
};