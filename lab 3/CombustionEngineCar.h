#pragma once
#include "Header.h"

class CombustionEngineCar: virtual public Car
{
protected:
	int fuelTankCapacity;
public:
	void addCar(int year, int mileage, float price, const std::string& brand, const std::string& model, float tankCapacity) const;
	void print() override;
	void updateCar(int index, int year, int mileage, float price, const std::string& brand, const std::string& model, float tankCapacity) const;
	virtual void deleteCar(int index) const;
	void getCar(int index, int& year, int& mileage, float& price, std::string& brand, std::string& model, float& tankCapacity) const;
};