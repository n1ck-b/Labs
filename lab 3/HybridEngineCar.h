#pragma once
#include "Header.h"
template <typename T>
class Repository;

class HybridEngineCar: public ElectricEngineCar, public CombustionEngineCar
{
	friend class Repository<HybridEngineCar>;
private:
	int hybridType; //0 - ����������������, 1 - ������������
public:
	void setHybridType(int hybridType);
};