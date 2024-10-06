#pragma once
#include <iostream>
#include <string>


class Car
{
private:
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
	int getYear() const;
	int getMile() const;
	float getPrice() const;
	std::string getBrand() const;
	std::string getModel() const;
	friend std::ostream& operator << (std::ostream& os, const Car& car)
	{
		os << "  Год выпуска: " << car.yearOfProduction << std::endl;
		os << "  Пробег в км: " << car.mileage << std::endl;
		os << "  Стоимость в $: " << car.price << std::endl;
		os << "  Марка: " << car.brand << std::endl;
		os << "  Модель: " << car.model << std::endl;
		return os;
	}
};