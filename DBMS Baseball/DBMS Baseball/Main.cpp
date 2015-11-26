// DBMS Baseball.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Dbms.h"
#include "Entity.h"

using namespace std;

Dbms dbms;
string a;

void createTables();
void printStructDbms();
void inserData();

int main()
{
	dbms = Dbms();

	createTables();

	//test
	printStructDbms();

	cin >> a;


    return EXIT_SUCCESS;
}

void createTables() {
	//player
	Column idPlayerColumn = Column();
	idPlayerColumn.setName("id");
	idPlayerColumn.setType(DataType::INTEGER);
	idPlayerColumn.setPrimaryKey(true);

	Column namePlayerColumn = Column();
	namePlayerColumn.setName("name");
	namePlayerColumn.setType(DataType::VARCHAR);
	namePlayerColumn.setPrimaryKey(false);

	vector<Column> playerColumns;
	playerColumns.push_back(idPlayerColumn);
	playerColumns.push_back(namePlayerColumn);

	Entity player = Entity();
	player.setName("player");
	player.setColumns(playerColumns);
	player.create();

	//position
	Column idPositionColumn = Column();
	idPositionColumn.setName("id");
	idPositionColumn.setType(DataType::INTEGER);
	idPositionColumn.setPrimaryKey(true);

	Column namePositionColumn = Column();
	namePositionColumn.setName("name");
	namePositionColumn.setType(DataType::VARCHAR);
	namePositionColumn.setPrimaryKey(false);

	Column playerIdPositionColumn = Column();
	playerIdPositionColumn.setName("player_id");
	playerIdPositionColumn.setType(DataType::INTEGER);
	playerIdPositionColumn.setPrimaryKey(false);


	vector<Column> positionColumns;
	positionColumns.push_back(idPositionColumn);
	positionColumns.push_back(namePositionColumn);
	positionColumns.push_back(playerIdPositionColumn);

	ForeignKey positionPlayerFK = ForeignKey();
	positionPlayerFK.setEntityParent("player");
	positionPlayerFK.setEntityChild("position");
	positionPlayerFK.setColumnParent("id");
	positionPlayerFK.setColumnChild("player_id");

	vector<ForeignKey> positionFKs;
	positionFKs.push_back(positionPlayerFK);

	Entity position = Entity();
	position.setName("position");
	position.setColumns(positionColumns);
	position.setForeignKeys(positionFKs);
	position.create();

	//add tables
	dbms.addTable(player);
	dbms.addTable(position);
}

void printStructDbms() {
	for (unsigned tableIndex = 0; tableIndex < dbms.getTables().size(); tableIndex++) {
		Entity table = dbms.getTables().at(tableIndex);
		vector<Column> columns = table.getColumns();
		vector<ForeignKey> foreingKeys = table.getForeignKeys();
		cout << endl << endl;
		cout << " Tabla : " << table.getName() << endl;

		if (!columns.empty()) {
			cout << " ********** Columns *********** " << endl;
			for (unsigned columnIndex = 0; columnIndex < columns.size(); columnIndex++) {
				Column column = columns.at(columnIndex);

				cout << " >>>> Colum: " << column.getNane() << endl;
			}
		}

		if (!foreingKeys.empty()) {
			cout << " ********** ForeingKeys *********** " << endl;
			for (unsigned foreingKeyIndex = 0; foreingKeyIndex < foreingKeys.size(); foreingKeyIndex++) {
				ForeignKey foreingKey = foreingKeys.at(foreingKeyIndex);

				cout << " >>>> ForeingKey: " << foreingKey.getColumnParent() << " <> " << foreingKey.getColumnChild() << endl;
			}
		}
	}
}

void inserData() {
	
}



