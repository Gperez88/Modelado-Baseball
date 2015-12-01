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

bool Entity::validateDataPersistent(vector<string> data)
{
	if (data.size() != columns.size()) {
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
		string columnName = columns.at(i).getName();
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

void Entity::insertRow(vector<string> data)
{
	if (validateDataPersistent(data)) {
		ofstream outFile = ofstream();
		outFile.open(this->name + ".txt", ios::app);
		
		stringstream row_ss;

		for (unsigned i = 0; i < data.size(); i++) {
			row_ss << data.at(i) << "|";
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

void Entity::select()
{
	stringstream outSelect;
	vector<string> columnRows = Utils::readFile(this->name + ".txt");

	for (unsigned index = 0; index < columnRows.size(); index++) {
		vector<string> data = Utils::split(columnRows.at(index), '|');
			
		for (unsigned dataIndex = 0; dataIndex < data.size(); dataIndex++) {
			outSelect << columns.at(dataIndex).getName() << " : " << data.at(dataIndex) << endl;
		}

		outSelect << endl;
	}

	cout << outSelect.str();
}

void Entity::select(WhereCondition whereCondition[])
{
	vector<string> columnRows = Utils::readFile(this->name + ".txt");

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
