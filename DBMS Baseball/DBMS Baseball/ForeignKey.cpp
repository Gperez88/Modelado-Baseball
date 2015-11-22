#include "stdafx.h"
#include "ForeignKey.h"

ForeignKey::ForeignKey()
{
}

ForeignKey::ForeignKey(string entityParent, string entityChild, string columnParent, string columnChild)
{
	this->entityParent = entityParent;
	this->entityChild = entityChild;
	this->columnParent = columnParent;
	this->columnChild = columnChild;
}

ForeignKey::~ForeignKey()
{
}

//getters and setters
string ForeignKey::getEntityParent()
{
	return entityParent;
}

void ForeignKey::setEntityParent(string entityParent)
{
	this->entityParent = entityParent;
}

string ForeignKey::getEntityChild()
{
	return entityChild;
}

void ForeignKey::setEntityChild(string entityChild)
{
	this->entityChild = entityChild;
}

string ForeignKey::getColumnParent()
{
	return columnParent;
}

void ForeignKey::setColumnParent(string columnParent)
{
	this->columnParent = columnParent;
}

string ForeignKey::getColumnChild()
{
	return columnChild;
}

void ForeignKey::setColumnChild(string columnChild)
{
	this->columnChild = columnChild;
}
