#include "Header.h"

using namespace std;

int Node::GetYear() const
{
	return yearOfProduction;
}
int Node::GetMileage() const
{
	return mileage;
}
float Node::GetPrice() const
{
	return price;
}
string Node::GetBrand() const
{
	return brand;
}
string Node::GetModel() const
{
	return model;
}