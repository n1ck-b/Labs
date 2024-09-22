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
List::List()
{
	first = nullptr;
	last = nullptr;
	num = 0;
}
List::~List()
{
	for (int i = 0; i < num; i++)
	{
		removeByIndex(i);
	}
}
int List::GetNum() const
{
	return num;
}
bool List::isEmpty() const
{
	return first == nullptr;
}
void List::push(int year, int mileage, float price, const string& brand, const string& model)
{
	Node* temp = new Node;
	if (isEmpty() == 1)
	{
		first = temp;
		last = temp;
		temp->setObject(year, mileage, price, brand, model);
		return;
	}
	last->next = temp;
	last = temp;
	last->setObject(year, mileage, price, brand, model);
	num++;
}
void List::print()
{
	Node* temp = first;
	int i = 0;
	while (temp != nullptr)
	{
		cout << "\n" << i + 1 << "-й автомобиль:" << endl;
		temp->readObject();
		temp = temp->next;
		i++;
	}
}
void List::removeByIndex(int index)
{
	Node* temp = first;
	for (int i = 0; i < index; i++)
	{
		temp = temp->next;
	}
	if (temp == first)
	{
		first = first->next;
		delete temp;
		num--;
		return;
	}
	if (temp == last)
	{
		Node* temp1 = first;
		while (temp1->next != last)
			temp1 = temp1->next;
		temp1->next = nullptr;
		last = temp1;
		delete temp;
		num--;
		return;
	}
	Node* temp1 = first;
	while (temp1->next != temp)
		temp1 = temp1->next;
	temp1->next = temp->next;
	delete temp;
	num--;
}
Node* List::operator[] (const int index)
{
	if (isEmpty() == 1)
		return nullptr;
	Node* temp = first;
	for (int i = 0; i < index; i++)
	{
		temp = temp->next;
	}
	return temp;
}
void List::searchByParameter(int choice, int year, int mileage, float priceLow, float priceHigh, const string& brand, const string& model)
{
	Node* temp = first;
	int flag = 0;
	switch (choice)
	{
		case 1:
			cout << "Поиск по году выпуска:\n" << endl;
			while (temp != nullptr)
			{
				if (temp->GetYear() == year)
				{
					cout << flag + 1 << "-й автомобиль:" << endl;
					temp->readObject();
					flag++;
				}
				temp = temp->next;
			}
			if (temp == nullptr && flag == 0)
			{
				cout << "Автомобилей с таким годом выпуска не найдено" << endl;
			}
			break;
		case 2:
			cout << "Поиск по пробегу:\n" << endl;
			while (temp != nullptr)
			{
				if (temp->GetMileage() == mileage)
				{
					cout << flag + 1 << "-й автомобиль:" << endl;
					temp->readObject();
					flag++;
				}
				temp = temp->next;
			}
			if (temp == nullptr && flag == 0)
			{
				cout << "Автомобилей с таким пробегом не найдено" << endl;
			}
			break;
		case 3:
			cout << "Поиск по диапозону стоимости:\n" << endl;
			while (temp != nullptr)
			{
				if (priceLow <= temp->GetPrice() && temp->GetPrice() <= priceHigh)
				{
					cout << flag + 1 << "-й автомобиль:" << endl;
					temp->readObject();
					flag++;
				}
				temp = temp->next;
			}
			if (temp == nullptr && flag == 0)
			{
				cout << "Автомобилей с таким диапозоном цены не найдено" << endl;
			}
			break;
		case 4:
			cout << "Поиск по марке:\n" << endl;
			while (temp != nullptr)
			{
				if (temp->GetBrand() == brand)
				{
					cout << flag + 1 << "-й автомобиль:" << endl;
					temp->readObject();
					flag++;
				}
				temp = temp->next;
			}
			if (temp == nullptr && flag == 0)
			{
				cout << "Автомобилей такой марки не найдено" << endl;
			}
			break;
		case 5:
			cout << "Поиск по модели:\n" << endl;
			while (temp != nullptr)
			{
				if (temp->GetModel() == model)
				{
					cout << flag + 1 << "-й автомобиль:" << endl;
					temp->readObject();
					flag++;
				}
				temp = temp->next;
			}
			if (temp == nullptr && flag == 0)
			{
				cout << "Автомобилей такой модели не найдено" << endl;
			}
			break;
		default:
			return;
	}
}
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
	cout << "  Год выпуска: " << yearOfProduction << endl;
	cout << "  Пробег в км: " << mileage << endl;
	cout << "  Стоимость в $: " << price << endl;
	cout << "  Марка: " << brand << endl;
	cout << "  Модель: " << model << endl;
}
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
	if (catalogIndex > list.GetNum())
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
	if (list.GetNum() == 0)
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