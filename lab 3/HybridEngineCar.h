#pragma once
#include "Header.h"

class HybridEngineCar: public ElectricEngineCar, public CombustionEngineCar
{
private:
	enum class HybridType
	{
		SERIAL,
		PARALLEL
	};
public:
	void addCar(int year, int mileage, float price, const std::string& brand, const std::string& model, float btrCapacity, float tankCapacity, int hybridType) const;
	void print() override;
	void updateCar(int index, int year, int mileage, float price, const std::string& brand, const std::string& model, float btrCapacity, float tankCapacity, int hybridType) const;
	void deleteCar(int index) const override;
	void getCar(int index, int& year, int& mileage, float& price, std::string& brand, std::string& model, float& batteryCapacity, float& fuelTankCapacity, int& hybridType) const;
};