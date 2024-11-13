#include "Functions.h"

using namespace std;


int tableRowCount(int& count, const string& tableName)
{
	sqlite3* dataBase;
	sqlite3_stmt* stmt;
	int error = sqlite3_open_v2("Cars.db", &dataBase, SQLITE_OPEN_READWRITE, nullptr);
	if (error)
	{
		throw Exception(sqlite3_errmsg(dataBase), "DataBase");
	}
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