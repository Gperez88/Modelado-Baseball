#pragma once
#include <string>

using namespace std;

class ForeignKey
{
private:
	string entityParent;
	string entityChild;
	string columnParent;
	string columnChild;
public:
	ForeignKey();
	ForeignKey(string entityParent, string entityChild, string columnParent, string columnChild);
	virtual ~ForeignKey();

	//getters and setters
	string getEntityParent();
	void setEntityParent(string entityParent);
	string getEntityChild();
	void setEntityChild(string entityChild);
	string getColumnParent();
	void setColumnParent(string columnParent);
	string getColumnChild();
	void setColumnChild(string columnChild);
};

