#include "stdafx.h"
#include "Entity.h"
#include "Utils.h"


// contructs
Entity::Entity() {
}

Entity::Entity(string name, vector<Column> columns, vector<ForeignKey> foreingKeys) {
	this->name = name;
	this->columns = columns;
	this->foreingKeys = foreingKeys;
}

Entity::~Entity() {
}


// private methods

/***************************************************
* Valida que la tabla no exista en el sistema.
****************************************************/
bool Entity::validateDataSystem() {
	vector<string> tableRows = Utils::readFile(DataSystem::TABLE);

	for (unsigned tableIndex = 0; tableIndex < tableRows.size(); tableIndex++) {
		string tableName = tableRows.at(tableIndex);

		if (this->name == tableName) {
			stringstream ss;
			ss << "Intenta agregar una tabla llamada '" << this->name << "' que ya existe en el sistema.";

			this->errorMessage = ss.str();

			this->entityValid = false;
			return false;
		}
	}

	this->entityValid = true;
	return true;
}

/***************************************************
* Valida la integridad de los datos al persistirlo.
* @param columns vector de las columnas.
* @param data vector de los datos a persistir.
* @return true si la validacion paso bien.
****************************************************/
bool Entity::validateDataPersistent(vector<string> columns, vector<string> data) {
	// valido que se especifiquen todos los atributos de la tabla, ya que es un insert all.
	if (columns.size() == 0 && data.size() != this->columns.size()) {
		return false;
	}

	// valido que tanto las columnas como los atributos especificado concuerden en cantidad.
	if (columns.size() > 0 && data.size() != columns.size()) {
		return false;
	}

	//valido los tipos de datos.
	if (!validateDataType(columns, data)) {
		return false;
	}

	string primaryKey = data.at(0);

	//valido si ya existe un registro con ese primary key.
	if (validatePrimaryKeyExist(primaryKey)) {
		return false;
	}

	return true;
}

/***************************************************
* Valida el tipo de datos de las columnas.
* @param columns vector de las columnas.
* @param data vector de los datos a persistir.
* @return true si la validacion paso bien.
****************************************************/
bool Entity::validateDataType(vector<string> columns, vector<string> data) {
	return true;
}

/***************************************************
* Valida si la llame primaria ya existe en la tabla.
* @param primaryKey nombre de la llame primaria.
* @return true si la validacion paso bien.
****************************************************/
bool Entity::validatePrimaryKeyExist(string primaryKey) {
	vector<string> rows = Utils::readFile(this->name + ".txt");

	for (unsigned index = 0; index < rows.size(); index++) {
		string row = rows.at(index);
		vector<string> dataColumns = Utils::split(row,'|');

		if (dataColumns.at(0) == primaryKey) {
			stringstream ss;
			ss << "Intenta agregar una llave primaria '" << primaryKey << "' que ya existe en la tabla '" << this->name << "'.";

			this->errorMessage = ss.str();

			return true;
		}
	}

	return false;
}

/***************************************************
* Valida si la columna es primary key.
* @param columnName nombre de la columna.
* @return true si la validacion paso bien.
****************************************************/
bool Entity::isPrimaryKey(string columnName) {
	for (unsigned indexColumn = 0; indexColumn < columns.size(); indexColumn++) {
		Column column = columns.at(indexColumn);
		if (column.getName() == columnName) {
			return column.isPrimaryKey();
		}
	}
	return false;
}


// public methods

