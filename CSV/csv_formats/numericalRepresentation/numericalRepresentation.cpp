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

json FormatearArchivo(const char* fileName, int cifras_significativas) {
	json j;
	char *str, line[1024], str_readed[1024];
	int c, numCharReaded = 0, numCharReaded2, num_linea = 0, num_columnas = 0, columna_actual;
	long value = 0, value2;
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
			//si la celda debe ser trabajada
			if (typeColumn[columna_actual - 1]) {
				//se comprueba que contenga un numero
				if (sscanf(str, "%ld %n", &value, &numCharReaded)) {
					//si todo lo que tiene la celda es entero
					if (str[numCharReaded] == ',' || str[numCharReaded + 1] == '\0') {
						//si es negativo no se trabaja
						if (f_value < 0) {
							fprintf(fw, "%d;", value);
						}
						//si no es negativo se debe trabajar
						else {
							//si toda la columna tiene que quedar en %, signigica que se debe modificar a %
							if (typeColumn[columna_actual - 1] == 1) {
								//conversion de ppm a %
								f_value = value / 10000.0;
//**********************************************falta aqui lo de las cifras y esas cosas
								fprintf(fw, "%lf;", f_value);
							}
							//si la columna esta en ppm se copia igual al archivo de copia
							else {
//**********************************************falta aqui lo de las cifras y esas cosas
								fprintf(fw, "%d;", value);
							}
						}
					}
					//si la celda no tiene solo un entero
					else {
						//si la celda tiene un entero y algun caracter se trabaja todo como un string
						if (str[numCharReaded] != '.') {
							sscanf(str, "%[^,] %n", &str_readed, &numCharReaded);
							fprintf(fw, "%s;", str_readed);
						}
						//si la celda tiene un float
						else {
							//se lee lo que esta despues del punto
							sscanf(&str[numCharReaded + 1], "%ld %n", &value2, &numCharReaded2);
							//si solo tiene 0's despues del punto se toma como un entero 
							if (value2 == 0) {
								//si es negativo no se trabaja
								if (f_value < 0) {
									fprintf(fw, "%d;", value);
								}
								//si no es negativo se debe trabajar
								else {
									//si toda la columna tiene que quedar en %, signigica que se debe modificar a %
									if (typeColumn[columna_actual - 1] == 1) {
										//conversion de ppm a %
										f_value = value / 10000.0;
//**********************************************falta aqui lo de las cifras y esas cosas
										fprintf(fw, "%lf;", f_value);
									}
									//si la columna esta en ppm se copia igual al archivo de copia
									else {
//**********************************************falta aqui lo de las cifras y esas cosas
										fprintf(fw, "%d;", value);
									}
								}
							}
							//sino se puede leer como un float
							else {
								sscanf(str, "%lf %n", &f_value, &numCharReaded);
								//si todo lo que hay en la celda es un float
								if (str[numCharReaded] == ',' || str[numCharReaded + 1] == '\0') {
									//si es negativo no se trabaja
									if (f_value < 0) {
										fprintf(fw, "%f;", value);
									}
									//si no es negativo se debe trabajar
									else {
										//si toda la columna tiene que quedar en % se copia tal cual al archivo
										if (typeColumn[columna_actual - 1] == 1) {
//**********************************************falta aqui lo de las cifras y esas cosas
											fprintf(fw, "%f;", f_value);
										}
										//si no se debe pasar de % ppm 
										else {
											value = (double)(f_value*10000);
//**********************************************falta aqui lo de las cifras y esas cosas
											fprintf(fw, "%d;", value);
										}
									}
								}
								//si la celda tiene un float y algun caracter se trabaja todo como un string
								else{
									sscanf(str, "%[^,] %n", &str_readed, &numCharReaded);
									fprintf(fw, "%s;", str_readed);
								}
							}
						}
					}
				}
				//si no parte como un numero se lee y se trabaja como string 
				else {
					sscanf(str, "%[^,] %n", &str_readed, &numCharReaded);
					fprintf(fw, "%s;", str_readed);
				}
			}
			//si no se debe modificar la celda
			else {
				//se compruba que el comienzo sea un numero
				if (sscanf(str, "%ld %n", &value, &numCharReaded)) {
					//si es un entero se lee y se escribe en el archivo de copia
					if (str[numCharReaded] == ',' || str[numCharReaded + 1] == '\0') {
						fprintf(fw, "%d;", value);
					}
					//si no es un entero se lee y escribe como string
					else {
						sscanf(str, "%[^,] %n", &str_readed, &numCharReaded);
						fprintf(fw, "%s;", str_readed);
					}
				}
				//si no es un entero se lee y escribe como string
				else {
					sscanf(str, "%[^,] %n", &str_readed, &numCharReaded);
					fprintf(fw, "%s;", str_readed);
				}
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
