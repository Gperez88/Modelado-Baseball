#pragma once
#include <string>

using namespace std;

namespace Operator {
	const string AND = "and";
	const string OR = "or";
}

class WhereCondition
{
private:
	string column;
	string value;
	string operatorCondition;
public:
	WhereCondition();
	~WhereCondition();

	//getter and setters
	string getColumn();
	void setColumn(string column);
	string getValue();
	void setValue(string value);
	string getOperator();
	void setOperator(string operatorCondition);
	
};

