#pragma once
#include "Header.h"

class ElectricEngineCar: virtual public Car
{
protected:
	int batteryCapacity;
public:
	void addCar(int year, int mileage, float price, const std::string& brand, const std::string& model, float btrCapacity) const;
	void print() override;
	void updateCar(int index, int year, int mileage, float price, const std::string& brand, const std::string& model, float btrCapacity) const;
	virtual void deleteCar(int index) const;
	void getCar(int index, int& year, int& mileage, float& price, std::string& brand, std::string& model, float& btrCapacity) const;
};