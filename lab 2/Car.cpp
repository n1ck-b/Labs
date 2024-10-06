#include "Header.h"

void Car::setYear(int year)
{
	yearOfProduction = year;
}
void Car::setMileage(int mile)
{
	mileage = mile;
}
void Car::setPrice(float pr)
{
	price = pr;
}
void Car::setBrand(const string& br)
{
	brand = br;
}
void Car::setModel(const string& md)
{
	model = md;
}
void Car::setObject(int year, int mile, float pr, const string& br, const string& md)
{
	yearOfProduction = year;
	mileage = mile;
	price = pr;
	brand = br;
	model = md;
}
int Car::getYear() const
{
	return yearOfProduction;
}
int Car::getMile() const
{
	return mileage;
}
float Car::getPrice() const
{
	return price;
}
string Car::getBrand() const
{
	return brand;
}
string Car::getModel() const
{
	return model;
}
