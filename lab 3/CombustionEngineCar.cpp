#include "Header.h"

void CombustionEngineCar::addCar(int year, int mileage, float price, const std::string& brand, const std::string& model, float tankCapacity) const
{
	sqlite3* dataBase;
	int error = sqlite3_open("Cars.db", &dataBase);
	if (error)
	{
		std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
		return;
	}
	sqlite3_stmt* stmt;
	const char* SQL = "INSERT INTO combustion_cars (year_of_production, mileage, price, brand, model, fuel_tank_capacity)"
		"VALUES (?, ?, ?, ?, ?, ?);";
	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
	if (error != SQLITE_OK)
	{
		std::cout << "Не удалось подготовить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
		sqlite3_close(dataBase);
		return;
	}
	sqlite3_bind_int(stmt, 1, year);
	sqlite3_bind_int(stmt, 2, mileage);
	sqlite3_bind_double(stmt, 3, price);
	sqlite3_bind_text(stmt, 4, brand.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, model.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_double(stmt, 6, tankCapacity);
	error = sqlite3_step(stmt);
	if (error != SQLITE_DONE)
	{
		std::cout << "Не удалось выполнить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(dataBase);
}
void CombustionEngineCar::print()
{
	sqlite3* dataBase;
	int error = sqlite3_open("Cars.db", &dataBase);
	if (error)
	{
		std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
		return;
	}
	const char* sql = "SELECT year_of_production, mileage, price, brand, model, fuel_tank_capacity "
		"FROM combustion_cars;";
	sqlite3_stmt* stmt;
	error = sqlite3_prepare_v2(dataBase, sql, -1, &stmt, nullptr);
	if (error != SQLITE_OK)
	{
		std::cout << "Не удалось выполнить запрос: " << sqlite3_errmsg(dataBase) << std::endl;
		return;
	}
	int i = 1;
	std::cout << "\nАвтомобили с ДВС:" << std::endl;
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		std::cout << "\n" << i << "-й автомобиль:\n" << std::endl;
		std::cout << "  Год выпуска: " << sqlite3_column_int(stmt, 0) << std::endl;
		std::cout << "  Пробег в км: " << sqlite3_column_int(stmt, 1) << std::endl;
		std::cout << "  Стоимость в $: " << sqlite3_column_double(stmt, 2) << std::endl;
		std::cout << "  Марка: " << sqlite3_column_text(stmt, 3) << std::endl;
		std::cout << "  Модель: " << sqlite3_column_text(stmt, 4) << std::endl;
		std::cout << "  Объем топливного бака: " << sqlite3_column_double(stmt, 5) << std::endl;
		i++;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(dataBase);
}
void CombustionEngineCar::updateCar(int index, int year, int mileage, float price, const std::string& brand, const std::string& model, float tankCapacity) const
{
	int id;
	id = findIDinDB(index, "combustion_cars");
	sqlite3* dataBase;
	int error = sqlite3_open("Cars.db", &dataBase);
	if (error)
	{
		std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
		return;
	}
	const char* SQL = "UPDATE combustion_cars SET year_of_production = ?, mileage = ?, price = ?, brand = ?, model = ?, fuel_tank_capacity = ? WHERE id = ?;";
	sqlite3_stmt* stmt;
	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
	if (error != SQLITE_OK)
	{
		std::cout << "Не удалось подготовить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
		sqlite3_close(dataBase);
		return;
	}
	sqlite3_bind_int(stmt, 1, year);
	sqlite3_bind_int(stmt, 2, mileage);
	sqlite3_bind_double(stmt, 3, price);
	sqlite3_bind_text(stmt, 4, brand.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 5, model.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_double(stmt, 6, tankCapacity);
	sqlite3_bind_int(stmt, 7, id);
	error = sqlite3_step(stmt);
	if (error != SQLITE_DONE)
	{
		std::cout << "Не удалось выполнить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(dataBase);
}
void CombustionEngineCar::deleteCar(int index) const
{
	int id;
	id = findIDinDB(index, "combustion_cars");
	sqlite3* dataBase;
	int error = sqlite3_open("Cars.db", &dataBase);
	if (error)
	{
		std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
		return;
	}
	sqlite3_stmt* stmt;
	const char* SQL = "DELETE FROM combustion_cars WHERE id = ?;";
	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
	if (error != SQLITE_OK)
	{
		std::cout << "Не удалось подготовить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
		sqlite3_close(dataBase);
		return;
	}
	sqlite3_bind_int(stmt, 1, id);
	error = sqlite3_step(stmt);
	if (error != SQLITE_DONE)
	{
		std::cout << "Не удалось выполнить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(dataBase);
}
void CombustionEngineCar::getCar(int index, int& year, int& mileage, float& price, std::string& brand, std::string& model, float& tankCapacity) const
{
	int id;
	id = findIDinDB(index, "combustion_cars");
	sqlite3* dataBase;
	int error = sqlite3_open("Cars.db", &dataBase);
	if (error)
	{
		std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
		return;
	}
	sqlite3_stmt* stmt;
	const char* SQL = "SELECT year_of_production, mileage, price, brand, model, fuel_tank_capacity FROM combustion_cars WHERE id = ?;";
	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
	if (error != SQLITE_OK)
	{
		std::cout << "Не удалось подготовить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
		sqlite3_close(dataBase);
		return;
	}
	sqlite3_bind_int(stmt, 1, id);
	sqlite3_step(stmt);
	year = sqlite3_column_int(stmt, 0);
	mileage = sqlite3_column_int(stmt, 1);
	price = static_cast<float>(sqlite3_column_double(stmt, 2));
	brand = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
	model = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
	tankCapacity = static_cast<float>(sqlite3_column_double(stmt, 5));
}