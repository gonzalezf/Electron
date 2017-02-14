// deteccion.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
int main()
{

	int start_s = clock();
	std::ifstream  data("modelo_cp.csv");
	std::string line;
	int contador = 0;

	while (std::getline(data, line))
	{
		std::stringstream  lineStream(line);
		std::string        cell;
		contador += 1;

		cout << "linea = " << contador <<" "<<  line << endl;
		/*while (std::getline(lineStream, cell, ','))
		{
			//cout << cell << endl;
		}*/
	}

	int stop_s = clock();
	cout << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << endl;

	while (true) { 
		//Este while unicamente existe para que no se cierre el programa cada vez q lo pruebo.
	}
	return 0;
}

