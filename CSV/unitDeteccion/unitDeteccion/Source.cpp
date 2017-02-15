#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

json pez(const char * fileName) {
	vector<string> types;
	vector<string> units;
	vector<vector<size_t>> arrayCounters;
	vector<size_t> counterColumns = {0,0,0};
	vector<double> accumulatedValues, accumulatedRejected;
	vector<long> numAccumulate, numRejected;
	vector<string> columnName;
	char *str, line[1024],str_readed[1024];
	int value = 0, c, numCharReaded = 0;
	float f_value;
	FILE *f;
	fopen_s(&f, fileName, "rt");
	if (!f) {
		std::cerr << "No se puden abrir el archivo de datos\n";
		throw exception();
	}
	fgets(line, sizeof(line), f);
	c = 0;
	int totalColumns = 0;
	str = &line[c];
	while (true) {
		totalColumns++;
		sscanf(str, "%[^,] %n", &str_readed, &numCharReaded);
		arrayCounters.push_back(counterColumns);
		c += numCharReaded + 1;
		if (line[c - 1] == '\0') {
			str_readed[numCharReaded - 1] = '\0';
			columnName.push_back(string(str_readed));
			accumulatedValues.push_back(0);
			numAccumulate.push_back(0);
			break;
		}
		columnName.push_back(string(str_readed));
		accumulatedValues.push_back(0);
		numAccumulate.push_back(0);
		str = &line[c];
	}

	while (fgets(line, sizeof(line), f)) {
		c = 0;
		int k = 0;
		str = &line[c];
		while (true) {
			if (sscanf(str, "%i %n", &value, &numCharReaded)) {
				if (str[numCharReaded] == (char)',' || &str[numCharReaded + 1] == '\0') {
					arrayCounters[k][0]++;
					c += numCharReaded+1;
				}

				else {
					if (!sscanf(str, "%f %n", &f_value, &numCharReaded)||( str[numCharReaded] != (char)',' && str[numCharReaded] != (char)'\0')) {
						sscanf(str, "%[^,] %n", &str_readed, &numCharReaded);
						arrayCounters[k][2]++;
					}
					else {
						if (f_value < 0) {
							c += numCharReaded + 1;
							arrayCounters[k][2]++;
						}
						else if (! numAccumulate[k]) {
							arrayCounters[k][1]++;
							accumulatedValues[k] = f_value;
							numAccumulate[k]++;
							c += numCharReaded + 1;
						}
						else if ( abs(((accumulatedValues[k]/numAccumulate[k])-f_value)/ (accumulatedValues[k] / numAccumulate[k])) < 1000) {
							arrayCounters[k][1]++;
							accumulatedValues[k] += f_value;
							numAccumulate[k]++;
							c += numCharReaded + 1;
						}
					}
				}
			}
			else {
				sscanf(str, "%[^,] %n", &str_readed, &numCharReaded);
				arrayCounters[k][2]++;
				c += numCharReaded+1;
			}
k++;
if (line[c - 1] == '\0' || k == totalColumns) {
	break;
}
str = &line[c];
		}
	}
	std::fclose(f);
	json file;
	float percent = 0;
	for (size_t i = 0; i < totalColumns; i++) {
		/*
		cout << "La columna " << columnName[i] << " tiene:\n"
			<< "   " << arrayCounters[i][0] << " int\n"
			<< "   " << arrayCounters[i][1] << " float\n"
			<< "   " << arrayCounters[i][2] << " string\n"
			<< "   " << "un valor promedio de: " << accumulatedValues[i] / std::max((long)1,numAccumulate[i])<<endl;
			*/
		if (arrayCounters[i][0] > arrayCounters[i][1] || arrayCounters[i][1] < arrayCounters[i][2]) {
			types.push_back("Categorical");
			units.push_back("");
			/*
			if (arrayCounters[i][0] > arrayCounters[i][2]) {
				percent = (float)arrayCounters[i][0] / (arrayCounters[i][0] + arrayCounters[i][1] + arrayCounters[i][2]);
			}

			else {
				percent = arrayCounters[i][2] / (arrayCounters[i][0] + arrayCounters[i][1] + arrayCounters[i][2]);
			}

			if (percent == 1) {
				percent = 0.999999;
			}

			cout << "Se concluye que es una variable categorica con un " << percent*100 << "% de seguridad\n";
			*/
		}
		else {
			/*
			percent = (float) arrayCounters[i][1] / (arrayCounters[i][0] + arrayCounters[i][1] + arrayCounters[i][2]);
			if (percent == 1) {
				percent = 0.999999;
			}
			cout << "Se concluye que es una variable continua con un " << percent * 100 << "% de seguridad ";
			*/
			types.push_back("Continuous");
			if (((string(columnName[i]).find(string("Cu")) != string::npos || string(columnName[i]).find("cu") != string::npos)) && accumulatedValues[i] / std::max((long)1, numAccumulate[i]) < 10) {
				//cout << "y se estima que su unidad es '%'" ;
				units.push_back("%");
			}
			else if (((string(columnName[i]).find(string("Fe")) != string::npos || string(columnName[i]).find("fe") != string::npos)) && accumulatedValues[i] / std::max((long)1, numAccumulate[i]) < 100) {
				//cout << "y se estima que su unidad es '%'";
				units.push_back("%");
			}
			else if (accumulatedValues[i] / std::max((long)1, numAccumulate[i]) < 1) {
				//cout << "y se estima que su unidad es '%'";
				units.push_back("%");
			}
			else {
				//cout << "y se estima que su unidad es ppm,ppb o g/t";
				units.push_back("ppm|ppb|g/t");
			}
			//cout << endl;
		}
	}
	file["header"] = columnName;
	file["types"] = types;
	file["units"] = units;
	return file;


}
string getFileName(const char * fileName) {
	string strFileName = fileName;
	size_t aux;
	while (strFileName.find('/') != string::npos) {
		aux = strFileName.find('/');
		strFileName = &strFileName[aux + 1];
	}
	while (strFileName.find('\\') != string::npos) {
		aux = strFileName.find('\\');
		strFileName = &strFileName[aux + 1];
	}
	return strFileName;
}

