#include "Header.h"

using namespace std;


int mainMenu()
{
	int choice;
	while (true)
	{
		cout << "\nВозможные действия\n1. Добавить новый автомобиль\n2. Вывести каталог\n3. Изменить информацию об автомобиле\n4. Удалить автомобиль из каталога\n5. Найти автомобиль по параметру\n6. Сравнить 2 автомобиля\n7. Завершить выполнение" << endl;
		cout << "\nВыберите пункт меню: ";
		cin >> choice;
		if (cin.fail() || choice <= 0 || choice > 7)
		{
			cout << "\n\033[31mНекорректный ввод\033[0m" << endl;
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
		cout << "\nВведите пункт меню" << endl;
		cin >> choice;
		if (cin.fail() || choice <= 0 || choice > 5)
		{
			cout << "\n\033[31mНекорректный ввод\033[0m" << endl;
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
		cout << "Не удалось открыть файл с данными" << endl;
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
	writeToFile(list);
}
void catalogOutput(List& list)
{
	if (list.isEmpty() == 1)
	{
		cout << "\n\033[31mАвтомобилей в каталоге нет\033[0m" << endl;
		return;
	}
	list.print();
}
void updateCarInfo(List& list)
{
	if (list.isEmpty() == 1)
	{
		cout << "\033[31mАвтомобилей в каталоге нет\033[0m" << endl;
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
	if (catalogIndex > list.getNum())
	{
		cout << "\033[31mТакого индекса не существует\033[0m" << endl;
		return;
	}
	choice = subMenu();
	switch (choice)
	{
	case 1:
		cout << "\nВведите год выпуска: ";
		cin >> year;
		list[catalogIndex - 1]->car.setYear(year);
		break;
	case 2:
		cout << "\nВведите пробег в км: ";
		cin >> mileage;
		list[catalogIndex - 1]->car.setMileage(mileage);
		break;
	case 3:
		cout << "\nВведите стоимость в $: ";
		cin >> price;
		list[catalogIndex - 1]->car.setPrice(price);
		break;
	case 4:
		cout << "\nВведите марку: ";
		cin.ignore();
		getline(cin, brand);
		list[catalogIndex - 1]->car.setBrand(brand);
		break;
	case 5:
		cout << "\nВведите модель: ";
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
		cout << "Не удалось открыть файл с данными" << endl;
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
		cout << "\033[31mАвтомобилей в каталоге нет\033[0m" << endl;
		return;
	}
	int catalogIndex;
	catalogOutput(list);
	cout << "\nВведите индекс автомобиля, который необходимо удалить из каталога" << endl;
	cin >> catalogIndex;
	if (catalogIndex > list.getNum())
	{
		cout << "\033[31mТакого индекса не существует\033[0m" << endl;
		return;
	}
	list.removeByIndex(catalogIndex - 1);
	rewriteToFile(list);
}
void searchForCar(List& list)
{
	if (list.isEmpty() == 1)
	{
		cout << "\033[31mАвтомобилей в каталоге нет\033[0m" << endl;
		return;
	}
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
		return current->car.getYear() == year;
	case 2:
		return current->car.getMile() == mileage;
	case 3:
		return current->car.getPrice() >= priceLow && current->car.getPrice() <= priceHigh;
	case 4:
		return current->car.getBrand() == brand;
	case 5:
		return current->car.getModel() == model;
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
		cout << "Не удалось открыть файл с данными" << endl;
		return;
	}
	if (file.peek() == EOF)
	{
		cout << "\033[33mФайл пуст или же не был найден, поэтому создан новый\033[0m" << endl;
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
	cout << "Год выпуска: ";
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
	cout << "Пробег:     ";
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
	cout << "Стоимость $: ";
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
void operator == (const Node& car1, const Node& car2)
{
	cout << "Результат сравнения:\n" << endl;
	cout << "\t\t1-ый автомобиль\t\t  2-ой автомобиль" << endl;
	compareAndPrintForYear(car1.car.getYear(), car2.car.getYear());
	compareAndPrintForMile(car1.car.getMile(), car2.car.getMile());
	compareAndPrintForPrice(car1.car.getPrice(), car2.car.getPrice());
	cout << "Марка:       ";
	cout.width(12);
	cout << car1.car.getBrand();
	cout.width(25);
	cout << car2.car.getBrand() << endl;
	cout << "Модель:      ";
	cout.width(12);
	cout << car1.car.getModel();
	cout.width(25);
	cout << car2.car.getModel() << endl;
}
void compareCars(List& list)
{
	if (list.isEmpty() == 1)
	{
		cout << "\033[31mАвтомобилей в каталоге нет\033[0m" << endl;
		return;
	}
	catalogOutput(list);
	int index1;
	int index2;
	cout << "\nВведите индексы автомобилей, которые нужно сравнить" << endl;
	cin >> index1 >> index2;
	if (index1 > list.getNum() || index2 > list.getNum() || index1 == index2)
	{
		cout << "\033[31mВведен неверный индекс\033[0m" << endl;
		return;
	}
	*list[index1 - 1] == *list[index2 - 1];
}