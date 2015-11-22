#pragma once
#include <string>

using namespace std;

class Column
{
private:
	string name;
	string type;
	bool primaryKey;
public:
	Column();
	Column(string name, string type, bool primaryKey);
	virtual ~Column();

	//getters and setters
	string getNane();
	void setName(string name);
	string getType();
	void setType(string type);
	bool getPrimaryKey();
	void setPrimaryKey(bool primaryKey);
};

