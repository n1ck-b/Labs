#include <iostream>
#include <string>
using namespace std;

class Car
{
private:
	int yearOfProduction;
	int mileage;
	float price;
	string brand;
	string model;
public:
	void setYear(int year);
	void setMileage(int mile);
	void setPrice(float pr);
	void setBrand(string& br);
	void setModel(string& md);
	void setObject(int year, int mile, float pr, string& br, string& md);
	void readObject() const;
	void deleteObject(Car**& array, int index, int& numOfCars);
};
int mainMenu();
int subMenu();
Car** addOneCar(Car** array, int& numOfCars);
void catalogOutput(Car** array, int numOfCars);
Car** updateCarInfo(Car** array, int numOfCars);
Car** deleteOneCar(Car** array, int& numOfCars);
void freeMemory(Car**& array, int numOfCars);