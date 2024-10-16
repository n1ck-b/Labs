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
		cout << "\nВыберите параметр для поиска:" << endl;
		cout << "  1. Год выпуска \n  2. Пробег\n  3. Стоимость в $\n  4. Марка\n  5. Модель\n  6. Объем топливного бака\n  7. Емкость батареи\n  8. Тип гибрида" << endl;
		cout << "\nВведите пункт меню" << endl;
		cin >> choice;
		if (cin.fail() || choice <= 0 || choice > 8)
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
void carDataInput(bool isFull, int& type, int& year, int& mileage, float& price, string& brand, string& model)
{
	if (isFull)
	{
		cout << "\nВыберите тип двигателя:\n1. Электрический\n2. Внутреннего сгорания\n3. Гибридный" << endl;
		cin >> type;
	}
	cout << "Введите год выпуска автомобиля: ";
	cin >> year;
	cout << "Введите пробег в км: ";
	cin >> mileage;
	cout << "Введите стоимость $: ";
	cin >> price;
	cout << "Введите название марки: ";
	cin.ignore();
	getline(cin, brand);
	cout << "Введите название модели: " ;
	getline(cin, model);
}
int tableRowCount(int& count, const string& tableName)
{
	sqlite3* dataBase;
	sqlite3_stmt* stmt;
	sqlite3_open("Cars.db", &dataBase);
	string sql = "SELECT COUNT(*) FROM " + tableName + ";";
	sqlite3_prepare_v2(dataBase, sql.c_str(), -1, &stmt, nullptr);
	sqlite3_step(stmt);
	count = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);
	sqlite3_close(dataBase);
	return count;
}
void dbRowsCount(int& hybridCount, int& combustionCount, int& electricCount)
{
	tableRowCount(electricCount, "electric_cars");
	tableRowCount(combustionCount, "combustion_cars");
	tableRowCount(hybridCount, "hybrid_cars");
}
void addOneCar()
{
	int year;
	int mileage;
	int engineType;
	float price;
	string brand;
	string model;
	carDataInput(true, engineType, year, mileage, price, brand, model);
	ElectricEngineCar electricCar;
	CombustionEngineCar combustionCar;
	HybridEngineCar hybridCar;
	switch (engineType)
	{
		case 1:
			float batteryCapacity;
			cout << "Введите емкость аккумулятора: ";
			cin >> batteryCapacity;
			electricCar.addCar(year, mileage, price, brand, model, batteryCapacity);
			break;
		case 2:
			float fuelTankCapacity;
			cout << "Введите объем топливного бака: ";
			cin >> fuelTankCapacity;
			combustionCar.addCar(year, mileage, price, brand, model, fuelTankCapacity);
			break;
		case 3:
			int hybridType;
			cout << "Введите емкость аккумулятора: ";
			cin >> batteryCapacity;
			cout << "Введите объем топливного бака: ";
			cin >> fuelTankCapacity;
			cout << "Выберите тип гибрида:\n0. Последовательный\n1. Параллельный" << endl;
			cin >> hybridType;
			hybridCar.addCar(year, mileage, price, brand, model, batteryCapacity, fuelTankCapacity, hybridType);
			break;
		default:
			return;
	}
}
void catalogOutput()
{
	int electricCount;
	int hybridCount;
	int combustionCount;
	dbRowsCount(hybridCount, combustionCount, electricCount);
	if (electricCount == 0 && hybridCount == 0 && combustionCount == 0)
	{
		cout << "\nАвтомобилей в каталоге нет" << endl;
		return;
	}
	CombustionEngineCar combustionCar;
	combustionCar.print();
	ElectricEngineCar electricCar;
	electricCar.print();
	HybridEngineCar hybridCar;
	hybridCar.print();
}
void checkCatalogIndex(int type, int catalogIndex, int electricCount, int combustionCount, int hybridCount)
{
	switch (type)
	{
	case 1:
		if (catalogIndex > electricCount || catalogIndex <= 0)
		{
			cout << "Такого индекса не существует" << endl;
			return;
		}
		break;
	case 2:
		if (catalogIndex > combustionCount || catalogIndex <= 0)
		{
			cout << "Такого индекса не существует" << endl;
			return;
		}
		break;
	case 3:
		if (catalogIndex > hybridCount || catalogIndex <= 0)
		{
			cout << "Такого индекса не существует" << endl;
			return;
		}
		break;
	default:
		cout << "Некорректный ввод" << endl;
		return;
	}
}
void updateCarInfo()
{
	int electricCount;
	int hybridCount;
	int combustionCount;
	dbRowsCount(hybridCount, combustionCount, electricCount);
	if (electricCount == 0 && hybridCount == 0 && combustionCount == 0)
	{
		cout << "\nАвтомобилей в каталоге нет" << endl;
		return;
	}
	int catalogIndex;
	int year;
	int mileage;
	float price;
	string brand;
	string model;
	catalogOutput();
	int type;
	cout << "\nВыберите тип автомобиля:\n1. Электрический\n2. С ДВС\n3. Гибридный\n";
	cin >> type;
	cout << "Введите индекс автомобиля, о котором необходимо изменить информацию: ";
	cin >> catalogIndex;
	checkCatalogIndex(type, catalogIndex, electricCount, combustionCount, hybridCount);
	cout << "\nВведите новые данные:" << endl;
	carDataInput(false, type, year, mileage, price, brand, model);
	ElectricEngineCar electricCar;
	CombustionEngineCar combustionCar;
	HybridEngineCar hybridCar;
	switch (type)
	{
	case 1:
		float batteryCapacity;
		cout << "\nВведите емкость аккумулятора: ";
		cin >> batteryCapacity;
		electricCar.updateCar(catalogIndex, year, mileage, price, brand, model, batteryCapacity);
		break;
	case 2:
		float fuelTankCapacity;
		cout << "\nВведите объем топливного бака: ";
		cin >> fuelTankCapacity;
		combustionCar.updateCar(catalogIndex, year, mileage, price, brand, model, fuelTankCapacity);
		break;
	case 3:
		int hybridType;
		cout << "\nВведите емкость аккумулятора: ";
		cin >> batteryCapacity;
		cout << "\nВведите объем топливного бака: ";
		cin >> fuelTankCapacity;
		cout << "\nВыберите тип гибрида:\n0. Последовательный\n1. Параллельный\n" << endl;
		cin >> hybridType;
		hybridCar.updateCar(catalogIndex, year, mileage, price, brand, model, batteryCapacity, fuelTankCapacity, hybridType);
		break;
	default:
		return;
	}
}
void deleteOneCar()
{
	int electricCount;
	int hybridCount;
	int combustionCount;
	dbRowsCount(hybridCount, combustionCount, electricCount);
	if (electricCount == 0 && hybridCount == 0 && combustionCount == 0)
	{
		cout << "\nАвтомобилей в каталоге нет" << endl;
		return;
	}
	int catalogIndex;
	catalogOutput();
	int type;
	cout << "\nВыберите тип автомобиля:\n1. Электрический\n2. С ДВС\n3. Гибридный\n";
	cin >> type;
	cout << "\nВведите индекс автомобиля, который необходимо удалить: ";
	cin >> catalogIndex;
	ElectricEngineCar electricCar;
	CombustionEngineCar combustionCar;
	HybridEngineCar hybridCar;
	checkCatalogIndex(type, catalogIndex, electricCount, combustionCount, hybridCount);
	switch (type)
	{
	case 1:
		electricCar.deleteCar(catalogIndex);
		break;
	case 2:
		combustionCar.deleteCar(catalogIndex);
		break;
	case 3:
		hybridCar.deleteCar(catalogIndex);
		break;
	default:
		break;
	}
}
void searchForCarInDB(const string& tableName, const string& parameter1, const string& parameter2, const string& fieldName, int type)
{
	sqlite3* dataBase;
	string sql;
	int error = sqlite3_open("Cars.db", &dataBase);
	if (error)
	{
		cout << "Не удалось открыть базу данных" << sqlite3_errmsg(dataBase) << endl;
		return;
	}
	if (parameter2 != " ")
	{
		sql = "SELECT * FROM " + tableName +
			  " WHERE " + fieldName + " >= " + parameter1 + " AND " + fieldName + " <= " + parameter2 + ";";
	}
	else
	{
		sql = "SELECT * FROM " + tableName +
			  " WHERE " + fieldName + " = '" + parameter1 + "';";
	}
	cout << sql << endl;
	const char* SQL = sql.c_str();
	sqlite3_stmt* stmt;
	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
	if (error != SQLITE_OK)
	{
		std::cout << "Не удалось выполнить запрос." << sqlite3_errmsg(dataBase) << std::endl;
		return;
	}
	int i = 1;
	std::cout << "\nРезультаты поиска:" << std::endl;
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		std::cout << "\n" << i << "-й автомобиль:\n" << std::endl;
		std::cout << "  Год выпуска: " << sqlite3_column_int(stmt, 1) << std::endl;
		std::cout << "  Пробег в км: " << sqlite3_column_int(stmt, 2) << std::endl;
		std::cout << "  Стоимость в $: " << sqlite3_column_double(stmt, 3) << std::endl;
		std::cout << "  Марка: " << sqlite3_column_text(stmt, 4) << std::endl;
		std::cout << "  Модель: " << sqlite3_column_text(stmt, 5) << std::endl;
		if (type == 2 || type == 3)
			std::cout << "  Объем топливного бака: " << sqlite3_column_double(stmt, 6) << std::endl;
		if(type == 1 || type == 3)
			std::cout << "  Емкость аккумулятора: " << sqlite3_column_double(stmt, 7) << std::endl;
		if (type == 3)
		{
			int hybridType = sqlite3_column_int(stmt, 8);
			if (hybridType == 0)
				std::cout << "  Тип гибридного двигателя: последовательный" << std::endl;
			else
				std::cout << "  Тип гибридного двигателя: параллельный" << std::endl;
		}
		i++;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(dataBase);
}
template <typename T>
void inputDataInRange(const string& msg, T& min, T& max)
{
	cout << msg << " (от и до): ";
	cin >> min >> max;
	while (min < 0 || max < 0)
	{
		cout << "Некорректный ввод\n" << msg << " (от и до): ";
		cin >> min >> max;
	}
}
void searchForCar()
{
	int electricCount;
	int hybridCount;
	int combustionCount;
	int type;
	ostringstream oss;
	string str;
	dbRowsCount(hybridCount, combustionCount, electricCount);
	if (electricCount == 0 && hybridCount == 0 && combustionCount == 0)
	{
		cout << "\nАвтомобилей в каталоге нет" << endl;
		return;
	}
	vector <int> vectorInt(2);
	string brand;
	string model;
	int hybridType;
	vector <float> vectorFloat(2);
	cout << "\nВыберите тип автомобиля:\n1. Электрический\n2. С ДВС\n3. Гибридный\n";
	cin >> type;
	vector <string> vectorStr(4); //0 - tableName, 1 - parameterForSearchInDB1, 2 - parameterForSearchInDB2, 3 - fieldName
	vectorStr[2] = " ";
	switch (type)
	{
	case 1:
		vectorStr[0] = "electric_cars";
		break;
	case 2:
		vectorStr[0] = "combustion_cars";
		break;
	case 3:
		vectorStr[0] = "hybrid_cars";
		break;
	default:
		cout << "Такого типа не существует\n" << endl;
		return;
	}
	int choice = subMenu();
	switch (choice)
	{
	case 1:
		inputDataInRange("Введите год выпуска автомобиля", vectorInt[0], vectorInt[1]);
		vectorStr[3] = "year_of_production";
		vectorStr[1] = to_string(vectorInt[0]);
		vectorStr[2] = to_string(vectorInt[1]);
		break;
	case 2:
		inputDataInRange("Введите пробег в км", vectorInt[0], vectorInt[1]);
		vectorStr[3] = "mileage";
		vectorStr[1] = to_string(vectorInt[0]);
		vectorStr[2] = to_string(vectorInt[1]);
		break;
	case 3:
		inputDataInRange("Введите диапозон стоимости $", vectorFloat[0], vectorFloat[1]);
		vectorStr[3] = "price";
		oss << vectorFloat[0];
		str = oss.str();
		vectorStr[1] = str;
		oss << vectorFloat[1];
		str.clear();
		str = oss.str();
		vectorStr[2] = str;
		break;
	case 4:
		cout << "Введите название марки: ";
		cin.ignore();
		getline(cin, brand);
		vectorStr[3] = "brand";
		vectorStr[1] = brand;
		break;
	case 5:
		cout << "Введите название модели: ";
		cin.ignore();
		getline(cin, model);
		vectorStr[3] = "model";
		vectorStr[1] = model;
		break;
	case 6:
		if (type == 1)
		{
			cout << "У электрической машины нет топливного бака\n" << endl;
			return;
		}
		inputDataInRange("Введите объем топливного бака", vectorFloat[0], vectorFloat[1]);
		vectorStr[3] = "fuel_tank_capacity";
		oss << vectorFloat[0];
		str.clear();
		str = oss.str();
		vectorStr[1] = str;
		oss << vectorFloat[1];
		str.clear();
		str = oss.str();
		vectorStr[2] = str;
		break;
	case 7:
		if (type == 2)
		{
			cout << "У машины с ДВС нет батареи\n" << endl;
			return;
		}
		inputDataInRange("Введите емкость аккумулятора", vectorFloat[0], vectorFloat[1]);
		vectorStr[3] = "battery_capacity";
		oss << vectorFloat[0];
		str.clear();
		str = oss.str();
		vectorStr[1] = str;
		oss << vectorFloat[1];
		str.clear();
		str = oss.str();
		vectorStr[2] = str;
		break;
	case 8:
		if (type != 3)
		{
			cout << "У выбранного типа автомобиля нет гибридного двигателя\n" << endl;
			return;
		}
		cout << "Выберите тип гибрида:\n0. Последовательный\n1. Параллельный\n" << endl;
		cin >> hybridType;
		while (hybridType != 0 && hybridType != 1)
		{
			cout << "Некорректный ввод\nВыберите тип гибрида:\n0. Последовательный\n1. Параллельный\n" << endl;
			cin >> hybridType;
		}
		vectorStr[3] = "hybrid_type";
		vectorStr[1] = to_string(hybridType);
		break;
	default:
		break;
	}
	searchForCarInDB(vectorStr[0], vectorStr[1], vectorStr[2], vectorStr[3], type);
}
template <typename T> 
void compareAndPrint(T val1, T val2, bool isReverse, const string& msg)
{
	cout << msg;
	switch (isReverse)
	{
	case 1:
		if (val1 > val2)
		{
			cout.width(12);
			cout << val1;
			cout.width(27);
			cout << val2 << endl;
		}
		else
		{
			cout.width(12);
			cout << "" << val1;
			cout.width(27);
			cout << val2 << endl;
		}
		break;
	case 0:
		if (val1 < val2)
		{
			cout.width(12);
			cout << val1;
			cout.width(27);
			cout << val2 << endl;
		}
		else
		{
			cout.width(12);
			cout << val1;
			cout.width(27);
			cout << val2 << endl;
		}
		break;
	default:
		break;
	}
}
void compareCarsToParameters(int type, vector <int> vectorInt, vector <float> vectorFloat, vector <string> vectorStr)
{
	std::cout << "Результат сравнения:\n" << std::endl;
	std::cout << "\t\t1-ый автомобиль\t\t  2-ой автомобиль" << std::endl;
	compareAndPrint(vectorInt[0], vectorInt[1], true, "Год выпуска:  ");
	compareAndPrint(vectorInt[2], vectorInt[3], false, "Пробег:     ");
	compareAndPrint(vectorFloat[0], vectorFloat[1], false, "Стоимость $: ");
	std::cout << "Марка:       ";
	std::cout.width(12);
	std::cout << vectorStr[0];
	std::cout.width(25);
	std::cout << vectorStr[1];
	std::cout << "\nМодель:      ";
	std::cout.width(12);
	std::cout << vectorStr[2];
	std::cout.width(25);
	std::cout << vectorStr[3] << std::endl;
	switch (type)
	{
	case 1:
		compareAndPrint(vectorFloat[2], vectorFloat[3], false, "Емкость батареи:");
		break;
	case 2:
		compareAndPrint(vectorFloat[2], vectorFloat[3], true, "Объем бака:     ");
		break;
	case 3:
		compareAndPrint(vectorFloat[2], vectorFloat[3], false, "Емкость батареи:");
		compareAndPrint(vectorFloat[4], vectorFloat[5], true, "Объем бака:     ");
		break;
	default:
		break;
	}
}
void compareCars()
{
	int electricCount;
	int hybridCount;
	int combustionCount;
	dbRowsCount(hybridCount, combustionCount, electricCount);
	ElectricEngineCar electricCar;
	CombustionEngineCar combustionCar;
	HybridEngineCar hybridCar;
	vector <int> vectorInt(6); //0 - year1, 1 - year2, 2 - mileage1, 3 - mileage2, 4 - hybridType1, 5 - hybridType2
	vector <float> vectorFloat(6); //0 - price1, 1 - price2, 2 - batteryCapacity1, 3 - batteryCapacity2, 4 - fuelTankCapacity1, 5 - fuelTankCapacity2
	vector <string> vectorStr(4); //0 - brand1, 1 - brand2, 2 - model1, 3 - model2
	if (electricCount == 0 && hybridCount == 0 && combustionCount == 0)
	{
		cout << "\nАвтомобилей в каталоге нет" << endl;
		return;
	}
	catalogOutput();
	int index1;
	int index2;
	int type;
	cout << "\nВыберите тип двигателя автомобилей:\n1. Электрический\n2. С ДВС\n3. Гибридный\n";
	cin >> type;
	cout << "\nВведите индексы автомобилей, которые нужно сравнить" << endl;
	cin >> index1 >> index2;
	switch (type)
	{
		case 1:
			if (index1 > electricCount || index2 > electricCount)
			{
				cout << "Введен неверный индекс" << endl;
				return;
			}
			electricCar.getCar(index1, vectorInt[0], vectorInt[2], vectorFloat[0], vectorStr[0], vectorStr[2], vectorFloat[2]);
			electricCar.getCar(index2, vectorInt[1], vectorInt[3], vectorFloat[1], vectorStr[1], vectorStr[3], vectorFloat[3]);
			break;
		case 2:
			if (index1 > combustionCount || index2 > combustionCount)
			{
				cout << "Введен неверный индекс" << endl;
				return;
			}
			combustionCar.getCar(index1, vectorInt[0], vectorInt[2], vectorFloat[0], vectorStr[0], vectorStr[2], vectorFloat[2]);
			combustionCar.getCar(index2, vectorInt[1], vectorInt[3], vectorFloat[1], vectorStr[1], vectorStr[3], vectorFloat[3]);
			break;
		case 3:
			if (index1 > hybridCount || index2 > hybridCount)
			{
				cout << "Введен неверный индекс" << endl;
				return;
			}
			hybridCar.getCar(index1, vectorInt[0], vectorInt[2], vectorFloat[0], vectorStr[0], vectorStr[2], vectorFloat[2], vectorFloat[4], vectorInt[4]);
			hybridCar.getCar(index2, vectorInt[1], vectorInt[3], vectorFloat[1], vectorStr[1], vectorStr[3], vectorFloat[3], vectorFloat[5], vectorInt[5]);
			break;
		default:
			cout << "\nТакого типа не существует" << endl;
			return;
	}
	compareCarsToParameters(type, vectorInt, vectorFloat, vectorStr);
}