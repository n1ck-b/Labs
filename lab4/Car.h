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
	int getYear() const;
	int getMileage() const;
	float getPrice() const;
	std::string getBrand() const;
	std::string getModel() const;
	void setYear(int yearOfProduction);
	void setMileage(int mileage);
	void setPrice(float price);
	void setBrand(const std::string& CarBrand);
	void setModel(const std::string& CarModel);
	virtual ~Car() = 0;
};