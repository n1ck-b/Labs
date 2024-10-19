#pragma once
#include "Header.h"
template <typename T>
class Repository;

class CombustionEngineCar: virtual public Car
{
	friend class Repository<CombustionEngineCar>;
protected:
	float fuelTankCapacity;
public:
	void setFuelTankCapacity(float fuelTankCapacity);
};