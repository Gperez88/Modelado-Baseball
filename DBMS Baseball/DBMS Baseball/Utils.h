#pragma once

#include "stdafx.h"
#include "Entity.h"

class Utils
{
public:
	static vector<string> split(string str, char delimit);
	static vector<string> readFile(string pathFile);
};

