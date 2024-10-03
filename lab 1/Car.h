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
	void setYear(int year);
	void setMileage(int mile);
	void setPrice(float pr);
	void setBrand(const std::string& br);
	void setModel(const std::string& md);
	void setObject(int year, int mile, float pr, const std::string& br, const std::string& md);
	void readObject() const;
};