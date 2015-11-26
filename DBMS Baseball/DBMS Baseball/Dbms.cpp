#include "stdafx.h"
#include "Dbms.h"


Dbms::Dbms()
{
}

Dbms::~Dbms()
{
}

//private methods
vector<string> Dbms::split(string str, char delimit) {
	vector<string> vector;
	stringstream ss(str);
	string tok;

	while (getline(ss, tok, delimit)) {
		vector.push_back(tok);
	}

	return vector;
}

vector<string> Dbms::readFile(string pathFile) {
	ifstream inputFile = ifstream();
	inputFile.open(pathFile);

	vector<string> lines;
	string line;

	while (inputFile.good()) {
		getline(inputFile, line);

		if (line != "")
			lines.push_back(line);
	}

	return lines;
}

Entity Dbms::parserEntity(string name) {
	Entity entity;

	vector<Column> columns;
	vector<ForeignKey> foreingKeys;

	vector<string> columnsRows;
	vector<string> foreingKeysRows;

	for (unsigned i = 0; i < columnsRows.size(); i++){
		vector<string> attributeColumn = split(columnsRows.at(i), '|');

		if (attributeColumn.size() == 3) {
			Column column;

			string name = attributeColumn.at(0);
			string type = attributeColumn.at(1);
			bool isPrimary = atoi(attributeColumn.at(2).c_str());

			column.setName(name);
			column.setType(type);
			column.setPrimaryKey(isPrimary);
		
			columns.push_back(column);
		}
	}

	for (unsigned i = 0; i < foreingKeysRows.size(); i++) {
		vector<string> attributeForeingKey = split(foreingKeysRows.at(i), '|');

		if (attributeForeingKey.size() == 4) {
			ForeignKey foreingKey;

			string entityParent = attributeForeingKey.at(0);
			string entityChild = attributeForeingKey.at(1);
			string columnParent = attributeForeingKey.at(2);
			string columnChild = attributeForeingKey.at(3);

			foreingKey.setColumnParent(entityParent);
			foreingKey.setEntityChild(entityChild);
			foreingKey.setColumnParent(columnParent);
			foreingKey.setColumnChild(columnChild);

			foreingKeys.push_back(foreingKey);
		}
	}

	entity.setName(name);
	entity.setColumns(columns);
	entity.setForeignKeys(foreingKeys);

	return entity;
}

void Dbms::init()
{

}

//public methods
Entity Dbms::getTable(string name)
{
	return Entity();
}

vector<Entity> Dbms::getTables()
{
	return vector<Entity>();
}

void Dbms::setTables(vector<Entity> tables)
{

}