int main(int argc, const char * argv[]) {
	string ERROR_MESSAGE = "Modos de uso:\n    unitDeteccion file1 [fil2][file3]...[FileN] -u \n    unitDeteccion file1 [fil2][file3]...[FileN] [num_decimal] -d \n    unitDeteccion file1 [fil2][file3]...[FileN] [number_letters] -v \n";
	int n, aux;
	size_t option = 0;
	if (argc < 3) {
		cerr << ERROR_MESSAGE;
		return 1;
	}
	if (argv[argc - 1][0] != '-' || strlen(argv[argc - 1]) != 2 || (argv[argc - 1][1] != 'u' && argv[argc - 1][1] != 'd' && argv[argc - 1][1] != 'v')) {
		cerr << ERROR_MESSAGE;
		return 1;
	}
	if (argv[argc - 1][1] == 'u') {
		for (size_t i = 1; i < (argc-1); i++) {
			if (string(argv[i]).find('csv') == string::npos) {
				cerr << "El archivo numero " << i << " no tiene formato csv" << endl;
				return 1;
			}
		}
	}
	else {
		for (size_t i = 1; i < (argc-2); i++) {
			if (string(argv[i]).find('csv') == string::npos) {
				cerr << "El archivo numero " << i  << " no tiene formato csv" << endl;
				return 1;
			}
		}
	}
	if ((argv[argc - 1][1] == 'd' || argv[argc - 1][1] == 'v') && string(argv[argc - 2]).find('csv') == string::npos) {
		if (sscanf_s(argv[argc - 2], "%i %n", &n,&aux) ){
			if (argv[argc - 2][aux] != '\0') {
				if (argv[argc - 1][1] != 'd') {
					cerr << "El valor opcional number_letters debe ser entero";
					return 1;
				}
				else {
					cerr << "El valor opcional num_decimald ebe ser entero";
					return 1;
				}
			}
			else if (n < 0 ) {
				if (argv[argc - 1][1] != 'd') {
					cerr << "El valor opcional number_letters debe ser entero";
					return 1;
				}
				else {
					cerr << "El valor opcional num_decimald ebe ser entero";
					return 1;
				}
			}
		}
		else {
			if (argv[argc - 1][1] != 'd') {
				cerr << "El valor opcional num_decimal debe ser entero";
				return 1;
			}
			else {
				cerr << "El valor opcional number_letters debe ser entero";
				return 1;
			}
			
		}
	}
	json final;
	for (size_t i = 1; argv[argc - 1][1] == 'u' && i < argc-1 ; i++){
		json j = pez(argv[1]);
		final["SW"][getFileName(argv[1])] = j;
	}
	for (size_t i = 1; argv[argc - 1][1] == 'd' && i < argc - 2; i++) {
		cout << "trabajando para usted\n";
		break;
	}
	for (size_t i = 1; argv[argc - 1][1] == 'v' && i < argc - 1; i++) {
		cout << "trabajando para usted\n";
		break;
	}
	std::cout << endl << final << endl << endl;;
	return 0;
}