#include "Header.h"

void ElectricEngineCar::addCar(int year, int mileage, float price, const std::string& brand, const std::string& model, float btrCapacity) const
{
	sqlite3* dataBase;
	int error = sqlite3_open("Cars.db", &dataBase);
	if (error)
	{
		std::cout << "�� ������� ������� ���� ������: " << sqlite3_errmsg(dataBase) << std::endl;
		sqlite3_close(dataBase);
		return;
	}
	sqlite3_stmt* stmt;
	const char* SQL = "INSERT INTO electric_cars (year_of_production, mileage, price, brand, model, battery_capacity)"
		"VALUES (?, ?, ?, ?, ?, ?);";
	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
	if (error != SQLITE_OK)
	{
		std::cout << "�� ������� ����������� SQL ������: " << sqlite3_errmsg(dataBase) << std::endl;
		sqlite3_close(dataBase);
		return;
	}
	sqlite3_bind_int(stmt, 1, year);
	sqlite3_bind_int(stmt, 2, mileage);
	sqlite3_bind_double(stmt, 3, price);
	sqlite3_bind_text(stmt, 4, brand.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, model.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_double(stmt, 6, btrCapacity);
	error = sqlite3_step(stmt);
	if (error != SQLITE_DONE)
	{
		std::cout << "�� ������� ��������� SQL ������: " << sqlite3_errmsg(dataBase) << std::endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(dataBase);
}
void ElectricEngineCar::print()
{
	sqlite3* dataBase;
	int error = sqlite3_open("Cars.db", &dataBase);
	if (error)
	{
		std::cout << "�� ������� ������� ���� ������: " << sqlite3_errmsg(dataBase) << std::endl;
		return;
	}
	const char* sql = "SELECT year_of_production, mileage, price, brand, model, battery_capacity "
		"FROM electric_cars;";
	sqlite3_stmt* stmt;
	error = sqlite3_prepare_v2(dataBase, sql, -1, &stmt, nullptr);
	if (error != SQLITE_OK)
	{
		std::cout << "�� ������� ��������� ������: " << sqlite3_errmsg(dataBase) << std::endl;
		return;
	}
	int i = 1;
	std::cout << "\n������������� ����������:" << std::endl;
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		std::cout << "\n" << i << "-� ����������:\n" << std::endl;
		std::cout << "  ��� �������: " << sqlite3_column_int(stmt, 0) << std::endl;
		std::cout << "  ������ � ��: " << sqlite3_column_int(stmt, 1) << std::endl;
		std::cout << "  ��������� � $: " << sqlite3_column_double(stmt, 2) << std::endl;
		std::cout << "  �����: " << sqlite3_column_text(stmt, 3) << std::endl;
		std::cout << "  ������: " << sqlite3_column_text(stmt, 4) << std::endl;
		std::cout << "  ������� �������: " << sqlite3_column_double(stmt, 5) << std::endl;
		i++;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(dataBase);
}
void ElectricEngineCar::updateCar(int index, int year, int mileage, float price, const std::string& brand, const std::string& model, float btrCapacity) const
{
	int id;
	id = findIDinDB(index, "electric_cars");
	sqlite3* dataBase;
	int error = sqlite3_open("Cars.db", &dataBase);
	if (error)
	{
		std::cout << "�� ������� ������� ���� ������: " << sqlite3_errmsg(dataBase) << std::endl;
		return;
	}
	sqlite3_stmt* stmt;
	const char* SQL = "UPDATE electric_cars SET year_of_production = ?, mileage = ?, price = ?, brand = ?, model = ?, battery_capacity = ? WHERE id = ?;";
	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
	if (error != SQLITE_OK)
	{
		std::cout << "�� ������� ����������� SQL ������: " << sqlite3_errmsg(dataBase) << std::endl;
		sqlite3_close(dataBase);
		return;
	}
	sqlite3_bind_int(stmt, 1, year);
	sqlite3_bind_int(stmt, 2, mileage);
	sqlite3_bind_double(stmt, 3, price);
	sqlite3_bind_text(stmt, 4, brand.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, model.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_double(stmt, 6, btrCapacity);
	sqlite3_bind_int(stmt, 7, id);
	error = sqlite3_step(stmt);
	if (error != SQLITE_DONE)
	{
		std::cout << "�� ������� ��������� SQL ������: " << sqlite3_errmsg(dataBase) << std::endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(dataBase);
}
void ElectricEngineCar::deleteCar(int index) const
{
	int id;
	id = findIDinDB(index, "electric_cars");
	sqlite3* dataBase;
	int error = sqlite3_open("Cars.db", &dataBase);
	if (error)
	{
		std::cout << "�� ������� ������� ���� ������: " << sqlite3_errmsg(dataBase) << std::endl;
		return;
	}
	sqlite3_stmt* stmt;
	const char* SQL = "DELETE FROM electric_cars WHERE id = ?;";
	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
	if (error != SQLITE_OK)
	{
		std::cout << "�� ������� ����������� SQL ������: " << sqlite3_errmsg(dataBase) << std::endl;
		sqlite3_close(dataBase);
		return;
	}
	sqlite3_bind_int(stmt, 1, id);
	error = sqlite3_step(stmt);
	if (error != SQLITE_DONE)
	{
		std::cout << "�� ������� ��������� SQL ������: " << sqlite3_errmsg(dataBase) << std::endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(dataBase);
}
void ElectricEngineCar::getCar(int index, int& year, int& mileage, float& price, std::string& brand, std::string& model, float& btrCapacity) const
{
	int id;
	id = findIDinDB(index, "electric_cars");
	sqlite3* dataBase;
	int error = sqlite3_open("Cars.db", &dataBase);
	if (error)
	{
		std::cout << "�� ������� ������� ���� ������: " << sqlite3_errmsg(dataBase) << std::endl;
		return;
	}
	sqlite3_stmt* stmt;
	const char* SQL = "SELECT year_of_production, mileage, price, brand, model, battery_capacity FROM electric_cars WHERE id = ?;";
	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
	if (error != SQLITE_OK)
	{
		std::cout << "�� ������� ����������� SQL ������: " << sqlite3_errmsg(dataBase) << std::endl;
		sqlite3_close(dataBase);
		return;
	}
	sqlite3_bind_int(stmt, 1, id);
	error = sqlite3_step(stmt);
	if (error != SQLITE_DONE)
	{
		std::cout << "�� ������� ��������� SQL ������: " << sqlite3_errmsg(dataBase) << std::endl;
	}
	year = sqlite3_column_int(stmt, 0);
	mileage = sqlite3_column_int(stmt, 1);
	price = static_cast<float>(sqlite3_column_double(stmt, 2));
	brand = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
	model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
	btrCapacity = static_cast<float>(sqlite3_column_double(stmt, 5));
}