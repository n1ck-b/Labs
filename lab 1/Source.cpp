#include "Header.h"

using namespace std;


int mainMenu()
{
	int choice;
	while (true)
	{
		cout << "\n��������� ��������\n1. �������� ����� ����������\n2. ������� �������\n3. �������� ���������� �� ����������\n4. ������� ���������� �� ��������\n5. ����� ���������� �� ���������\n6. ��������� ����������\n" << endl;
		cout << "�������� ����� ����: ";
		cin >> choice;
		if (cin.fail() || choice <= 0 || choice > 6)
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
		cout << "�������� �������� ��� ���������/������:" << endl;
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
void addOneCar(List& list)
{
	int year;
	int mileage;
	float price;
	string brand;
	string model;
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
	list.push(year, mileage, price, brand, model);
}
void catalogOutput(List& list)
{
	if (list.isEmpty() == 1)
	{
		cout << "\n����������� � �������� ���" << endl;
		return;
	}
	list.print();
}
void updateCarInfo(List& list)
{
	if (list.isEmpty() == 1)
	{
		cout << "����������� � �������� ���" << endl;
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
	cout << "\n������� ������ ����������, � ������� ���������� �������� ����������" << endl;
	cin >> catalogIndex;
	if (catalogIndex > list.getNum() + 1)
	{
		cout << "������ ������� �� ����������" << endl;
		return;
	}
	choice = subMenu();
	switch (choice)
	{
	case 1:
		cout << "\n������� ��� �������: ";
		cin >> year;
		list[catalogIndex - 1]->setYear(year);
		break;
	case 2:
		cout << "\n������� ������ � ��: ";
		cin >> mileage;
		list[catalogIndex - 1]->setMileage(mileage);
		break;
	case 3:
		cout << "\n������� ��������� � $: ";
		cin >> price;
		list[catalogIndex - 1]->setPrice(price);
		break;
	case 4:
		cout << "\n������� �����: ";
		cin.ignore();
		getline(cin, brand);
		list[catalogIndex - 1]->setBrand(brand);
		break;
	case 5:
		cout << "\n������� ������: ";
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
		cout << "����������� � �������� ���" << endl;
		return;
	}
	int catalogIndex;
	catalogOutput(list);
	cout << "\n������� ������ ����������, ������� ���������� ������� �� ��������" << endl;
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
			cout << "������� ��� ������� ����������: ";
			cin >> year;
			break;
		case 2:
			cout << "������� ������ � ��: ";
			cin >> mileage;
			break;
		case 3:
			cout << "������� �������� ��������� $(�� � ��): ";
			cin >> priceLow >> priceHigh;
			break;
		case 4:
			cout << "������� �������� �����: ";
			cin.ignore();
			getline(cin, brand);
			break;
		case 5:
			cout << "������� �������� ������: ";
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