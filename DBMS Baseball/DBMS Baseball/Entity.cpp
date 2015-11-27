#include "stdafx.h"
#include "Entity.h"
#include "Utils.h"

//contructs
Entity::Entity()
{
}

Entity::Entity(string name, vector<Column> columns, vector<ForeignKey> foreingKeys)
{
	this->name = name;
	this->columns = columns;
	this->foreingKeys = foreingKeys;
}

Entity::~Entity()
{
}

//private methods
bool Entity::validateDataSystem()
{
	vector<string> tableRows = Utils::readFile(DataSystem::TABLE);

	for (unsigned tableIndex = 0; tableIndex < tableRows.size(); tableIndex++) {
		string tableName = tableRows.at(tableIndex);

		if (this->name == tableName) {
			stringstream ss;
			ss << "Intenta agregar una tabla llamada '" << this->name << "' que ya existe en el sistema.";

			errorMessage = ss.str();

			return false;
		}
	}

	return true;
}

bool Entity::validateDataPersistent(string data[])
{
	int size = sizeof(data) / sizeof(*data);

	if (size != columns.size()) {
		return false;
	}

	return true;
}

//public methods
void Entity::create()
{
	//valid data system
	if (!validateDataSystem()) {
		return;
	}

	ofstream outFile = ofstream();

	//persistent table
	outFile.open(DataSystem::TABLE, ios::app);
	string tableName = this->name;
	outFile << tableName << endl;
	outFile.close();

	//persistent column
	outFile.open(DataSystem::COLUMN, ios::app);
	for (unsigned i = 0; i < columns.size(); i++) {
		string columnName = columns.at(i).getNane();
		string columnType = columns.at(i).getType();
		bool isColumnPrimaryKey = columns.at(i).getPrimaryKey();

		outFile << tableName << "|" << columnName << "|" << columnType << "|" << isColumnPrimaryKey << endl;
	}
	outFile.close();

	//persistent foreignkey
	outFile.open(DataSystem::FOREIGNKEY, ios::app);
	for (unsigned i = 0; i < foreingKeys.size(); i++) {
		string entityParentName = foreingKeys.at(i).getEntityParent();
		string entityChildName = foreingKeys.at(i).getEntityChild();
		string columnParentName = foreingKeys.at(i).getColumnParent();
		string columnChildName = foreingKeys.at(i).getColumnChild();

		outFile << entityParentName << "|" << entityChildName << "|" << columnParentName << "|" << columnChildName << endl;
	}
	outFile.close();
}

void Entity::insertRow(string data[])
{
	int size = sizeof(data) / sizeof(*data);

	if (validateDataPersistent(data)) {
		ofstream outFile = ofstream();
		outFile.open(this->name, ios::app);
		
		stringstream row_ss;

		for (int i = 0; i < size; i++) {
			row_ss << data[i] << "|";
		}

		string row = row_ss.str();
		row = row.substr(0,row.length() -1);

		outFile << row << endl;
		outFile.close();
	}

}

void Entity::insertRow(string column[], string data[])
{
}

void Entity::updateRow(string data[])
{
}

void Entity::updateRow(string column[], string data[])
{
}

void Entity::deleteRow()
{
}

void Entity::deleteRow(string column[], string data[])
{
}

vector<Entity> Entity::select()
{
	return vector<Entity>();
}

vector<Entity> Entity::select(WhereCondition whereCondition[])
{
	return vector<Entity>();
}

//getters and setters
string Entity::getName()
{
	return name;
}

void Entity::setName(string name)
{
	this->name = name;
}

vector<Column> Entity::getColumns()
{
	return columns;
}

void Entity::setColumns(vector<Column> columns)
{
	this->columns = columns;
}

vector<ForeignKey> Entity::getForeignKeys()
{
	return foreingKeys;
}

void Entity::setForeignKeys(vector<ForeignKey> foreingKeys)
{
	this->foreingKeys = foreingKeys;
}

string Entity::getErrorMessage()
{
	return errorMessage;
}
