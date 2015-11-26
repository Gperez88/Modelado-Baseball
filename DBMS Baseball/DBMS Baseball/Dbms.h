#pragma once
#include "stdafx.h"
#include "Entity.h"

class Dbms
{
private:
	vector<Entity> tables;

	//private methods
	vector<string> split(string str, char delimit);
	vector<string> readFile(string pathFile);
	Entity parserEntity(string name);
	void init();
public:
	Dbms();
	~Dbms();

	//public methods
	Entity getTable(string name);
	
	//getters and setters
	vector<Entity> getTables();
	void setTables(vector<Entity> tables);
};

