#pragma once
#include "stdafx.h"
#include "Column.h"
#include "ForeignKey.h"
#include "WhereCondition.h"

using namespace std;

namespace DataSystem {
	const char TABLE[] = "table.txt";
	const char COLUMN[] = "column.txt";
	const char FOREIGNKEY[] = "foreingKey.txt";
}

namespace DataType {
	const string VARCHAR = "VARCHAR";
	const string INTEGER = "INTERGER";
	const string DECIMAL = "DECIMAL";
	const string DATE = "DATE";
}

class Entity
{
private:
	string name;
	vector<Column> columns;
	vector<ForeignKey> foreingKeys;

	bool entityValid;
	string errorMessage;

	//private methods
	bool validateDataSystem();
	bool validateDataPersistent(vector<string> columns,vector<string> data);
	bool validateDataType(vector<string> columns, vector<string> data);
	bool validatePrimaryKeyExist(string primaryKey);
	bool isPrimaryKey(string columnName);
public:
	Entity();
	Entity(string name, vector<Column> columns, vector<ForeignKey> foreingKeys);
	virtual ~Entity();

	//public methods
	void create();
	void insertRow(vector<string> data);
	void insertRow(vector<string> columns, vector<string> data);
	void updateRow(vector<string> columns, vector<string> data);
	void updateRow(string column[], string data[], vector<WhereCondition> whereCondition);
	void deleteRow();
	void deleteRow(string column[], string data[]);
	void select();
	void select(vector<string> columns, vector<WhereCondition> whereCondition);

	//getters and sertters
	string getName();
	void setName(string name);
	vector<Column> getColumns();
	void setColumns(vector<Column> columns);
	vector<ForeignKey> getForeignKeys();
	void setForeignKeys(vector<ForeignKey> foreingKeys);

	string getErrorMessage();
	bool isValid();
};
