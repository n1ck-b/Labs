#include "Header.h"

using namespace std;


int mainMenu()
{
	int choice;
	while (true)
	{
		cout << "\n��������� ��������\n1. �������� ����� ����������\n2. ������� �������\n3. �������� ���������� �� ����������\n4. ������� ���������� �� ��������\n5. ����� ���������� �� ���������\n6. �������� 2 ����������\n7. ��������� ����������" << endl;
		cout << "\n�������� ����� ����: ";
		cin >> choice;
		if (cin.fail() || choice <= 0 || choice > 7)
		{
			cout << "\n\033[31m������������ ����\033[0m" << endl;
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
		cout << "\n������� ����� ����" << endl;
		cin >> choice;
		if (cin.fail() || choice <= 0 || choice > 5)
		{
			cout << "\n\033[31m������������ ����\033[0m" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
		{
			return choice;
		}
	}
}
void writeToFile(List& list)
{
	ofstream file;
	file.open("Cars.txt", ofstream::app);
	if (!file.is_open())
	{
		cout << "�� ������� ������� ���� � �������" << endl;
		return;
	}
	int index = list.getNum() - 1;
	Car car = list[index]->car;
	file << car.getYear() << "\t" << car.getMile() << "\t" << car.getPrice() << "\t" << car.getBrand() << "\t" << car.getModel() << "\n";
	file.close();
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
	writeToFile(list);
}
void catalogOutput(List& list)
{
	if (list.isEmpty() == 1)
	{
		cout << "\n\033[31m����������� � �������� ���\033[0m" << endl;
		return;
	}
	list.print();
}
void updateCarInfo(List& list)
{
	if (list.isEmpty() == 1)
	{
		cout << "\033[31m����������� � �������� ���\033[0m" << endl;
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
	if (catalogIndex > list.getNum())
	{
		cout << "\033[31m������ ������� �� ����������\033[0m" << endl;
		return;
	}
	choice = subMenu();
	switch (choice)
	{
	case 1:
		cout << "\n������� ��� �������: ";
		cin >> year;
		list[catalogIndex - 1]->car.setYear(year);
		break;
	case 2:
		cout << "\n������� ������ � ��: ";
		cin >> mileage;
		list[catalogIndex - 1]->car.setMileage(mileage);
		break;
	case 3:
		cout << "\n������� ��������� � $: ";
		cin >> price;
		list[catalogIndex - 1]->car.setPrice(price);
		break;
	case 4:
		cout << "\n������� �����: ";
		cin.ignore();
		getline(cin, brand);
		list[catalogIndex - 1]->car.setBrand(brand);
		break;
	case 5:
		cout << "\n������� ������: ";
		cin.ignore();
		getline(cin, model);
		list[catalogIndex - 1]->car.setModel(model);
		break;
	default:
		return;
	}
	rewriteToFile(list);
}
void rewriteToFile(List& list)
{
	ofstream file;
	file.open("Cars.txt");
	if (!file.is_open())
	{
		cout << "�� ������� ������� ���� � �������" << endl;
		return;
	}
	Car car;
	for (int i = 0; i < list.getNum(); i++)
	{
		car = list[i]->car;
		file << car.getYear() << "\t" << car.getMile() << "\t" << car.getPrice() << "\t" << car.getBrand() << "\t" << car.getModel() << "\n";
	}
	file.close();
}
void deleteOneCar(List& list)
{
	if (list.isEmpty() == 1)
	{
		cout << "\033[31m����������� � �������� ���\033[0m" << endl;
		return;
	}
	int catalogIndex;
	catalogOutput(list);
	cout << "\n������� ������ ����������, ������� ���������� ������� �� ��������" << endl;
	cin >> catalogIndex;
	if (catalogIndex > list.getNum())
	{
		cout << "\033[31m������ ������� �� ����������\033[0m" << endl;
		return;
	}
	list.removeByIndex(catalogIndex - 1);
	rewriteToFile(list);
}
void searchForCar(List& list)
{
	if (list.isEmpty() == 1)
	{
		cout << "\033[31m����������� � �������� ���\033[0m" << endl;
		return;
	}
	int year[2];
	int mileage[2];
	float price[2];
	string brand;
	string model;
	int choice = subMenu();
	switch (choice)
	{
	case 1:
		cout << "������� ��� ������� ���������� (�� � ��): ";
		cin >> year[0] >> year[1];
		break;
	case 2:
		cout << "������� ������ � �� (�� � ��): ";
		cin >> mileage[0] >> mileage[1];
		break;
	case 3:
		cout << "������� �������� ��������� $(�� � ��): ";
		cin >> price[0] >> price[1];
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
	list.searchByParameter(choice, year, mileage, price, brand, model);
}
bool matchCars(const Car& current, int choice, const int* year, const int* mileage, const float* price, const string& brand, const string& model)
{
	switch (choice)
	{
	case 1:
		return current.getYear() >= year[0] && current.getYear() <= year[1];
	case 2:
		return current.getMile() >= mileage[0] && current.getMile() <= mileage[1];
	case 3:
		return current.getPrice() >= price[0] && current.getPrice() <= price[1];
	case 4:
		return current.getBrand() == brand;
	case 5:
		return current.getModel() == model;
	default:
		return false;
	}
}
void readFromFile(List& list)
{
	ifstream file;
	file.open("Cars.txt", ifstream::app);
	if (!file.is_open())
	{
		cout << "�� ������� ������� ���� � �������" << endl;
		return;
	}
	if (file.peek() == EOF)
	{
		cout << "\033[33m���� ���� ��� �� �� ��� ������, ������� ������ �����\033[0m" << endl;
		file.close();
		return;
	}
	int year;
	int mile;
	float price;
	string brand;
	string model;
	while (file >> year >> mile >> price)
	{
		file.ignore(1, '\t');
		getline(file, brand, '\t');
		getline(file, model);
		list.push(year, mile, price, brand, model);
	}
	file.close();
}
void compareAndPrintForYear(int a, int b)
{
	cout << "��� �������: ";
	if (a > b)
	{
		cout.width(12);
		cout << "\033[32m" << a;
		cout.width(27);
		cout << "\033[31m" << b << "\033[0m" << endl;
	}
	else
	{
		cout.width(12);
		cout << "\033[31m" << a;
		cout.width(27);
		cout << "\033[32m" << b << "\033[0m" << endl;
	}
}
void compareAndPrintForMile(int a, int b)
{
	cout << "������:     ";
	if (a < b)
	{
		cout.width(12);
		cout << "\033[32m" << a;
		cout.width(27);
		cout << "\033[31m" << b << "\033[0m" << endl;
	}
	else
	{
		cout.width(12);
		cout << "\033[31m" << a;
		cout.width(27);
		cout << "\033[32m" << b << "\033[0m" << endl;
	}
}
void compareAndPrintForPrice(float a, float b)
{
	cout << "��������� $: ";
	if (a < b)
	{
		cout.width(12);
		cout << "\033[32m" << a;
		cout.width(27);
		cout << "\033[31m" << b << "\033[0m" << endl;
	}
	else
	{
		cout.width(12);
		cout << "\033[31m" << a;
		cout.width(27);
		cout << "\033[32m" << b << "\033[0m" << endl;
	}
}
void compareCarsToParameters(const Node& car1, const Node& car2)
{
	std::cout << "��������� ���������:\n" << std::endl;
	std::cout << "\t\t1-�� ����������\t\t  2-�� ����������" << std::endl;
	compareAndPrintForYear(car1.car.getYear(), car2.car.getYear());
	compareAndPrintForMile(car1.car.getMile(), car2.car.getMile());
	compareAndPrintForPrice(car1.car.getPrice(), car2.car.getPrice());
	std::cout << "�����:       ";
	std::cout.width(12);
	std::cout << car1.car.getBrand();
	std::cout.width(25);
	std::cout << car2.car.getBrand() << std::endl;
	std::cout << "������:      ";
	std::cout.width(12);
	std::cout << car1.car.getModel();
	std::cout.width(25);
	std::cout << car2.car.getModel() << std::endl;
}
void compareCars(List& list)
{
	if (list.isEmpty() == 1)
	{
		cout << "\033[31m����������� � �������� ���\033[0m" << endl;
		return;
	}
	catalogOutput(list);
	int index1;
	int index2;
	cout << "\n������� ������� �����������, ������� ����� ��������" << endl;
	cin >> index1 >> index2;
	if (index1 > list.getNum() || index2 > list.getNum() || index1 == index2)
	{
		cout << "\033[31m������ �������� ������\033[0m" << endl;
		return;
	}
	if (*list[index1 - 1] == *list[index2 - 1] == 1)
		cout << "������ ��������� �� ����������� ����������" << endl;
	else
	{
		cout << "������ �� ���������" << endl;
		compareCarsToParameters(*list[index1 - 1], *list[index2 - 1]);
	}
}