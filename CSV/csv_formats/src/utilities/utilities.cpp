#include "utilities.h"
#include <iostream>
#include <algorithm>
//funcion que recibe el nombre y ruta de un archivo y retorba solo un nombre
std::string getFileName(const char * fileName) {
	std::string strFileName = fileName;
	size_t aux;
	//se quitan todos lo qu este antes de un /
	while (strFileName.find('/') != std::string::npos) {
		aux = strFileName.find('/');
		strFileName = &strFileName[aux + 1];
	}
	//se quitan todos lo qu este antes de un '\'
	while (strFileName.find('\\') != std::string::npos) {
		aux = strFileName.find('\\');
		strFileName = &strFileName[aux + 1];
	}
	return strFileName;
}
//funcion que recive los datos de entrada y un entero donde guardar un valor opcional y retorna un valor dependiendo de estos:
//retorna 0-> si el input no es valido
//retorna 1-> si el input es valido la opcion es -u
//retorna 3-> si el input es valido la opcion es -d y no se le dan cifras
//retorna 6-> si el input es valido la opcion es -d
//retorna 5-> si el input es valido la opcion es -v y no se le dan largo del nombre
//retorna 10-> si el input es valido la opcion es -v
int validator(int argc, const char * argv[], int *optionalValue) {
	//mensaje estandar
	std::string ERROR_MESSAGE = "Modos de uso:\n    unitDeteccion file1 [fil2][file3]...[FileN] -u \n    unitDeteccion file1 [fil2][file3]...[FileN] [num_decimal] -d \n    unitDeteccion file1 [fil2][file3]...[FileN] [number_letters] -v \n";
	int aux;
	size_t exist_optional = 1;
	//si no recibe suficientes parametros
	if (argc < 3) {
		std::cerr << ERROR_MESSAGE;
		return 0;
	}
	//si el ultimo input no es una opcion valida
	if (argv[argc - 1][0] != '-' || strlen(argv[argc - 1]) != 2 || (argv[argc - 1][1] != 'u' && argv[argc - 1][1] != 'd' && argv[argc - 1][1] != 'v')) {
		std::cerr << ERROR_MESSAGE;
		return 0;
	}
	//si la opcion es unitdeteccion
	if (argv[argc - 1][1] == 'u') {
		for (size_t i = 1; i < (argc - 1); i++) {
			//si algun archivo no es un csv retorna un erro r
			if (std::string(argv[i]).find(".csv\0") == std::string::npos) {
				std::cerr << "El archivo numero " << i << " no tiene formato csv\n";
				return 0;
			}
		}
		//si indica la opcion
		return 1;
	}
	//si la opcion es alguna otra
	else {
		//si el penultimo valor no es un csv
		if (std::string(argv[argc - 2]).find(".csv\0") == std::string::npos) {
			exist_optional = 2;
			//si el penultimo valor es un entero
			if (sscanf_s(argv[argc - 2], "%i %n", optionalValue, &aux)) {
				//si la opcion no es solo un entero
				if (argv[argc - 2][aux] != '\0') {
					//se muestra el mensaje dependiendo de la opcion
					if (argv[argc - 1][1] != 'd' && argv[argc - 1][1] != 'D') {
						std::cerr << "El valor opcional number_letters debe ser entero positivo\n";
						return 0;
					}
					else {
						std::cerr << "El valor opcional num_decimal debe ser entero positivo\n";
						return 0;
					}
				}
				//si el valor es negativo se muestra el error correspondiente
				else if (*optionalValue < 0) {
					if (argv[argc - 1][1] != 'd' && argv[argc - 1][1] != 'D') {
						std::cerr << "El valor opcional number_letters debe ser entero positivo\n";
						return 0;
					}
					else {
						std::cerr << "El valor opcional num_decimal debe ser entero positivo\n";
						return 0;
					}
				}
			}
			//si el ultimo valorno es un .csv ni un entero se muestra el error correspondiente
			else {
				if (argv[argc - 1][1] != 'd'&& argv[argc - 1][1] != 'D') {
					std::cerr << "El valor opcional num_decimal debe ser entero positivo\n";
					return 0;
				}
				else {
					std::cerr << "El valor opcional number_letters debe ser entero positivo\n";
					return 0;
				}

			}
		}
		//se chequea que todos los valores no opcionales sean csv
		for (size_t i = 1; i < (argc -exist_optional ); i++) {
			if (std::string(argv[i]).find(".csv\0") == std::string::npos) {
				std::cerr << "El archivo numero " << i << " no tiene formato csv\n";
				return 0;
			}
		}
		//se retorna la opcion escogida
		if (argv[argc - 1][1] != 'v') {
			//se setea el valor por defecto si no se indico el numero de cifras
			if (exist_optional == 1) {
				*optionalValue = 3;
			}
			if (argv[argc - 1][1]=='D') {
				return exist_optional * 7;
			}
			else{
				return exist_optional * 3;
			}
			
		}
		if (exist_optional == 1) {
			//valor por defecto para el numero de caracteres
			*optionalValue = 7;
		}
		return exist_optional * 5;
	}
}
//funcion que recibe el nombre de una columna y retorna si en el se encuentra el nombre 
//de algun mineral, retonra 0 si no existe ningun nombre ,1 si le mineral es cu o fe y 2 en otro caso
int searchSubstring(std::string name) {
	//std::string lower_name = name;
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	for (size_t i = 0; i < NUM_NAMES; i++) {
		if (name.find(MINERALS_NAMES[i]) != std::string::npos) {
			if (i < 6) {
				return 1;
			}
			else {
				return 2;
			}
		}
	}
	return 0;
}
//funcion que recibe parte de una linea de csv, variables para guardar el int, float, o string y la cantidad
//de caracteres leidos, retorna 0 si se leyo un  int , 1 para un float, 2 para un string y 3 para null
int classifyType(char * str, long *value, double *f_value, char *str_readed, int * numCharReaded) {
	int  numCharReaded2;
	int value2;
	//se trata de leer la casilla como un int
	if (sscanf(str, "%ld %n", value, numCharReaded)) {
		//si ademas solo tiene numeros se trabaja como un int
		if (str[*numCharReaded] == ',' || str[*numCharReaded] == '\0') {
			//si es un número negativo se considera nulo
			if (value < 0) {
				return 3;
			}
			//de otro modo se cuenta como int
			else {
				return 0;
			}
		}
		//si no solo hay numeros en la casilla
		else {
			//y si los numeros son seguidos por algo que no sea un punto se toma como string
			if (str[*numCharReaded] != '.') {
				sscanf(str, "%[^,] %n", str_readed, numCharReaded);
				return 2;
			}
			//si son seguidos por un punto se toma como float
			else {
				//y lo que esta despues del punto es un numero
				if (sscanf(&str[*numCharReaded + 1], "%ld %n", &value2, &numCharReaded2)) {
					//si todo lo que estaba en la celda es un float
					if (str[numCharReaded2 + *numCharReaded + 1] == ',' || str[numCharReaded2 + *numCharReaded + 1] == '\0') {
						//si el valor es negativo se cuenta como nulo
						if (value < 0) {
							*numCharReaded += numCharReaded2 + 1;
							return 3;
						}
						//si todo a la izquierda del punto son 0's se toma como int 
						else if (value2 == 0) {
							*numCharReaded += numCharReaded2 + 1;
							return 0;
						}
						//se tomo como un float si nada de lo anterior ocurre
						else {
							//se lee toda la celda como float
							sscanf(str, "%lf %n", f_value, numCharReaded);
							return 1;
						}
					}
					//si tiene algo ademas de un float se toma como string
					else {
						sscanf(str, "%[^,] %n", str_readed, numCharReaded);
						return 2;
					}
				}
				//si despues del punto hay mas caracteres se toma como un string
				else {
					sscanf(str, "%[^,] %n", str_readed, numCharReaded);
					return 2;
				}
			}
		}
	}
	//si no parte con algun numero es tomado como string
	else {
		sscanf(str, "%[^,] %n", str_readed, numCharReaded);
		return 2;
	}
}