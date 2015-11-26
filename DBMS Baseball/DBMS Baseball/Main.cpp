// DBMS Baseball.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Dbms.h"
#include "Entity.h"

using namespace std;

Dbms dbms;

void createTables();
void inserData();

int main()
{
	dbms = Dbms();

	createTables();

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

	ForeignKey positionPlayerFK = ForeignKey();
	positionPlayerFK.setEntityParent("position");
	positionPlayerFK.setEntityChild("player");
	positionPlayerFK.setColumnParent("player_id");
	positionPlayerFK.setColumnChild("id");

	vector<ForeignKey> positionFKs;
	positionFKs.push_back(positionPlayerFK);

	Entity position = Entity();
	position.setName("position");
	position.setColumns(positionColumns);
	position.setForeignKeys(positionFKs);
	position.create();
}

void inserData() {
	
}



