#include "Header.h"

using namespace std;

int Node::getYear() const
{
	return yearOfProduction;
}
int Node::getMileage() const
{
	return mileage;
}
float Node::getPrice() const
{
	return price;
}
string Node::getBrand() const
{
	return brand;
}
string Node::getModel() const
{
	return model;
}