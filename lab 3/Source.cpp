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
		cout << "\n�������� �������� ��� ������:" << endl;
		cout << "  1. ��� ������� \n  2. ������\n  3. ��������� � $\n  4. �����\n  5. ������\n  6. ����� ���������� ����\n  7. ������� �������\n  8. ��� �������" << endl;
		cout << "\n������� ����� ����" << endl;
		cin >> choice;
		if (cin.fail() || choice <= 0 || choice > 8)
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
template <typename T>
void carDataInput(T& carClass)
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
	cout << "������� �������� ������: " ;
	getline(cin, model);
	carClass.setYear(year);
	carClass.setMileage(mileage);
	carClass.setPrice(price);
	carClass.setBrand(brand);
	carClass.setModel(model);
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
	int engineType;
	ElectricEngineCar electricCar;
	CombustionEngineCar combustionCar;
	HybridEngineCar hybridCar;
	cout << "\n�������� ��� ���������:\n1. �������������\n2. ����������� ��������\n3. ���������" << endl;
	cin >> engineType;
	const char* SQL;
	switch (engineType)
	{
		case 1:
			Repository <ElectricEngineCar> repository1;
			carDataInput(electricCar);
			float batteryCapacity;
			cout << "������� ������� ������������: ";
			cin >> batteryCapacity;
			SQL = "INSERT INTO electric_cars (year_of_production, mileage, price, brand, model, battery_capacity)"
				"VALUES (?, ?, ?, ?, ?, ?);";
			repository1.addCar(electricCar, SQL, engineType, 0, batteryCapacity);
			break;
		case 2:
			Repository <CombustionEngineCar> repository2;
			carDataInput(combustionCar);
			float fuelTankCapacity;
			cout << "������� ����� ���������� ����: ";
			cin >> fuelTankCapacity;
			SQL = "INSERT INTO combustion_cars (year_of_production, mileage, price, brand, model, fuel_tank_capacity)"
				"VALUES (?, ?, ?, ?, ?, ?);";
			repository2.addCar(combustionCar, SQL, engineType, fuelTankCapacity);
			break;
		case 3:
			Repository <HybridEngineCar> repository3;
			carDataInput(hybridCar);
			int hybridType;
			cout << "������� ������� ������������: ";
			cin >> batteryCapacity;
			cout << "������� ����� ���������� ����: ";
			cin >> fuelTankCapacity;
			cout << "�������� ��� �������:\n0. ����������������\n1. ������������" << endl;
			cin >> hybridType;
			hybridCar.setHybridType(hybridType);
			SQL = "INSERT INTO hybrid_cars (year_of_production, mileage, price, brand, model, fuel_tank_capacity, battery_capacity, hybrid_type)"
				"VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
			repository3.addCar(hybridCar, SQL, engineType, fuelTankCapacity, batteryCapacity, hybridType);
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
		cout << "\n����������� � �������� ���" << endl;
		return;
	}
	const char* SQL = "SELECT year_of_production, mileage, price, brand, model, fuel_tank_capacity "
		"FROM combustion_cars;";
	Repository <CombustionEngineCar> repository1;
	repository1.print(SQL, 2, "\n���������� � ��� :");
	SQL = "SELECT year_of_production, mileage, price, brand, model, battery_capacity "
		"FROM electric_cars;";
	Repository <ElectricEngineCar> repository2;
	repository2.print(SQL, 1, "\n������������� ����������:");
	SQL = "SELECT year_of_production, mileage, price, brand, model, fuel_tank_capacity, battery_capacity, hybrid_type "
		"FROM hybrid_cars;";
	Repository <HybridEngineCar> repository3;
	repository3.print(SQL, 3, "\n��������� ����������:");
}
void checkCatalogIndex(int type, int catalogIndex, int electricCount, int combustionCount, int hybridCount)
{
	switch (type)
	{
	case 1:
		if (catalogIndex > electricCount || catalogIndex <= 0)
		{
			cout << "������ ������� �� ����������" << endl;
			return;
		}
		break;
	case 2:
		if (catalogIndex > combustionCount || catalogIndex <= 0)
		{
			cout << "������ ������� �� ����������" << endl;
			return;
		}
		break;
	case 3:
		if (catalogIndex > hybridCount || catalogIndex <= 0)
		{
			cout << "������ ������� �� ����������" << endl;
			return;
		}
		break;
	default:
		cout << "������������ ����" << endl;
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
		cout << "\n����������� � �������� ���" << endl;
		return;
	}
	int catalogIndex;
	catalogOutput();
	int type;
	cout << "\n�������� ��� ����������:\n1. �������������\n2. � ���\n3. ���������\n";
	cin >> type;
	cout << "������� ������ ����������, � ������� ���������� �������� ����������: ";
	cin >> catalogIndex;
	checkCatalogIndex(type, catalogIndex, electricCount, combustionCount, hybridCount);
	cout << "\n������� ����� ������:" << endl;
	ElectricEngineCar electricCar;
	CombustionEngineCar combustionCar;
	HybridEngineCar hybridCar;
	const char* SQL;
	switch (type)
	{
	case 1:
		Repository <ElectricEngineCar> rep1;
		carDataInput(electricCar);
		float batteryCapacity;
		cout << "\n������� ������� ������������: ";
		cin >> batteryCapacity;
		SQL = "UPDATE electric_cars SET year_of_production = ?, mileage = ?, price = ?, brand = ?, model = ?, battery_capacity = ? WHERE id = ?;";
		rep1.updateCar(electricCar, catalogIndex, SQL, "electric_cars", type, 0, batteryCapacity);
		break;
	case 2:
		Repository <CombustionEngineCar> rep2;
		carDataInput(combustionCar);
		float fuelTankCapacity;
		cout << "\n������� ����� ���������� ����: ";
		cin >> fuelTankCapacity;
		SQL = "UPDATE combustion_cars SET year_of_production = ?, mileage = ?, price = ?, brand = ?, model = ?, fuel_tank_capacity = ? WHERE id = ?;";
		rep2.updateCar(combustionCar, catalogIndex, SQL, "combustion_cars", type, fuelTankCapacity);
		break;
	case 3:
		Repository <HybridEngineCar> rep3;
		carDataInput(hybridCar);
		int hybridType;
		cout << "\n������� ������� ������������: ";
		cin >> batteryCapacity;
		cout << "\n������� ����� ���������� ����: ";
		cin >> fuelTankCapacity;
		cout << "\n�������� ��� �������:\n0. ����������������\n1. ������������\n" << endl;
		cin >> hybridType;
		SQL = "UPDATE hybrid_cars SET year_of_production = ?, mileage = ?, price = ?, brand = ?, model = ?, fuel_tank_capacity = ?, battery_capacity = ?, hybrid_type = ? WHERE id = ?;";
		rep3.updateCar(hybridCar, catalogIndex, SQL, "hybrid_cars", type, fuelTankCapacity, batteryCapacity, hybridType);
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
		cout << "\n����������� � �������� ���" << endl;
		return;
	}
	int catalogIndex;
	catalogOutput();
	int type;
	cout << "\n�������� ��� ����������:\n1. �������������\n2. � ���\n3. ���������\n";
	cin >> type;
	cout << "\n������� ������ ����������, ������� ���������� �������: ";
	cin >> catalogIndex;
	ElectricEngineCar electricCar;
	CombustionEngineCar combustionCar;
	HybridEngineCar hybridCar;
	checkCatalogIndex(type, catalogIndex, electricCount, combustionCount, hybridCount);
	const char* SQL;
	switch (type)
	{
	case 1:
		Repository <ElectricEngineCar> rep1;
		SQL = "DELETE FROM electric_cars WHERE id = ?;";
		rep1.deleteCar(catalogIndex, "electric_cars", SQL);
		break;
	case 2:
		Repository <CombustionEngineCar> rep2;
		SQL = "DELETE FROM combustion_cars WHERE id = ?;";
		rep2.deleteCar(catalogIndex, "combustion_cars", SQL);
		break;
	case 3:
		Repository <HybridEngineCar> rep3;
		SQL = "DELETE FROM hybrid_cars WHERE id = ?;";
		rep3.deleteCar(catalogIndex, "hybrid_cars", SQL);
		break;
	default:
		break;
	}
}
template <typename T>
void inputDataInRange(const string& msg, T& min, T& max)
{
	cout << msg << " (�� � ��): ";
	cin >> min >> max;
	while (min < 0 || max < 0)
	{
		cout << "������������ ����\n" << msg << " (�� � ��): ";
		cin >> min >> max;
	}
}
void searchForCar()
{
	int electricCount;
	int hybridCount;
	int combustionCount;
	int type;
	Repository <ElectricEngineCar> rep;
	ostringstream oss;
	string str;
	dbRowsCount(hybridCount, combustionCount, electricCount);
	if (electricCount == 0 && hybridCount == 0 && combustionCount == 0)
	{
		cout << "\n����������� � �������� ���" << endl;
		return;
	}
	vector <int> vectorInt(2);
	string brand;
	string model;
	int hybridType;
	vector <float> vectorFloat(2);
	cout << "\n�������� ��� ����������:\n1. �������������\n2. � ���\n3. ���������\n";
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
		cout << "������ ���� �� ����������\n" << endl;
		return;
	}
	int choice = subMenu();
	switch (choice)
	{
	case 1:
		inputDataInRange("������� ��� ������� ����������", vectorInt[0], vectorInt[1]);
		vectorStr[3] = "year_of_production";
		vectorStr[1] = to_string(vectorInt[0]);
		vectorStr[2] = to_string(vectorInt[1]);
		break;
	case 2:
		inputDataInRange("������� ������ � ��", vectorInt[0], vectorInt[1]);
		vectorStr[3] = "mileage";
		vectorStr[1] = to_string(vectorInt[0]);
		vectorStr[2] = to_string(vectorInt[1]);
		break;
	case 3:
		inputDataInRange("������� �������� ��������� $", vectorFloat[0], vectorFloat[1]);
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
		cout << "������� �������� �����: ";
		cin.ignore();
		getline(cin, brand);
		vectorStr[3] = "brand";
		vectorStr[1] = brand;
		break;
	case 5:
		cout << "������� �������� ������: ";
		cin.ignore();
		getline(cin, model);
		vectorStr[3] = "model";
		vectorStr[1] = model;
		break;
	case 6:
		if (type == 1)
		{
			cout << "� ������������� ������ ��� ���������� ����\n" << endl;
			return;
		}
		inputDataInRange("������� ����� ���������� ����", vectorFloat[0], vectorFloat[1]);
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
			cout << "� ������ � ��� ��� �������\n" << endl;
			return;
		}
		inputDataInRange("������� ������� ������������", vectorFloat[0], vectorFloat[1]);
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
			cout << "� ���������� ���� ���������� ��� ���������� ���������\n" << endl;
			return;
		}
		cout << "�������� ��� �������:\n0. ����������������\n1. ������������\n" << endl;
		cin >> hybridType;
		while (hybridType != 0 && hybridType != 1)
		{
			cout << "������������ ����\n�������� ��� �������:\n0. ����������������\n1. ������������\n" << endl;
			cin >> hybridType;
		}
		vectorStr[3] = "hybrid_type";
		vectorStr[1] = to_string(hybridType);
		break;
	default:
		break;
	}
	rep.searchForCarInDB(vectorStr[0], vectorStr[1], vectorStr[2], vectorStr[3], type);
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
			cout << "\033[32m" << val1;
			cout.width(27);
			cout << "\033[31m" << val2 << "\033[0m" << endl;
		}
		else
		{
			cout.width(12);
			cout << "\033[31m" << val1;
			cout.width(27);
			cout << "\033[32m" << val2 << "\033[0m" << endl;
		}
		break;
	case 0:
		if (val1 < val2)
		{
			cout.width(12);
			cout << "\033[32m" << val1;
			cout.width(27);
			cout << "\033[31m" << val2 << "\033[0m" << endl;
		}
		else
		{
			cout.width(12);
			cout << "\033[31m" << val1;
			cout.width(27);
			cout << "\033[32m" << val2 << "\033[0m" << endl;
		}
		break;
	default:
		break;
	}
}
template <typename T>
void compareCarsToParameters(int type, vector <T> carObj, vector <float> vectorFloat)
{
	std::cout << "��������� ���������:\n" << std::endl;
	std::cout << "\t\t1-�� ����������\t\t  2-�� ����������" << std::endl;
	compareAndPrint(carObj[0].getYear(), carObj[1].getYear(), true, "��� �������:  ");
	compareAndPrint(carObj[0].getMileage(), carObj[1].getMileage(), false, "������:     ");
	compareAndPrint(carObj[0].getPrice(), carObj[1].getPrice(), false, "��������� $: ");
	std::cout << "�����:       ";
	std::cout.width(12);
	std::cout << carObj[0].getBrand();
	std::cout.width(25);
	std::cout << carObj[1].getBrand();
	std::cout << "\n������:      ";
	std::cout.width(12);
	std::cout << carObj[0].getModel();
	std::cout.width(25);
	std::cout << carObj[1].getModel() << std::endl;
	switch (type)
	{
	case 1:
		compareAndPrint(vectorFloat[0], vectorFloat[1], true, "������� �������:");
		break;
	case 2:
		compareAndPrint(vectorFloat[2], vectorFloat[3], true, "����� ����:     ");
		break;
	case 3:
		compareAndPrint(vectorFloat[0], vectorFloat[1], true, "������� �������:");
		compareAndPrint(vectorFloat[2], vectorFloat[3], true, "����� ����:     ");
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
	const char* SQL;
	dbRowsCount(hybridCount, combustionCount, electricCount);
	vector<ElectricEngineCar> electricCar(2);
	vector<CombustionEngineCar> combustionCar(2);
	vector<HybridEngineCar> hybridCar(2);
	vector<int> vectorInt(2); //0 - hybridType1, 1 - hybridType2
	vector<float> vectorFloat(4); //0 - batteryCapacity1, 1 - batteryCapacity2, 2 - fuelTankCapacity1, 3 - fuelTankCapacity2
	if (electricCount == 0 && hybridCount == 0 && combustionCount == 0)
	{
		cout << "\n����������� � �������� ���" << endl;
		return;
	}
	catalogOutput();
	int index1;
	int index2;
	int type;
	cout << "\n�������� ��� ��������� �����������:\n1. �������������\n2. � ���\n3. ���������\n";
	cin >> type;
	cout << "\n������� ������� �����������, ������� ����� ��������" << endl;
	cin >> index1 >> index2;
	switch (type)
	{
		case 1:
			Repository <ElectricEngineCar> rep1;
			if (index1 > electricCount || index2 > electricCount)
			{
				cout << "������ �������� ������" << endl;
				return;
			}
			SQL = "SELECT year_of_production, mileage, price, brand, model, battery_capacity FROM electric_cars WHERE id = ?;";
			rep1.getCar(index1, "electric_cars", SQL, type, electricCar[0], vectorFloat[2], vectorFloat[0], vectorInt[0]);
			rep1.getCar(index2, "electric_cars", SQL, type, electricCar[1], vectorFloat[3], vectorFloat[1], vectorInt[1]);
			compareCarsToParameters(type, electricCar, vectorFloat);
			break;
		case 2:
			Repository <CombustionEngineCar> rep2;
			if (index1 > combustionCount || index2 > combustionCount)
			{
				cout << "������ �������� ������" << endl;
				return;
			}
			SQL = "SELECT year_of_production, mileage, price, brand, model, fuel_tank_capacity FROM combustion_cars WHERE id = ?;";
			rep2.getCar(index1, "combustion_cars", SQL, type, combustionCar[0], vectorFloat[2], vectorFloat[0], vectorInt[0]);
			rep2.getCar(index2, "combustion_cars", SQL, type, combustionCar[1], vectorFloat[3], vectorFloat[1], vectorInt[1]);
			compareCarsToParameters(type, combustionCar, vectorFloat);
			break;
		case 3:
			Repository <HybridEngineCar> rep3;
			if (index1 > hybridCount || index2 > hybridCount)
			{
				cout << "������ �������� ������" << endl;
				return;
			}
			SQL = "SELECT year_of_production, mileage, price, brand, model, fuel_tank_capacity, battery_capacity, hybrid_type FROM hybrid_cars WHERE id = ?;";
			rep3.getCar(index1, "hybrid_cars", SQL, type, hybridCar[0], vectorFloat[2], vectorFloat[0], vectorInt[0]);
			rep3.getCar(index2, "hybrid_cars", SQL, type, hybridCar[1], vectorFloat[3], vectorFloat[1], vectorInt[1]);
			compareCarsToParameters(type, hybridCar, vectorFloat);
			break;
		default:
			cout << "\n������ ���� �� ����������" << endl;
			return;
	}
}