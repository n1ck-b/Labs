#include "Header.h"

void Car::executeQuery(const char* SQL) const
{
	sqlite3* dataBase;
	int error = sqlite3_open("Cars.db", &dataBase);
	if (error)
	{
		std::cout << "Не удалось открыть базу данных" << sqlite3_errmsg(dataBase) << std::endl;
		return;
	}
	char* errMsg;
	error = sqlite3_exec(dataBase, SQL, nullptr, nullptr, &errMsg);
	if (error != SQLITE_OK)
	{
		std::cout << "Возникла ошибка при обновлении данных." << errMsg << std::endl;
		return;
	}
	sqlite3_close(dataBase);
}
int Car::findIDinDB(int index, const string& tableName) const
{
	int id = 0;
	sqlite3* dataBase;
	int error = sqlite3_open("Cars.db", &dataBase);
	if (error)
	{
		std::cout << "Не удалось открыть базу данных: " << sqlite3_errmsg(dataBase) << std::endl;
		return 0;
	}
	sqlite3_stmt* stmt;
	string sql = "SELECT id FROM " + tableName + ";";
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