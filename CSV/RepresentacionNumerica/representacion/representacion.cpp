// representacion.cpp: define el punto de entrada de la aplicación de consola.


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


// for convenience
using namespace std;
using json = nlohmann::json;




std::string format(double f, int n)
{
	if (f == 0) {
		return "0";
	}
	int d = (int)::ceil(::log10(f < 0 ? -f : f)); /*digits before decimal point*/
	double order = ::pow(10., n - d);
	std::stringstream ss;
	ss << std::fixed << std::setprecision(std::max(n - d, 0)) << round(f * order) / order;
	return ss.str();
}


json FormatearArchivo(string file_name, int cifras_significativas) {
	int start_s = clock();


	std::ifstream  data(file_name+".csv"); // Abrir archivo entrada
	std::string line;

	ofstream copiaFile; //Crear archivo donde se copiaran variables
	copiaFile.open("copia-"+file_name+".csv");

	int num_linea = -1;
	vector <double> sumatoria(100, 0.0);
	vector <double> elevado(100, 0.0); //numeros elevados por 2  en cada columna. 
	vector<map<int, int>> magnitudes(100); //<orden magnitud, cantidad de veces>
	vector<int> cant_datos_por_columna(100,0);
	int num_columnas = 0;

	while (std::getline(data, line))
	{
		num_linea += 1; // al final, sera el mismo numero de filas con datos que se mantienen, el header no se contabiliza.
		std::stringstream  lineStream(line);
		std::string        cell;
		
		//cout << "linea = " << contador << " " << line << endl;
		if (num_linea == 0) { // Primera linea leida..
			copiaFile << line << "\n";
			while (std::getline(lineStream, cell, ',')) {
				num_columnas += 1;
			}
			//cout << "Numero de columnas = " << num_columnas << endl;
			sumatoria.resize(num_columnas - 3);
			elevado.resize(num_columnas - 3);
			magnitudes.resize(num_columnas - 3);
			cant_datos_por_columna.resize(num_columnas - 3);
		}
		else {
			int columna_actual = 0;
			while (std::getline(lineStream, cell, ','))
			{
				columna_actual += 1;

				if (columna_actual > 3) {
					double valor_actual = atof(cell.c_str());

					if (valor_actual > 0) {
						int orden_magnitud = (int)floor(log10(valor_actual));
						//agregar orden de magnitud

						magnitudes[columna_actual - 4][orden_magnitud] += 1;
						cant_datos_por_columna[columna_actual - 4] += 1;
						sumatoria[columna_actual - 4] += valor_actual; // almacena valores en columnas para sacar promedio despues.
						elevado[columna_actual - 4] += (valor_actual*valor_actual);
						copiaFile << format(valor_actual, cifras_significativas) << ",";

					}

					
				}
				else {
					copiaFile << cell.c_str() << ",";
				}
				//cout << valor_actual << " - " << format(valor_actual, cifras_significativas) << "\n";

			}

		}
		copiaFile << "\n"; // fin de linea
	} // fin de leer el archivo


	for (int i = 0; i < num_columnas - 3; i++) {
		std::cout << "COLUMNA: " << i << endl;

		for (auto it = magnitudes[i].cbegin(); it != magnitudes[i].cend(); ++it)
		{
			std::cout << it->first << " " << it->second << "\n";
		}
		std::cout << "--------------------------------" << endl;

	}
	vector<double> promedios(sumatoria.size());
	vector<double> varianza(sumatoria.size());
	for (int i = 0; i < sumatoria.size(); i++) {
		/*std::cout << "PROM " ;
		std::cout << sumatoria[i] / num_linea << ",";
		std::cout << endl;*/
		promedios[i] = sumatoria[i] / cant_datos_por_columna[i];
		varianza[i] = (elevado[i] - (sumatoria[i] * sumatoria[i] / cant_datos_por_columna[i])) / cant_datos_por_columna[i];
		std::cout << "Columna: " << i << endl;
		std::cout << "PROMEDIOS = " << promedios[i] << endl;
		std::cout << "VARIANZA = " << varianza[i] << endl;
		std::cout << "-----------------------------" << endl;

	}

	copiaFile.close();

	//Crear archivo json, para respuesta
	json j;
	int stop_s = clock();
	std::cout << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << endl;
	return j;
}


int main()
{
	FormatearArchivo("modelo_cp", 2); // 2 cifras significativas por defecto. 

	while (true) {
		//Este while unicamente existe para que no se cierre el programa cada vez q lo pruebo.
	}
	return 0;
}
