#include "stdafx.h"
#include "Column.h"

Column::Column()
{
}

Column::Column(string name, string type, bool primaryKey)
{
	this->name = name;
	this->type = type;
	this->primaryKey = primaryKey;
}

Column::~Column()
{
}

string Column::getName()
{
	return name;
}

void Column::setName(string name)
{
	this->name = name;
}

string Column::getType()
{
	return type;
}

void Column::setType(string type)
{
	this->type = type;
}

bool Column::getPrimaryKey()
{
	return primaryKey;
}

void Column::setPrimaryKey(bool primaryKey)
{
	this->primaryKey = primaryKey;
}
