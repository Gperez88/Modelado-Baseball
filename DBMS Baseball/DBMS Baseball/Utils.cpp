#include "stdafx.h"
#include "Utils.h"

/***************************************************
* Hace un split de un string y lo pasa a un vector.
* @param str string a separar.
* @param delimit delimitador de separacion.
* @return vector con los elementos separados.
****************************************************/
vector<string> Utils::split(string str, char delimit) {
	vector<string> vector;
	stringstream ss(str);
	string tok;

	while (getline(ss, tok, delimit)) {
		vector.push_back(tok);
	}

	return vector;
}

/********************************************************
* Lee un archivo line por linea y las mete en un vector.
* @param pathFile ruta donde se encuentra el archivo.
* @return vector con las lineas.
********************************************************/
vector<string> Utils::readFile(string pathFile) {
	ifstream inputFile = ifstream();
	inputFile.open(pathFile);

	vector<string> lines;
	string line;

	while (inputFile.good()) {
		getline(inputFile, line);

		if (line != "")
			lines.push_back(line);
	}

	return lines;
}

