#pragma once
#include "stdafx.h"
#include "Entity.h"

using namespace std;

const int COLUMN_ATTRIBUTE = 4;
const int FOREING_ATTRIBUTE = 4;

class Dbms
{
private:
	vector<Entity> tables;

	//private methods
	Entity parserEntity(string name, vector<string> columnRows, vector<string> foreingKeyRows);
	void clearTableInMemory();
	void init();
public:
	Dbms();
	~Dbms();

	//public methods
	void addTable(Entity table);
	void addTable(vector<Entity> tables);
	Entity getTable(string name);
	
	//getters and setters
	vector<Entity> getTables();
	void setTables(vector<Entity> tables);
};

