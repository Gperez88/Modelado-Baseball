#include "stdafx.h"
#include "WhereCondition.h"


WhereCondition::WhereCondition()
{
}


WhereCondition::~WhereCondition()
{
}

string WhereCondition::getColumn()
{
	return operatorCondition;
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
