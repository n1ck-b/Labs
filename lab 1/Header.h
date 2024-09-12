#include <iostream>
#include <string>
using namespace std;

class Car
{
protected:
	int yearOfProduction;
	int mileage;
	float price;
	string brand;
	string model;
public:
	void setYear(int year);
	void setMileage(int mile);
	void setPrice(float pr);
	void setBrand(const string& br);
	void setModel(const string& md);
	void setObject(int year, int mile, float pr, const string& br, const string& md);
	void readObject() const;
};

class Node : public Car
{
public:
	Node* next;
	int GetYear() const;
	int GetMileage() const;
	float GetPrice() const;
	string GetBrand() const;
	string GetModel() const;
};

class List : public Car
{
private:
	Node* first;
	Node* last;
	int num;
public:
	List();
	~List();
	int GetNum() const;
	bool isEmpty() const;
	void push(int year, int mileage, float price, const string& brand, const string& model);
	void print();
	void removeByIndex(int index);
	Node* operator [] (int index);
	void searchByParameter(int choice, int year, int mileage, float priceLow, float priceHigh, const string& brand, const string& model);
};

int mainMenu();
int subMenu();
void addOneCar(List& list);
void catalogOutput(List& list);
void updateCarInfo(List& list);
void deleteOneCar(List& list);
void searchForCar(List& list);