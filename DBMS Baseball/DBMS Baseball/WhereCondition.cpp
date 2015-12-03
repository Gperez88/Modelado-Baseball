#include "stdafx.h"
#include "WhereCondition.h"


WhereCondition::WhereCondition()
{
}

WhereCondition::WhereCondition(string column, string value, string operatorCondition)
{
	this->column = column;
	this->value = value;
	this->operatorCondition = operatorCondition;
}


WhereCondition::~WhereCondition()
{
}

string WhereCondition::getColumn()
{
	return column;
}

void WhereCondition::setColumn(string column)
{
	this->column = column;
}

string WhereCondition::getValue()
{
	return value;
}

void WhereCondition::setValue(string value)
{
	this->value = value;
}

string WhereCondition::getOperator()
{
	return operatorCondition;
}

void WhereCondition::setOperator(string operatorCondition)
{
	this->operatorCondition = operatorCondition;
}