/***************************************************
* Crea la entidad o tabla.
****************************************************/
void Entity::create() {
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
		bool isColumnPrimaryKey = columns.at(i).isPrimaryKey();

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

/*******************************************************
* Inserta un row con todos sus datos.
* @param data vector que contiene los datos a insertar.
********************************************************/
void Entity::insertRow(vector<string> data) {
	//TODO: mejorar mas adelante.
	vector<string> columns;

	if (validateDataPersistent(columns, data)) {
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

/*******************************************************
* Inserta un row con los datos especificados.
* @param column vector que contiene las columnas a insertar.
* @param data vector que contiene los datos a insertar.
********************************************************/
void Entity::insertRow(vector<string> columns, vector<string> data) {

	if (validateDataPersistent(columns, data)) {
		ofstream outFile = ofstream();
		outFile.open(this->name + ".txt", ios::app);

		stringstream row_ss;

		for (unsigned indexColumnLocal = 0; indexColumnLocal < this->columns.size(); indexColumnLocal++){
			string columnNameLocal = this->columns.at(indexColumnLocal).getName();
			int index = -1;

			for (unsigned indexColumn = 0; indexColumn < columns.size(); indexColumn++) {
				string column = columns.at(indexColumn);

				if (columnNameLocal == columns.at(indexColumn)) {
					index = indexColumn;
				}
			}

			if (index > -1) {
				row_ss << data.at(index) << "|";
			}
			else {
				row_ss << "null|";
			}
		}
		
		string row = row_ss.str();
		row = row.substr(0, row.length() - 1);

		outFile << row << endl;
		outFile.close();
	}
}

/*******************************************************
* Actualiza los row especificados de una tabla.
* @param column vector que contiene las columnas a actualizar.
* @param data vector que contiene los datos a actualizar.
* @param whereCondition vector que contiene las condiciones por la que se van a actualizar.
********************************************************/
void Entity::updateRow(string column[], string data[], vector<WhereCondition> whereCondition){
	//TODO: aun sin implementar.
}

/*******************************************************
* Elimina los row especificados de una tabla.
* @param column vector que contiene las columnas a eliminar.
* @param data vector que contiene los datos a eliminar.
* @param whereCondition vector que contiene las condiciones por la que se van a eliminar.
********************************************************/
void Entity::deleteRow(string column[], string data[], vector<WhereCondition> whereCondition){
	//TODO: aun sin implementar.
}

/***************************************************
* Trae toda la data de una entidad (Select * from entidad).
****************************************************/
void Entity::select(){

	stringstream outSelect;
	vector<string> columnRows = Utils::readFile(this->name + ".txt");

	for (unsigned index = 0; index < columnRows.size(); index++) {
		vector<string> data = Utils::split(columnRows.at(index), '|');
			
		for (unsigned dataIndex = 0; dataIndex < data.size(); dataIndex++) {
			outSelect << columns.at(dataIndex).getName() << " : " << data.at(dataIndex) << endl;
		}

		outSelect << endl;
	}

	std::cout << outSelect.str();
}

/***************************************************
* Trae la data que cumpla con la condicion.
* @param columns columnas a mostrar.
* @param whereConditions condiciones.
****************************************************/
void Entity::select(vector<string> columns, vector<WhereCondition> whereConditions) {
	stringstream outSelect;
	vector<string> columnRows = Utils::readFile(this->name + ".txt");

	for (unsigned index = 0; index < columnRows.size(); index++) {
		vector<string> data = Utils::split(columnRows.at(index), '|');

		for (unsigned dataIndex = 0; dataIndex < data.size(); dataIndex++) {
			Column columnLocal = this->columns.at(dataIndex);
			string dataLocal = data.at(dataIndex);

			bool condition = false;
			int index = -1;

			for (unsigned indexCondition = 0; indexCondition < whereConditions.size(); indexCondition++) {
				WhereCondition whereCondition = whereConditions.at(indexCondition);

				if (whereCondition.getColumn() == columnLocal.getName() && whereCondition.getValue() == dataLocal) {
					condition = true;
					break;
				}
			}

			if(condition){
				for (unsigned indexColumnLocal = 0; indexColumnLocal < this->columns.size();indexColumnLocal++){
					string columnLocalName = this->columns.at(indexColumnLocal).getName();

					for (unsigned indexColumn = 0; indexColumn < columns.size(); indexColumn++) {
						string columnName = columns.at(indexColumn);

						if (columnLocalName == columnName) {
							index = dataIndex;
							outSelect << columnName << " : " << data.at(indexColumnLocal) << endl;
							break;
						}
					}
				}
			}		
		}

		outSelect << endl;
	}

	std::cout << outSelect.str();



}

//getters and setters
string Entity::getName() {
	return name;
}

void Entity::setName(string name) {
	this->name = name;
}

vector<Column> Entity::getColumns() {
	return columns;
}

void Entity::setColumns(vector<Column> columns) {
	this->columns = columns;
}

vector<ForeignKey> Entity::getForeignKeys() {
	return foreingKeys;
}

void Entity::setForeignKeys(vector<ForeignKey> foreingKeys) {
	this->foreingKeys = foreingKeys;
}

string Entity::getErrorMessage() {
	return errorMessage;
}

bool Entity::isValid() {
	return entityValid;
}
