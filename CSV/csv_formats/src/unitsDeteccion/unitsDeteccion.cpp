#include "unitsDeteccion.h"
#include "utilities.h"

//recibe el nombre de un archivo csv y retorna un json con las estimacion del tipo de datos y las unidades que tiene cada columna
nlohmann::json unitDeteccion(const char * fileName) {
	std::vector<std::string> types, units, columnName;
	std::vector<std::vector<long>> arrayCounters;
	//vector que guarda si se encontro un valor sobre 100 para descartarlo como %
	std::vector<bool> percent_flag;
	//las posiciones del vector son 0->int 1->float 2->string 3-> null
	std::vector<long> counterColumns = { 0,0,0,0};
	char *str, line[1024], str_readed[1024];
	int c, numCharReaded = 0, totalColumns = 0;
	long value = 0,output;
	double f_value;
	FILE *f;
	fopen_s(&f, fileName, "rt");
	if (!f) {
		std::cerr << "No se puden abrir el archivo de datos: " << fileName <<std::endl;
		throw std::exception();
	}
	//se lee el header
	fgets(line, sizeof(line), f);
	c = 0;
	str = &line[c];
	//se analiza cada casilla del header
	while (true) {
		totalColumns++;
		//se lee una casilla
		sscanf(str, "%[^,] %n", &str_readed, &numCharReaded);
		//se agrega el vector de que cuenta los tipos de datos al vector principal
		arrayCounters.push_back(counterColumns);
		//se actualiza la cantidad de char leidos hasta el momento, el +1 es para saltar la coma del csv
		c += numCharReaded + 1;
		//si se llego al final de la linea
		if (line[c - 1] == '\0') {
			//se quita el \n del string
			str_readed[numCharReaded - 1] = '\0';
			//se guarda el nombre de la columna y se inicia el vector de %
			columnName.push_back(std::string(str_readed));
			percent_flag.push_back(true);
			break;
		}
		//se guarda el nombre de la columna y se inicia el vector de %
		columnName.push_back(std::string(str_readed));
		percent_flag.push_back(true);
		//se mueve el puntero sobre el string
		str = &line[c];
	}
	//se lee el resto de archivo
	while (fgets(line, sizeof(line), f)) {
		c = 0;
		int k = 0;
		//se elimina el salto de linea
		sscanf(line, "%[^\n]", &line);
		str = &line[c];
		while (true) {
			output = classifyType(str, &value, &f_value, str_readed, &numCharReaded);
			arrayCounters[k][output]++;
			if (percent_flag[k] && output==1 && f_value>100) {
				percent_flag[k] = false;
			}
			k++;
			c += 1 + numCharReaded;
			if (line[c - 1] == '\0' || k == totalColumns) {
				break;
			}
			str = str = &line[c];
		}
	}
	std::fclose(f);
	//se crea el objeto json
	nlohmann::json file;
	//Se analiza los datos de cada columna
	for (size_t i = 0; i<(size_t) totalColumns; i++){
		//si hay mas float que otros int y string se considera continua
		if (arrayCounters[i][1] >= arrayCounters[i][0] && arrayCounters[i][1] >= arrayCounters[i][2]) {
			types.push_back("Continuous");
			//si no existe ningun valor sobre 100
			if (percent_flag[i]) {
				//y tiene nombre de minerales en el header se toma como %
				if (searchSubstring(columnName[i])) {
					units.push_back("%");
				}
				//sino se toma como dencidad
				else {
					units.push_back("g/cc");
				}
			}
			//si hay algun valor sobre 100 se toma como ppm
			else {
				units.push_back("PPM");
			}
			
		}
		//si hay mas string que todo se toma como categorica
		else if (arrayCounters[i][2] > arrayCounters[i][0]) {
			types.push_back("Categorical");
			units.push_back("''");
		}
		//si hay mas int que string y float
		else {
			//si tiene nombre de minerales en el header se toma como ppm
			if (searchSubstring(columnName[i])) {
				types.push_back("Continuous");
				units.push_back("ppm");
			}
			//si no se toma como variable categorica
			else {
				types.push_back("Categorical");
				units.push_back("''");
			}
			
		}
	}
	//se escribe sobre el json
	file["header"] = columnName;
	file["types"] = types;
	file["units"] = units;
	return file;
}