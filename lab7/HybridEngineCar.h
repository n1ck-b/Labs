#pragma once
#include "Functions.h"
template <typename T>
class Repository;

class HybridEngineCar : public ElectricEngineCar, public CombustionEngineCar
{
	friend class Repository<HybridEngineCar>;
private:
	int hybridType; //0 - последовательный, 1 - параллельный
public:
	void setHybridType(int hybridType);
};