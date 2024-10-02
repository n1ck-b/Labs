#include "Header.h"

using namespace std;


int mainMenu()
{
	int choice;
	while (true)
	{
		cout << "\nВозможные действия\n1. Добавить новый автомобиль\n2. Вывести каталог\n3. Изменить информацию об автомобиле\n4. Удалить автомобиль из каталога\n5. Найти автомобиль по параметру\n6. Завершить выполнение\n" << endl;
		cout << "Выберите пункт меню: ";
		cin >> choice;
		if (cin.fail() || choice <= 0 || choice > 6)
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
		cout << "Выберите параметр для изменения/поиска:" << endl;
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
void addOneCar(List& list)
{
	int year;
	int mileage;
	float price;
	string brand;
	string model;
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
	list.push(year, mileage, price, brand, model);
}
void catalogOutput(List& list)
{
	if (list.isEmpty() == 1)
	{
		cout << "\nАвтомобилей в каталоге нет" << endl;
		return;
	}
	list.print();
}
void updateCarInfo(List& list)
{
	if (list.isEmpty() == 1)
	{
		cout << "Автомобилей в каталоге нет" << endl;
		return;
	}
	int catalogIndex;
	int choice;
	int year;
	int mileage;
	float price;
	string brand;
	string model;
	catalogOutput(list);
	cout << "\nВведите индекс автомобиля, о котором необходимо изменить информацию" << endl;
	cin >> catalogIndex;
	if (catalogIndex > list.getNum() + 1)
	{
		cout << "Такого индекса не существует" << endl;
		return;
	}
	choice = subMenu();
	switch (choice)
	{
	case 1:
		cout << "\nВведите год выпуска: ";
		cin >> year;
		list[catalogIndex - 1]->setYear(year);
		break;
	case 2:
		cout << "\nВведите пробег в км: ";
		cin >> mileage;
		list[catalogIndex - 1]->setMileage(mileage);
		break;
	case 3:
		cout << "\nВведите стоимость в $: ";
		cin >> price;
		list[catalogIndex - 1]->setPrice(price);
		break;
	case 4:
		cout << "\nВведите марку: ";
		cin.ignore();
		getline(cin, brand);
		list[catalogIndex - 1]->setBrand(brand);
		break;
	case 5:
		cout << "\nВведите модель: ";
		cin.ignore();
		getline(cin, model);
		list[catalogIndex - 1]->setModel(model);
		break;
	default:
		return;
	}
}
void deleteOneCar(List& list)
{
	if (list.getNum() == 0)
	{
		cout << "Автомобилей в каталоге нет" << endl;
		return;
	}
	int catalogIndex;
	catalogOutput(list);
	cout << "\nВведите индекс автомобиля, который необходимо удалить из каталога" << endl;
	cin >> catalogIndex;
	list.removeByIndex(catalogIndex - 1);
}
void searchForCar(List& list)
{
	int year = 0;
	int mileage = 0;
	float priceLow = 0;
	float priceHigh = 0;
	string brand;
	string model;
	int choice = subMenu();
	switch (choice)
	{
		case 1:
			cout << "Введите год выпуска автомобиля: ";
			cin >> year;
			break;
		case 2:
			cout << "Введите пробег в км: ";
			cin >> mileage;
			break;
		case 3:
			cout << "Введите диапозон стоимости $(от и до): ";
			cin >> priceLow >> priceHigh;
			break;
		case 4:
			cout << "Введите название марки: ";
			cin.ignore();
			getline(cin, brand);
			break;
		case 5:
			cout << "Введите название модели: ";
			cin.ignore();
			getline(cin, model);
			break;
		default:
			return;
	}
	list.searchByParameter(choice, year, mileage, priceLow, priceHigh, brand, model);
}
bool match(const Node* current, int choice, int year, int mileage, float priceLow, float priceHigh, const string& brand, const string& model)
{
	switch (choice)
	{
	case 1:
		return current->getYear() == year;
	case 2:
		return current->getMileage() == mileage;
	case 3:
		return current->getPrice() >= priceLow && current->getPrice() <= priceHigh;
	case 4:
		return current->getBrand() == brand;
	case 5:
		return current->getModel() == model;
	default:
		return false;
	}
}