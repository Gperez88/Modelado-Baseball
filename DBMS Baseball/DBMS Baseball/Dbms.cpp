#include "stdafx.h"
#include "Dbms.h"
#include "Utils.h"

Dbms::Dbms()
{
	this->init();
}

Dbms::~Dbms()
{
}

//private methods

/**********************************************************************
* Parsea un string y transforma en una entidad(tabla).
* @param name nombre de la entidad(tabla).
* @param columnRows vector de las columnas de la entidad(tabla)
* @param foreingKeyRows vector de los foreingKey de la entidad(tabla)
* @return una entidad(tabla).
***********************************************************************/
Entity Dbms::parserEntity(string name, vector<string> columnRows, vector<string> foreingKeyRows) {
	Entity entity;

	vector<Column> columns;
	vector<ForeignKey> foreingKeys;


	for (unsigned columnIndex = 0; columnIndex < columnRows.size(); columnIndex++){
		vector<string> attributeColumn = Utils::split(columnRows.at(columnIndex), '|');

		if (attributeColumn.size() == COLUMN_ATTRIBUTE) {
			Column column;

			string name = attributeColumn.at(1);
			string type = attributeColumn.at(2);
			bool isPrimary = atoi(attributeColumn.at(3).c_str()) == 1 ? true : false;

			column.setName(name);
			column.setType(type);
			column.setPrimaryKey(isPrimary);
		
			columns.push_back(column);
		}
	}

	for (unsigned foreingIndex = 0; foreingIndex < foreingKeyRows.size(); foreingIndex++) {
		vector<string> attributeForeingKey = Utils::split(foreingKeyRows.at(foreingIndex), '|');

		if (attributeForeingKey.size() == FOREING_ATTRIBUTE) {
			ForeignKey foreingKey;

			string entityParent = attributeForeingKey.at(0);
			string entityChild = attributeForeingKey.at(1);
			string columnParent = attributeForeingKey.at(2);
			string columnChild = attributeForeingKey.at(3);

			foreingKey.setEntityParent(entityParent);
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

/*****************************************************
* Limpia el vector de tablas para inicializar el dbms.
******************************************************/
void Dbms::clearTableInMemory()
{
	if(!tables.empty()){
		tables.clear();
	}
}

/**********************************************************
* Inicializa la estructrura de tablas y cargarla en el dbms.
***********************************************************/
void Dbms::init()
{
	vector<Entity> tables;

	vector<string> tableRows = Utils::readFile(DataSystem::TABLE);
	vector<string> columnRows = Utils::readFile(DataSystem::COLUMN);
	vector<string> foreingKeyRows = Utils::readFile(DataSystem::FOREIGNKEY);

	for (unsigned tableIndex = 0; tableIndex < tableRows.size(); tableIndex++) {
		string tableName = tableRows.at(tableIndex);
		
		vector<string> columns;
		vector<string> foreingKey;

		for (unsigned columnIndex = 0; columnIndex < columnRows.size(); columnIndex++) {
			string row = columnRows.at(columnIndex);
			vector<string> attributeColumn = Utils::split(row, '|');
			string columnTableName = attributeColumn.at(0);

			if (columnTableName == tableName) {
				columns.push_back(columnRows.at(columnIndex));
				
				//remove row.
				columnRows = Utils::removeItem<string>(columnRows,row);
				
				//descremento el indice ya que se borro un row.
				columnIndex--;
			}
		}

		for (unsigned foreingIndex = 0; foreingIndex < foreingKeyRows.size(); foreingIndex++) {
			string foreingKeyRow = foreingKeyRows.at(foreingIndex);
			vector<string> attributeForeing = Utils::split(foreingKeyRow, '|');
			string foreingKeyTableName = attributeForeing.at(1);

			if (foreingKeyTableName == tableName) {
				foreingKey.push_back(foreingKeyRow);

				//remove row.
				foreingKeyRows = Utils::removeItem<string>(foreingKeyRows, foreingKeyRow);

				//descremento el indice ya que se borro un row.
				foreingIndex--;
			}
		}

		Entity entity = parserEntity(tableName, columns, foreingKey);

		tables.push_back(entity);
	}
	//set all tables
	this->setTables(tables);
}

//public methods

/********************************
* Agrega tablas al dbms.
* @param tables tablas a agregar.
*********************************/
void Dbms::addTable(vector<Entity> tables)
{
	for (unsigned tableIndex = 0; tableIndex < tables.size(); tableIndex++) {
		addTable(tables.at(tableIndex));
	}
}

/********************************
* Agrega tabla al dbms.
* @param table tabla a agregar.
********************************/
void Dbms::addTable(Entity table)
{
	tables.push_back(table);
}

Entity Dbms::getTable(string name)
{
	return Entity();
}

vector<Entity> Dbms::getTables()
{
	return tables;
}

void Dbms::setTables(vector<Entity> tables)
{
	this->tables = tables;

}


