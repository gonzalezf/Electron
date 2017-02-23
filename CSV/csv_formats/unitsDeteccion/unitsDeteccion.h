#include "json.hpp"
//recibe el nombre de un archivo csv y retorna un json con las estimacion del tipo de datos y las unidades que tiene cada columna
nlohmann::json unitDeteccion(const char * fileName);