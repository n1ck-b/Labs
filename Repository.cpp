//#include "Functions.h"
//
//template <typename T>
//int Repository<T>::findIDinDB(int index, const std::string& tableName) const
//{
//	int id = 0;
//	sqlite3* dataBase;
//	int error = sqlite3_open("Cars.db", &dataBase);
//	if (error)
//	{
//		std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
//		return 0;
//	}
//	sqlite3_stmt* stmt;
//	std::string sql = "SELECT id FROM " + tableName + ";";
//	const char* SQL = sql.c_str();
//	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
//	if (error != SQLITE_OK)
//	{
//		std::cout << "Не удалось выполнить запрос: " << sqlite3_errmsg(dataBase) << std::endl;
//		return 0;
//	}
//	for (int i = 0; i < index; i++)
//	{
//		sqlite3_step(stmt);
//		id = sqlite3_column_int(stmt, 0);
//	}
//	sqlite3_finalize(stmt);
//	sqlite3_close(dataBase);
//	return id;
//}
//template <typename T>
//void Repository<T>::addCar(T& carClass, const char* SQL, const int typeOfEngine, float fuelTankCapacity, float batteryCapacity, int hybridType) const
//{
//	sqlite3* dataBase;
//	int error = sqlite3_open("Cars.db", &dataBase);
//	if (error)
//	{
//		std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
//		return;
//	}
//	sqlite3_stmt* stmt;
//	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
//	if (error != SQLITE_OK)
//	{
//		std::cout << "Не удалось подготовить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
//		sqlite3_close(dataBase);
//		return;
//	}
//	sqlite3_bind_int(stmt, 1, carClass.yearOfProduction);
//	sqlite3_bind_int(stmt, 2, carClass.mileage);
//	sqlite3_bind_double(stmt, 3, carClass.price);
//	sqlite3_bind_text(stmt, 4, carClass.brand.c_str(), -1, SQLITE_STATIC);
//	sqlite3_bind_text(stmt, 5, carClass.model.c_str(), -1, SQLITE_STATIC);
//	if (typeOfEngine == 2 || typeOfEngine == 3)
//		sqlite3_bind_double(stmt, 6, fuelTankCapacity);
//	if (typeOfEngine == 1)
//		sqlite3_bind_double(stmt, 6, batteryCapacity);
//	if (typeOfEngine == 3)
//	{
//		sqlite3_bind_double(stmt, 7, batteryCapacity);
//		sqlite3_bind_int(stmt, 8, hybridType);
//	}
//	error = sqlite3_step(stmt);
//	if (error != SQLITE_DONE)
//	{
//		std::cout << "Не удалось выполнить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
//	}
//	sqlite3_finalize(stmt);
//	sqlite3_close(dataBase);
//}
//template <typename T>
//void Repository<T>::print(const char* SQL, int typeOfEngine, const std::string& msg) const
//{
//	sqlite3* dataBase;
//	int error = sqlite3_open("Cars.db", &dataBase);
//	if (error)
//	{
//		std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
//		return;
//	}
//	sqlite3_stmt* stmt;
//	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
//	if (error != SQLITE_OK)
//	{
//		std::cout << "Не удалось выполнить запрос: " << sqlite3_errmsg(dataBase) << std::endl;
//		return;
//	}
//	int i = 1;
//	std::cout << msg << std::endl;
//	while (sqlite3_step(stmt) == SQLITE_ROW)
//	{
//		std::cout << "\n" << i << "-й автомобиль:\n" << std::endl;
//		std::cout << "  Год выпуска: " << sqlite3_column_int(stmt, 0) << std::endl;
//		std::cout << "  Пробег в км: " << sqlite3_column_int(stmt, 1) << std::endl;
//		std::cout << "  Стоимость в $: " << sqlite3_column_double(stmt, 2) << std::endl;
//		std::cout << "  Марка: " << sqlite3_column_text(stmt, 3) << std::endl;
//		std::cout << "  Модель: " << sqlite3_column_text(stmt, 4) << std::endl;
//		if (typeOfEngine == 2 || typeOfEngine == 3)
//			std::cout << "  Объем топливного бака: " << sqlite3_column_double(stmt, 5) << std::endl;
//		if (typeOfEngine == 1)
//			std::cout << "  Емкость батареи: " << sqlite3_column_double(stmt, 5) << std::endl;
//		if (typeOfEngine == 3)
//		{
//			std::cout << "  Емкость аккумулятора: " << sqlite3_column_double(stmt, 6) << std::endl;
//			int hybridType = sqlite3_column_int(stmt, 7);
//			if (hybridType == 0)
//				std::cout << "  Тип гибридного двигателя: последовательный" << std::endl;
//			else
//				std::cout << "  Тип гибридного двигателя: параллельный" << std::endl;
//		}
//		i++;
//	}
//	sqlite3_finalize(stmt);
//	sqlite3_close(dataBase);
//}
//template <typename T>
//void Repository<T>::updateCar(T& carClass, int index, const char* SQL, const std::string& tableName, int typeOfEngine, float fuelTankCapacity, float batteryCapacity, int hybridType) const
//{
//	int id;
//	id = findIDinDB(index, tableName);
//	sqlite3* dataBase;
//	int error = sqlite3_open("Cars.db", &dataBase);
//	if (error)
//	{
//		std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
//		return;
//	}
//	sqlite3_stmt* stmt;
//	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
//	if (error != SQLITE_OK)
//	{
//		std::cout << "Не удалось подготовить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
//		sqlite3_close(dataBase);
//		return;
//	}
//	sqlite3_bind_int(stmt, 1, carClass.yearOfProduction);
//	sqlite3_bind_int(stmt, 2, carClass.mileage);
//	sqlite3_bind_double(stmt, 3, carClass.price);
//	sqlite3_bind_text(stmt, 4, carClass.brand.c_str(), -1, SQLITE_STATIC);
//	sqlite3_bind_text(stmt, 5, carClass.model.c_str(), -1, SQLITE_STATIC);
//	if (typeOfEngine == 2)
//	{
//		sqlite3_bind_double(stmt, 6, fuelTankCapacity);
//		sqlite3_bind_int(stmt, 7, id);
//	}
//	if (typeOfEngine == 1)
//	{
//		sqlite3_bind_double(stmt, 6, batteryCapacity);
//		sqlite3_bind_int(stmt, 7, id);
//	}
//	if (typeOfEngine == 3)
//	{
//		sqlite3_bind_double(stmt, 6, fuelTankCapacity);
//		sqlite3_bind_double(stmt, 7, batteryCapacity);
//		sqlite3_bind_int(stmt, 8, hybridType);
//		sqlite3_bind_int(stmt, 9, id);
//	}
//	error = sqlite3_step(stmt);
//	if (error != SQLITE_DONE)
//	{
//		std::cout << "Не удалось выполнить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
//	}
//	sqlite3_finalize(stmt);
//	sqlite3_close(dataBase);
//}
//template <typename T>
//void Repository<T>::deleteCar(int index, const std::string& tableName, const char* SQL) const
//{
//	int id;
//	id = findIDinDB(index, tableName);
//	sqlite3* dataBase;
//	int error = sqlite3_open("Cars.db", &dataBase);
//	if (error)
//	{
//		std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
//		return;
//	}
//	sqlite3_stmt* stmt;
//	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
//	if (error != SQLITE_OK)
//	{
//		std::cout << "Не удалось подготовить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
//		sqlite3_close(dataBase);
//		return;
//	}
//	sqlite3_bind_int(stmt, 1, id);
//	error = sqlite3_step(stmt);
//	if (error != SQLITE_DONE)
//	{
//		std::cout << "Не удалось выполнить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
//	}
//	sqlite3_finalize(stmt);
//	sqlite3_close(dataBase);
//}
//template <typename T>
//void Repository<T>::searchForCarInDB(const std::string& tableName, const std::string& parameter1, const std::string& parameter2, const std::string& fieldName, int type) const
//{
//	sqlite3* dataBase;
//	std::string sql;
//	int error = sqlite3_open("Cars.db", &dataBase);
//	if (error)
//	{
//		std::cout << "Не удалось открыть базу данных" << sqlite3_errmsg(dataBase) << std::endl;
//		return;
//	}
//	if (parameter2 != " ")
//	{
//		sql = "SELECT * FROM " + tableName +
//			" WHERE " + fieldName + " >= " + parameter1 + " AND " + fieldName + " <= " + parameter2 + ";";
//	}
//	else
//	{
//		sql = "SELECT * FROM " + tableName +
//			" WHERE " + fieldName + " = '" + parameter1 + "';";
//	}
//	const char* SQL = sql.c_str();
//	sqlite3_stmt* stmt;
//	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
//	if (error != SQLITE_OK)
//	{
//		std::cout << "Не удалось выполнить запрос." << sqlite3_errmsg(dataBase) << std::endl;
//		return;
//	}
//	int i = 1;
//	std::cout << "\nРезультаты поиска:" << std::endl;
//	while (sqlite3_step(stmt) == SQLITE_ROW)
//	{
//		std::cout << "\n" << i << "-й автомобиль:\n" << std::endl;
//		std::cout << "  Год выпуска: " << sqlite3_column_int(stmt, 1) << std::endl;
//		std::cout << "  Пробег в км: " << sqlite3_column_int(stmt, 2) << std::endl;
//		std::cout << "  Стоимость в $: " << sqlite3_column_double(stmt, 3) << std::endl;
//		std::cout << "  Марка: " << sqlite3_column_text(stmt, 4) << std::endl;
//		std::cout << "  Модель: " << sqlite3_column_text(stmt, 5) << std::endl;
//		if (type == 2 || type == 3)
//			std::cout << "  Объем топливного бака: " << sqlite3_column_double(stmt, 6) << std::endl;
//		if (type == 1)
//			std::cout << "  Емкость аккумулятора: " << sqlite3_column_double(stmt, 6) << std::endl;
//		if (type == 3)
//		{
//			std::cout << "  Емкость аккумулятора: " << sqlite3_column_double(stmt, 7) << std::endl;
//			int hybridType = sqlite3_column_int(stmt, 8);
//			if (hybridType == 0)
//				std::cout << "  Тип гибридного двигателя: последовательный" << std::endl;
//			else
//				std::cout << "  Тип гибридного двигателя: параллельный" << std::endl;
//		}
//		i++;
//	}
//	sqlite3_finalize(stmt);
//	sqlite3_close(dataBase);
//}
//template <typename T>
//void Repository<T>::getCar(int index, std::string tableName, const char* SQL, int typeOfEngine, T& carClass, float& fuelTankCapacity, float& batteryCapacity, int& hybridType) const
//{
//	int id;
//	id = findIDinDB(index, tableName);
//	sqlite3* dataBase;
//	int error = sqlite3_open("Cars.db", &dataBase);
//	if (error)
//	{
//		std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
//		return;
//	}
//	sqlite3_stmt* stmt;
//	error = sqlite3_prepare_v2(dataBase, SQL, -1, &stmt, nullptr);
//	if (error != SQLITE_OK)
//	{
//		std::cout << "Не удалось подготовить SQL запрос: " << sqlite3_errmsg(dataBase) << std::endl;
//		sqlite3_close(dataBase);
//		return;
//	}
//	sqlite3_bind_int(stmt, 1, id);
//	sqlite3_step(stmt);
//	carClass.setYear(sqlite3_column_int(stmt, 0));
//	carClass.setMileage(sqlite3_column_int(stmt, 1));
//	carClass.setPrice(static_cast<float>(sqlite3_column_double(stmt, 2)));
//	carClass.setBrand((const char*)sqlite3_column_text(stmt, 3));
//	carClass.setModel((const char*)sqlite3_column_text(stmt, 4));
//	if (typeOfEngine == 2 || typeOfEngine == 3)
//		fuelTankCapacity = static_cast<float>(sqlite3_column_double(stmt, 5));
//	if (typeOfEngine == 1)
//		batteryCapacity = static_cast<float>(sqlite3_column_double(stmt, 5));
//	if (typeOfEngine == 3)
//	{
//		batteryCapacity = static_cast<float>(sqlite3_column_double(stmt, 6));
//		hybridType = sqlite3_column_int(stmt, 7);
//	}
//}