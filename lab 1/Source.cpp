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
	cout << "  Год выпуска: " << yearOfProduction << endl;
	cout << "  Пробег в км: " << mileage << endl;
	cout << "  Стоимость в $: " << price << endl;
	cout << "  Марка: " << brand << endl;
	cout << "  Модель: " << model << endl;
}
void Car::deleteObject(Car**& array, int index, int &numOfCars)
{
	if (numOfCars <= 0 || index < 0 || index >= numOfCars)
	{
		cout << "Неверный индекс или число автомобилей = 0" << endl;
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
		cout << "\nВозможные действия\n1. Добавить новый автомобиль\n2. Вывести каталог\n3. Изменить информацию об автомобиле\n4. Удалить автомобиль из каталога\n5. Завершить выполнение" << endl;
		cout << "Выберите пункт меню: ";
		cin >> choice;
		if (cin.fail() || choice <= 0 || choice > 5)
		{
			cout << "\nНекорректный ввод" << endl;
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
		cout << "Выберите параметр для изменения:" << endl;
		cout << "  1. Год выпуска \n  2. Пробег\n  3. Стоимость в $\n  4. Марка\n  5. Модель" << endl;
		cout << "Введите пункт меню" << endl;
		cin >> choice;
		if (cin.fail() || choice <= 0 || choice > 5)
		{
			cout << "\nНекорректный ввод" << endl;
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
	cout << "Введите год выпуска автомобиля: ";
	cin >> year;
	cout << "Введите пробег в км: ";
	cin >> mileage;
	cout << "Введите стоимость $: ";
	cin >> price;
	cout << "Введите название марки: ";
	cin.ignore();
	getline(cin, brand);
	cout << "Введите название модели: ";
	getline(cin, model);
	array[numOfCars - 1]->setObject(year, mileage, price, brand, model);
	return array;
}
void catalogOutput(Car** array, int numOfCars)
{
	if (numOfCars == 0)
	{
		cout << "\nАвтомобилей в каталоге нет" << endl;
		return;
	}
	for (int i = 0; i < numOfCars; i++)
	{
		cout << "\n" << i + 1 << "-й автомобиль:" << endl;
		array[i]->readObject();
	}
}
Car** updateCarInfo(Car** array, int numOfCars)
{
	if (numOfCars == 0)
	{
		cout << "Автомобилей в каталоге нет" << endl;
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
	cout << "\nВведите индекс автомобиля, о котором необходимо изменить информацию" << endl;
	cin >> catalogIndex;
	choice = subMenu();
	switch (choice)
	{
		case 1:
			cout << "\nВведите год выпуска: ";
			cin >> year;
			array[catalogIndex - 1]->setYear(year);
			break;
		case 2:
			cout << "\nВведите пробег в км: ";
			cin >> mileage;
			array[catalogIndex - 1]->setMileage(mileage);
			break;
		case 3:
			cout << "\nВведите стоимость в $: ";
			cin >> price;
			array[catalogIndex - 1]->setPrice(price);
			break;
		case 4:
			cout << "\nВведите марку: ";
			cin.ignore();
			getline(cin, brand);
			array[catalogIndex - 1]->setBrand(brand);
			break;
		case 5:
			cout << "\nВведите модель: ";
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
		cout << "Автомобилей в каталоге нет" << endl;
		return array;
	}
	int catalogIndex;
	catalogOutput(array, numOfCars);
	cout << "\nВведите индекс автомобиля, который необходимо удалить из каталога" << endl;
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