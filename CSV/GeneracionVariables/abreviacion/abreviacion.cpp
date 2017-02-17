// abreviacion.cpp: define el punto de entrada de la aplicación de consola.
//

#include <string.h>
#include "stdafx.h"
#include <iostream>
#include <deque>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <typeinfo>
#include <stdlib.h>     /* atof */
#include "json.hpp"
#include <map>
#include <utility>

// for convenience
using namespace std;
using json = nlohmann::json;



bool replaceSubString(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

json AbreviarArchivo(string file_name, int cantidad_caracteres) {
	int start_s = clock();


	std::ifstream  data(file_name + ".csv"); // Abrir archivo entrada
	std::string line;

	if (!data) {
		cout << "Error abriendo archivo " << endl;
		json j;
		return j;
	}

	int num_linea = -1;
	int num_columnas = 0;



	//Creacion de diccionarios con abreviaciones y palabras que pudiesen ser encontradas.
	multimap<string, string> diccionario;
	diccionario.insert(pair<string, string>("cu", "cobre"));
	diccionario.insert(pair<string, string>("cu", "copper"));
	diccionario.insert(pair<string, string>("au", "oro"));
	diccionario.insert(pair<string, string>("au", "gold"));
	diccionario.insert(pair<string, string>("mo", "molibdeno"));
	diccionario.insert(pair<string, string>("mo", "molybdenum"));
	diccionario.insert(pair<string, string>("fe", "hierro"));
	diccionario.insert(pair<string, string>("fe", "iron"));
	diccionario.insert(pair<string, string>("ag", "plata"));
	diccionario.insert(pair<string, string>("ag", "silver"));
	diccionario.insert(pair<string, string>("t", "total"));
	diccionario.insert(pair<string, string>("t", "overall"));
	diccionario.insert(pair<string, string>("s", "soluble"));
	diccionario.insert(pair<string, string>("s", "solvable"));
	diccionario.insert(pair<string, string>("x", "xcentre"));
	diccionario.insert(pair<string, string>("y", "ycentre"));
	diccionario.insert(pair<string, string>("z", "zcentre"));





	while (std::getline(data, line))
	{
		num_linea += 1; // al final, sera el mismo numero de filas con datos que se mantienen, el header no se contabiliza.
		std::stringstream  lineStream(line);
		std::string        cell;
		vector<string> ItemsColumnas(100);
		if (num_linea == 0) { // Primera linea leida..
			while (std::getline(lineStream, cell, ',')) {
				num_columnas += 1;
				string nombre_item = cell.c_str();
				cout << "Item leido  : " << nombre_item << endl;
				for (std::multimap<string, string>::iterator it = diccionario.begin(); it != diccionario.end(); ++it) {
					//std::cout << (*it).first << " => " << (*it).second << '\n'; // abreviacion sera it.first, palabras seras it.second
					string key = (*it).first;
					string word = (*it).second;


					if (nombre_item.find(word) != std::string::npos) { // chequear si word es un substring de nombre_item
						std::cout << "found!" << nombre_item << " - " << word << endl;
						replaceSubString(nombre_item, word, key);
						cout << "NOW WORD = "<<nombre_item<<endl;

					}//fin for

				}//fin while
				ItemsColumnas.resize(num_columnas);

			}

		}
		break; // Solo importa trabajar la primera linea del archivo (el 'header').
	}


	//Crear archivo json, para respuesta
	json j;
	int stop_s = clock();
	std::cout << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << endl;
	return j;
}


int main()
{

	AbreviarArchivo("modelo_cp", 2);
	while (true) {
		//Este while unicamente existe para que no se cierre el programa cada vez q lo pruebo.
	}
	return 0;
}
