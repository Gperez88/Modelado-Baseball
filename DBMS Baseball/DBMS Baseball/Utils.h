#pragma once

#include "stdafx.h"

using namespace std;

class Utils
{
public:
	static vector<string> split(string str, char delimit);
	static vector<string> readFile(string pathFile);
};

