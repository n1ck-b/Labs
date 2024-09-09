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
void Car::setBrand(string& br)
{
	brand.assign(br);
}
void Car::setModel(string& md)
{
	model.assign(md);
}
void Car::setObject(int year, int mile, float pr, string& br, string& md)
{
	yearOfProduction = year;
	mileage = mile;
	price = pr;
	brand = br;
	model = md;
}
void Car::readObject()
{
	cout << "  ��� �������: " << yearOfProduction << endl;
	cout << "  ������ � ��: " << mileage << endl;
	cout << "  ��������� � $: " << price << endl;
	cout << "  �����: " << brand << endl;
	cout << "  ������: " << model << endl;
}
void Car::deleteObject(Car**& array, int index, int &numOfCars)
{
	if (numOfCars <= 0 || index < 0 || index >= numOfCars)
	{
		cout << "�������� ������ ��� ����� ����������� = 0" << endl;
		return;
	}
	delete[] array[index];
	for (int i = index; i < numOfCars - 1; i++)
	{
		array[i] = array[i + 1];
	}
	array[numOfCars - 1] = nullptr;
	numOfCars--;
}
int mainMenu()
{
	int choice;
	while (true)
	{
		cout << "\n��������� ��������\n1. �������� ����� ����������\n2. ������� �������\n3. �������� ���������� �� ����������\n4. ������� ���������� �� ��������\n5. ��������� ����������" << endl;
		cout << "�������� ����� ����: ";
		cin >> choice;
		if (cin.fail() || choice <= 0 || choice > 5)
		{
			cout << "\n������������ ����" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
		{
			return choice;
		}
	}
}
int subMenu()
{
	int choice;
	while (true)
	{
		cout << "�������� �������� ��� ���������:" << endl;
		cout << "  1. ��� ������� \n  2. ������\n  3. ��������� � $\n  4. �����\n  5. ������" << endl;
		cout << "������� ����� ����" << endl;
		cin >> choice;
		if (cin.fail() || choice <= 0 || choice > 5)
		{
			cout << "\n������������ ����" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
		{
			return choice;
		}
	}
}
Car** addOneCar(Car** array, int& numOfCars)
{
	int year;
	int mileage;
	float price;
	string brand;
	string model;
	array[numOfCars] = new Car[1];
	numOfCars++;
	cout << "������� ��� ������� ����������: ";
	cin >> year;
	cout << "������� ������ � ��: ";
	cin >> mileage;
	cout << "������� ��������� $: ";
	cin >> price;
	cout << "������� �������� �����: ";
	cin.ignore();
	getline(cin, brand);
	cout << "������� �������� ������: ";
	getline(cin, model);
	array[numOfCars - 1]->setObject(year, mileage, price, brand, model);
	return array;
}
void catalogOutput(Car** array, int numOfCars)
{
	if (numOfCars == 0)
	{
		cout << "\n����������� � �������� ���" << endl;
		return;
	}
	for (int i = 0; i < numOfCars; i++)
	{
		cout << "\n" << i + 1 << "-� ����������:" << endl;
		array[i]->readObject();
	}
}
Car** updateCarInfo(Car** array, int numOfCars)
{
	if (numOfCars == 0)
	{
		cout << "����������� � �������� ���" << endl;
		return array;
	}
	int catalogIndex;
	int choice;
	int year;
	int mileage;
	float price;
	string brand;
	string model;
	catalogOutput(array, numOfCars);
	cout << "\n������� ������ ����������, � ������� ���������� �������� ����������" << endl;
	cin >> catalogIndex;
	choice = subMenu();
	switch (choice)
	{
		case 1:
			cout << "\n������� ��� �������: ";
			cin >> year;
			array[catalogIndex - 1]->setYear(year);
			break;
		case 2:
			cout << "\n������� ������ � ��: ";
			cin >> mileage;
			array[catalogIndex - 1]->setMileage(mileage);
			break;
		case 3:
			cout << "\n������� ��������� � $: ";
			cin >> price;
			array[catalogIndex - 1]->setPrice(price);
			break;
		case 4:
			cout << "\n������� �����: ";
			cin.ignore();
			getline(cin, brand);
			array[catalogIndex - 1]->setBrand(brand);
			break;
		case 5:
			cout << "\n������� ������: ";
			cin.ignore();
			getline(cin, model);
			array[catalogIndex - 1]->setModel(model);
			break;
	}
	return array;
}
Car** deleteOneCar(Car** array, int& numOfCars)
{
	if (numOfCars == 0)
	{
		cout << "����������� � �������� ���" << endl;
		return array;
	}
	int catalogIndex;
	catalogOutput(array, numOfCars);
	cout << "\n������� ������ ����������, ������� ���������� ������� �� ��������" << endl;
	cin >> catalogIndex;
	array[catalogIndex - 1]->deleteObject(array, catalogIndex - 1, numOfCars);
	return array;
}
void freeMemory(Car**& array, int numOfCars)
{
	for (int i = 0; i < numOfCars; i++)
	{
		delete[] array[i];
	}
}