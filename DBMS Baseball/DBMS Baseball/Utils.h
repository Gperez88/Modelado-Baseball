#pragma once

#include "stdafx.h"

using namespace std;

class Utils
{
public:

	/***************************************************
	* Hace un split de un string y lo pasa a un vector.
	* @param str string a separar.
	* @param delimit delimitador de separacion.
	* @return vector con los elementos separados.
	****************************************************/
	static vector<string> inline split(string str, char delimit) {
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
	static vector<string> inline readFile(string pathFile) {
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

	/********************************************************
	* Borra un elemento de un vector.
	* @param collection vector a borrar el elemento.
	* @param criteria criterio para borrar.
	* @return el vector con el elemento removido.
	********************************************************/
	template<class T>
	static vector<T> inline removeItem(vector<T> collection, T criteria) {
		vector<string>::iterator itItem = find(collection.begin(), collection.end(), criteria);
		collection.erase(itItem);
		
		return collection;
	}

	template<class T>
	static vector<T> inline sortCollection(vector<T> collection) {
		for (unsigned i = 1; i < collection.size(); i++) {
			for (unsigned j = 0; j < collection.size() - 1; j++) {
				if (collection.at(j) > collection.at(j + 1)) {
					T temp = collection.at(j);
					collection.at(j) == collection.at(j + 1);
					collection.at(j + 1) == temp;
				}
			}
		}

		return collection;
	}
};
