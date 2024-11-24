#pragma once
#include "Functions.h"
template <typename T>
class Repository;

class ElectricEngineCar : virtual public Car
{
	friend class Repository<ElectricEngineCar>;
protected:
	float batteryCapacity;
public:
	void setBatteryCapacity(float batteryCapacity);
	float getBatteryCapacity();
};