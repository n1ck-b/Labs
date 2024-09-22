#include "Header.h"

using namespace std;

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
void Car::readObject() const
{
	cout << "  ��� �������: " << yearOfProduction << endl;
	cout << "  ������ � ��: " << mileage << endl;
	cout << "  ��������� � $: " << price << endl;
	cout << "  �����: " << brand << endl;
	cout << "  ������: " << model << endl;
}