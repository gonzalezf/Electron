#include <chrono>
#include <fstream>
#include "utilities.h"
#include "unitsDeteccion.h"
#include "numericalRepresentation.h"
#include "json.hpp"
#include "abreviacion.h"
using json = nlohmann::json;
using namespace std;

int main(int argc, const char * argv[]) {

	clock_t c_start = clock();
	//guarda la forma en que se esta usando el programa
	int option, value_Opcional;
	bool convert = false;
	//se valida los datos de entrada y asigna que hara el programa
	option = validator(argc, argv,&value_Opcional);
	//si existe algun error en los datos de entrada se termina el programa. (el error es mostrado por la funcion)
	if (!option) {
		return 1;
	}
	//se crea el objeto que guarda los resultados
	json final;
	//loop para la detección de unidades
	for (size_t i = 1; option==1 && i < argc - 1; i++) {
		//ejecuta la funcion, de haber errores termina la ejecucion
		try {
			//se ejecuta la rutina para la deteccion de unidades y se guarda en el json 
			json j = unitDeteccion(argv[i]);
			final["SW"][getFileName(argv[i])] = j;
		}
		catch(exception&){
			return 2;
		}
		
	}
	//si se desea cambiar las unidades 
	if (option == 7 || option == 14) {
		convert = true;
		option = 3 + 3*(option % 2);
	}
	//loop para el manejo de cifras 
	for (size_t i = 1; (option == 3 || option == 6) && i < argc - (2 - option % 2 ); i++) {
		//ejecuta la funcion, de haber errores termina la ejecucion
		try {
			//se ejecuta la rutina para manejar las cifras y se guarda en el json 
			json j = FormatearArchivo(argv[i], value_Opcional,convert);
			final["SW"][getFileName(argv[i])] = j;
		}
		catch (exception&) {
			return 2;
		}
	}
	//loop para la abreviacion
	for (size_t i = 1; (option == 5 || option == 10) && i < argc - (2 - option % 2); i++) {
		//ejecuta la funcion, de haber errores termina la ejecucion
		try {
			//se ejecuta la rutina para manejar las cifras y se guarda en el json 
			json j = AbreviarArchivo(string(argv[i]), value_Opcional);
			final["SW"][getFileName(argv[i])] = j;
		}
		catch (exception&) {
			return 2;
		}
	}
	//se escribe en un archibo de salida los resultados
	std::ofstream ofs("file.json", std::ofstream::out);
	ofs << setw(4) << final;
	clock_t c_end = clock();
	cerr<<"Tiempo total: "<< 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n" ;
	return 0;
}