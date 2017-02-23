#include "utilities.h"
#include "numericalRepresentation.h"
#include "json.hpp"
// for convenience
using json = nlohmann::json;


std::string format(double f, int n){
	if (f == 0) {
		return "0";
	}
	int d = (int)::ceil(::log10(f < 0 ? -f : f)); /*digits before decimal point*/
	double order = ::pow(10., n - d);
	std::stringstream ss;
	ss << std::fixed << std::setprecision(std::max(n - d, 0)) << round(f * order) / order;
	return ss.str();
}

json FormatearArchivo(const char* fileName, int cifras_significativas, bool convert) {
	json j;
	char *str, line[1024], str_readed[1024];
	int c, numCharReaded, num_linea = 0, num_columnas = 0, columna_actual;
	long value = 0, output;
	double f_value;
	std::vector <int> typeColumn;
	std::vector <double> sumatoria(100, 0.0);
	std::vector <double> elevado(100, 0.0); //numeros elevados por 2  en cada columna. 
	std::vector<std::map<int, int>> magnitudes(100); //<orden magnitud, cantidad de veces>
	std::vector<int> cant_datos_por_columna(100, 0);
	FILE *fr, *fw;
	//se genera el nombre de la copia del archivo
	std::string copyName = "../output/copia-" + getFileName(fileName);
	//se abren los archivos
	fopen_s(&fr, fileName, "rt");
	fopen_s(&fw, copyName.c_str(), "w+");
	//se comprueba que se pueden leer/escribir
	if (!fr) {
		std::cerr << "No se puden abrir el archivo de datos: " << fileName << std::endl;
		throw std::exception();
	}if (!fw) {
		std::cerr << "No se puden abrir el archivo para copiar los datos: " << copyName << std::endl;
		throw std::exception();
	}
	//se lee la primera linea
	fgets(line, sizeof(line), fr);
	c = 0;
	str = &line[c];
	//se recorre la linea
	//se copia la 1ra linea al archivo de copia
	fprintf(fw, line);
	while (true) {
		num_columnas++;		
		//se lee la siguiente celda
		sscanf(str, "%[^,] %n", &str_readed, &numCharReaded);
		//se salta la coma
		c += numCharReaded + 1;
		//si es la ultima celda
		if (line[c - 1] == '\0') {
			str_readed[numCharReaded - 1] = '\0';
			typeColumn.push_back(searchSubstring(std::string(str_readed)));
			break;
		}
		//se guarda el tipo columna que se dejará, ppm->2, porcentaje->1 o otros->0
		typeColumn.push_back(searchSubstring(std::string(str_readed)));
		str = &line[c];
	}
	sumatoria.resize(num_columnas - 3);
	elevado.resize(num_columnas - 3);
	magnitudes.resize(num_columnas - 3);
	cant_datos_por_columna.resize(num_columnas - 3);
	//se lee el resto del archivo
	while (fgets(line, sizeof(line), fr)) {
		sscanf(line, "%[^\n]", &line);
		columna_actual = 0;
		c = 0;
		str = &line[c];
		//se lee cada celda
		while (true) {
			columna_actual++;
			output = classifyType(str, &value, &f_value, str_readed, &numCharReaded);
			switch (output){
			//se leyo un int
			case 0:
				//si toda la columna tiene que quedar en %, signigica que se debe modificar a %
				if (convert && typeColumn[columna_actual - 1] == 1) {
					//conversion de ppm a %
					f_value = value / 10000.0;
					fprintf(fw, "%s,", format(f_value, cifras_significativas));
					break;
				}
				//si la columna debe ser trabajada pero no trasnformar la unidad
				else if (typeColumn[columna_actual - 1] == 2) {
					fprintf(fw, "%s,", format(f_value, cifras_significativas));
					break;
				}
				fprintf(fw, "%d,", value);
				break;
			//se leyo un float
			case 1:
				//si toda la columna tiene que quedar en ppm, signigica que se debe modificar a ppm
				if (convert && typeColumn[columna_actual - 1] == 2) {
					//conversion de % a ppm
					value = (double)(f_value * 10000);
					fprintf(fw, "%s,", format(f_value, cifras_significativas));
					break;
				}
				//si la columna debe ser trabajada pero no trasnformar la unidad
				else if (typeColumn[columna_actual - 1] == 1) {
					fprintf(fw, "%s,", format(f_value, cifras_significativas));
					break;
				}
				fprintf(fw, "%f,", f_value);
				break;
			//se leyo un string se copia igual
			case 2:
				if (numCharReaded == 0) {
					fprintf(fw, ",");
					break;
				}
				fprintf(fw, "%s,", str_readed);
				
				break;
			//Se leyo un numero negativo, se copia igual
			case 3:
				fprintf(fw, "%d,", value);
				break;

			}
			c += numCharReaded + 1;
			if (line[c - 1] == '\0' || columna_actual == num_columnas) {
				fprintf(fw, "\n");
				break;
			}
			str = &line[c];
		}
	}
	std::fclose(fr);
	std::fclose(fw);
	return j;
}
