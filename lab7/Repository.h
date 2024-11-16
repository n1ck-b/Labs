#pragma once
#include "Functions.h"
#include "catalogwindow.h"
#include "ui_catalogwindow.h"
#include "MainWindow.h"
#include "Exception.h"
#include <QJsonArray>
#include <QJsonObject>

template <typename T>
class Repository
{
public:
	int findIDinDB(int index, const std::string& tableName) const
	{
		int id = 0;
		sqlite3* dataBase;
		int error = sqlite3_open_v2("Cars.db", &dataBase, SQLITE_OPEN_READWRITE, nullptr);
		if (error)
		{
			throw Exception(sqlite3_errmsg(dataBase), "DataBase");
		}
		sqlite3_stmt* stmt;
		std::string sql = "SELECT id FROM " + tableName + ";";
		const char* SQL = sql.c_str();
		error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
		if (error != SQLITE_OK)
		{
			std::cout << "Не удалось выполнить запрос: " << sqlite3_errmsg(dataBase) << std::endl;
			return 0;
		}
		for (int i = 0; i < index; i++)
		{
			sqlite3_step(stmt);
			id = sqlite3_column_int(stmt, 0);
		}
		sqlite3_finalize(stmt);
		sqlite3_close(dataBase);
		return id;
	}
	void addCar(T& carClass, const char* SQL, const int typeOfEngine, float fuelTankCapacity = 0, float batteryCapacity = 0, int hybridType = 0) const
	{
		sqlite3* dataBase;
		int error = sqlite3_open_v2("Cars.db", &dataBase, SQLITE_OPEN_READWRITE, nullptr);
		if (error)
		{
			throw Exception(sqlite3_errmsg(dataBase), "DataBase");
		}
		sqlite3_stmt* stmt;
		error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
		if (error != SQLITE_OK)
		{
			std::cout << "Не удалось подготовить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
			sqlite3_close(dataBase);
			return;
		}
		sqlite3_bind_int(stmt, 1, carClass.yearOfProduction);
		sqlite3_bind_int(stmt, 2, carClass.mileage);
		sqlite3_bind_double(stmt, 3, carClass.price);
		sqlite3_bind_text(stmt, 4, carClass.brand.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 5, carClass.model.c_str(), -1, SQLITE_STATIC);
		if (typeOfEngine == 2 || typeOfEngine == 3)
			sqlite3_bind_double(stmt, 6, fuelTankCapacity);
		if (typeOfEngine == 1)
			sqlite3_bind_double(stmt, 6, batteryCapacity);
		if (typeOfEngine == 3)
		{
			sqlite3_bind_double(stmt, 7, batteryCapacity);
			sqlite3_bind_int(stmt, 8, hybridType);
		}
		error = sqlite3_step(stmt);
		if (error != SQLITE_DONE)
		{
			std::cout << "Не удалось выполнить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
		}
		sqlite3_finalize(stmt);
		sqlite3_close(dataBase);
	}
	void print(const char* SQL, int typeOfEngine, QListWidget* listWidget, int& count) const
	{
		sqlite3* dataBase;
		int error = sqlite3_open_v2("Cars.db", &dataBase, SQLITE_OPEN_READWRITE, nullptr);
		if (error)
		{
			throw Exception(sqlite3_errmsg(dataBase), "DataBase");
		}
		sqlite3_stmt* stmt;
		error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
		std::string carData;
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			carData = std::to_string(count) + "-й автомобиль:\n" + "  Год выпуска: " + std::to_string(sqlite3_column_int(stmt, 0)) + "\n" + "  Пробег в км: " + std::to_string(sqlite3_column_int(stmt, 1)) + "\n" + "  Стоимость в $ : ";
			std::string str = std::to_string(sqlite3_column_double(stmt, 2));
			str = str.substr(0, str.find(',') + 4);
			carData += str + "\n" + "  Марка: " + (const char*)sqlite3_column_text(stmt, 3) + "\n" + "  Модель: " + (const char*)sqlite3_column_text(stmt, 4) + "\n";
			if (typeOfEngine == 2 || typeOfEngine == 3)
			{
				carData = carData + "  Объем топливного бака: ";
				str = std::to_string(sqlite3_column_double(stmt, 5));
				str = str.substr(0, str.find(',') + 4);
				carData += str + "\n";
			}
			if (typeOfEngine == 1)
			{
				carData = carData + "  Емкость батареи: ";
				str = std::to_string(sqlite3_column_double(stmt, 5));
				str = str.substr(0, str.find(',') + 4);
				carData += str + "\n";
			}
			if (typeOfEngine == 3)
			{
				carData = carData + "  Емкость аккумулятора: ";
				str = std::to_string(sqlite3_column_double(stmt, 6));
				str = str.substr(0, str.find(',') + 4);
				carData += str + "\n";
				int hybridType = sqlite3_column_int(stmt, 7);
				if (hybridType == 0)
					carData = carData + "  Тип гибридного двигателя: последовательный" + "\n";
				else
					carData = carData + "  Тип гибридного двигателя: параллельный" + "\n";
			}
			listWidget->addItem(QString::fromStdString(carData));
			count++;
		}
		sqlite3_finalize(stmt);
		sqlite3_close(dataBase);
	}
	void updateCar(T& carClass, int index, const char* SQL, const std::string& tableName, int typeOfEngine, float fuelTankCapacity = 0, float batteryCapacity = 0, int hybridType = 0) const
	{
		int id;
		id = findIDinDB(index, tableName);
		sqlite3* dataBase;
		int error = sqlite3_open_v2("Cars.db", &dataBase, SQLITE_OPEN_READWRITE, nullptr);
		if (error)
		{
			throw Exception(sqlite3_errmsg(dataBase), "DataBase");
		}
		if (error)
		{
			std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
			return;
		}
		sqlite3_stmt* stmt;
		error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
		if (error != SQLITE_OK)
		{
			std::cout << "Не удалось подготовить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
			sqlite3_close(dataBase);
			return;
		}
		sqlite3_bind_int(stmt, 1, carClass.yearOfProduction);
		sqlite3_bind_int(stmt, 2, carClass.mileage);
		sqlite3_bind_double(stmt, 3, carClass.price);
		sqlite3_bind_text(stmt, 4, carClass.brand.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 5, carClass.model.c_str(), -1, SQLITE_STATIC);
		if (typeOfEngine == 2)
		{
			sqlite3_bind_double(stmt, 6, fuelTankCapacity);
			sqlite3_bind_int(stmt, 7, id);
		}
		if (typeOfEngine == 1)
		{
			sqlite3_bind_double(stmt, 6, batteryCapacity);
			sqlite3_bind_int(stmt, 7, id);
		}
		if (typeOfEngine == 3)
		{
			sqlite3_bind_double(stmt, 6, fuelTankCapacity);
			sqlite3_bind_double(stmt, 7, batteryCapacity);
			sqlite3_bind_int(stmt, 8, hybridType);
			sqlite3_bind_int(stmt, 9, id);
		}
		error = sqlite3_step(stmt);
		if (error != SQLITE_DONE)
		{
			std::cout << "Не удалось выполнить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
		}
		sqlite3_finalize(stmt);
		sqlite3_close(dataBase);
	}
	void deleteCar(int index, const std::string& tableName) const
	{
		int id;
		id = findIDinDB(index, tableName);
		sqlite3* dataBase;
		int error = sqlite3_open_v2("Cars.db", &dataBase, SQLITE_OPEN_READWRITE, nullptr);
		if (error)
		{
			throw Exception(sqlite3_errmsg(dataBase), "DataBase");
		}
		if (error)
		{
			std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
			return;
		}
		std::string sql = "DELETE FROM " + tableName + " WHERE id = ? ; ";
		const char* SQL = sql.c_str();
		sqlite3_stmt* stmt;
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
	void searchForCarInDB(const char* SQL, int typeOfEngine, int& count, QListWidget* listWidget, QJsonArray& jsonArray) const
	{
		sqlite3* dataBase;
		int error = sqlite3_open_v2("Cars.db", &dataBase, SQLITE_OPEN_READWRITE, nullptr);
		if (error)
		{
			throw Exception(sqlite3_errmsg(dataBase), "DataBase");
			std::cout << "Не удалось открыть базу данных" << sqlite3_errmsg(dataBase) << std::endl;
			return;
		}
		sqlite3_stmt* stmt;
		error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
		if (error != SQLITE_OK)
		{
			std::cout << "Не удалось выполнить запрос." << sqlite3_errmsg(dataBase) << std::endl;
			return;
		}
		std::string carData;
		QJsonObject jsonObject;
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			carData = std::to_string(count) + "-й автомобиль:\n" + "  Год выпуска: " + std::to_string(sqlite3_column_int(stmt, 1)) + "\n" + "  Пробег в км: " + std::to_string(sqlite3_column_int(stmt, 2)) + "\n" + "  Стоимость в $ : ";
			std::string str = std::to_string(sqlite3_column_double(stmt, 3));
			str = str.substr(0, str.find(',') + 4);
			carData += str + "\n" + "  Марка: " + (const char*)sqlite3_column_text(stmt, 4) + "\n" + "  Модель: " + (const char*)sqlite3_column_text(stmt, 5) + "\n";
			jsonObject["year_of_production"] = QString::fromStdString(std::to_string(sqlite3_column_int(stmt, 1)));
			jsonObject["mileage"] = QString::fromStdString(std::to_string(sqlite3_column_int(stmt, 2)));
			jsonObject["price"] = QString::fromStdString(str);
			jsonObject["brand"] = (const char*)sqlite3_column_text(stmt, 4);
			jsonObject["model"] = (const char*)sqlite3_column_text(stmt, 5);
			if (typeOfEngine == 2 || typeOfEngine == 3)
			{
				carData = carData + "  Объем топливного бака: ";
				str = std::to_string(sqlite3_column_double(stmt, 6));
				str = str.substr(0, str.find(',') + 4);
				carData += str + "\n";
				jsonObject["fuel_tank_capacity"] = QString::fromStdString(str);
			}
			if (typeOfEngine == 1)
			{
				carData = carData + "  Емкость батареи: ";
				str = std::to_string(sqlite3_column_double(stmt, 6));
				str = str.substr(0, str.find(',') + 4);
				carData += str + "\n";
				jsonObject["battery_capacity"] = QString::fromStdString(str);
			}
			if (typeOfEngine == 3)
			{
				carData = carData + "  Емкость аккумулятора: ";
				str = std::to_string(sqlite3_column_double(stmt, 7));
				str = str.substr(0, str.find(',') + 4);
				carData += str + "\n";
				int hybridType = sqlite3_column_int(stmt, 8);
				if (hybridType == 0)
				{
					carData = carData + "  Тип гибридного двигателя: последовательный" + "\n";
					jsonObject["hybrid_type"] = "serial";
				}
				else
				{
					carData = carData + "  Тип гибридного двигателя: параллельный" + "\n";
					jsonObject["hybrid_type"] = "parallel";
				}
			}
			jsonArray.append(jsonObject);
			listWidget->addItem(QString::fromStdString(carData));
			count++;
		}
		sqlite3_finalize(stmt);
		sqlite3_close(dataBase);
	}
	void getCar(int index, std::string tableName, const char* SQL, int typeOfEngine, T& carClass, float& fuelTankCapacity, float& batteryCapacity, int& hybridType) const
	{
		int id;
		id = findIDinDB(index, tableName);
		sqlite3* dataBase;
		int error = sqlite3_open_v2("Cars.db", &dataBase, SQLITE_OPEN_READWRITE, nullptr);
		if (error)
		{
			throw Exception(sqlite3_errmsg(dataBase), "DataBase");
			std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
			return;
		}
		sqlite3_stmt* stmt;
		error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
		if (error != SQLITE_OK)
		{
			std::cout << "Не удалось подготовить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
			sqlite3_close(dataBase);
			return;
		}
		sqlite3_bind_int(stmt, 1, id);
		sqlite3_step(stmt);
		carClass.setYear(sqlite3_column_int(stmt, 0));
		carClass.setMileage(sqlite3_column_int(stmt, 1));
		carClass.setPrice(static_cast<float>(sqlite3_column_double(stmt, 2)));
		carClass.setBrand((const char*)sqlite3_column_text(stmt, 3));
		carClass.setModel((const char*)sqlite3_column_text(stmt, 4));
		if (typeOfEngine == 2 || typeOfEngine == 3)
			fuelTankCapacity = static_cast<float>(sqlite3_column_double(stmt, 5));
		if (typeOfEngine == 1)
			batteryCapacity = static_cast<float>(sqlite3_column_double(stmt, 5));
		if (typeOfEngine == 3)
		{
			batteryCapacity = static_cast<float>(sqlite3_column_double(stmt, 6));
			hybridType = sqlite3_column_int(stmt, 7);
		}
	}
};