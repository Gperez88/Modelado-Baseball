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

	string errorMessage;

	//private methods
	bool validateDataSystem();
	bool validateDataPersistent(vector<string> data);
public:
	Entity();
	Entity(string name, vector<Column> columns, vector<ForeignKey> foreingKeys);
	virtual ~Entity();

	//public methods
	void create();
	void insertRow(vector<string> data);
	void insertRow(string column[],string data[]);
	void updateRow(string data[]);
	void updateRow(string column[], string data[]);
	void deleteRow();
	void deleteRow(string column[], string data[]);
	vector<Entity> select();
	vector<Entity> select(WhereCondition whereCondition[]);

	//getters and sertters
	string getName();
	void setName(string name);
	vector<Column> getColumns();
	void setColumns(vector<Column> columns);
	vector<ForeignKey> getForeignKeys();
	void setForeignKeys(vector<ForeignKey> foreingKeys);

	string getErrorMessage();
};
