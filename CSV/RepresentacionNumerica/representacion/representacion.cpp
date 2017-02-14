// representacion.cpp: define el punto de entrada de la aplicación de consola.


#include "stdafx.h"
#include <iostream>

using namespace std;
#include <deque>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <typeinfo>

#include "json.hpp"

// for convenience
using json = nlohmann::json;


void transpose_CSV(const std::string& filename)
{
	typedef std::vector <std::string> record;
	std::deque <record> table;
	std::size_t cols = 0;
	cout << "holiiii" << endl;
	// read the file
	{
		std::ifstream f(filename);
		std::string s;
		while (std::getline(f, s))
		{
			record r;
			std::istringstream ss(s);
			std::string cell;
			while (std::getline(ss, cell, ','))
				r.emplace_back(cell);
			table.emplace_back(r);
			cols = std::max <std::size_t>(cols, r.size());
		}
	}

	// write the file, transposing (col <--> row)
	{
		std::ofstream f(filename);
		for (std::size_t col = 0; col < cols; col++)
		{
			f << table[0][col];
			for (std::size_t row = 1; row < table.size(); row++)
			{
				f << ",";
				if (col < table[row].size()) f << table[row][col];
			}
			f << "\n";
		}
	}
}

int main()
{

	int start_s = clock();

	transpose_CSV("modelo_cp.csv");
	int stop_s = clock();
	
	cout << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << endl;

	std::ifstream  data("modelo_cp.csv");
	std::string line;
	int contador = 0;

	while (std::getline(data, line))
	{
		std::stringstream  lineStream(line);
		std::string        cell;
		contador += 1;

		//cout << "linea = " << contador << " " << line << endl;
		while (std::getline(lineStream, cell, ','))
		{
		//cout << cell << endl;
		//cout << typeid(cell).name() << endl;

		}
	}

	
	while (true) {
		//Este while unicamente existe para que no se cierre el programa cada vez q lo pruebo.
	}
	return 0;
}
