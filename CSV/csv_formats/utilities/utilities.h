#include <string>

const int NUM_NAMES = 17;
//lista de nombre de minerales comunes en csv
const std::string MINERALS_NAMES[NUM_NAMES] = {"cu","fe","cobre","hierro","copper","iron","mo","molibdeno","moli","Molybdenum","moly","au","ag","oro","plata","gold","silver" };
//funcion que recibe el nombre y ruta de un archivo y retorna solo un nombre
std::string getFileName(const char * fileName);
//funcion que recive los datos de entrada y un entero donde guardar un valor opcional y retorna un valor dependiendo de estos:
//retorna 0-> si el input no es valido
//retorna 1-> si el input es valido la opcion es -u
//retorna 3-> si el input es valido la opcion es -d y no se le dan cifras
//retorna 6-> si el input es valido la opcion es -d
//retorna 5-> si el input es valido la opcion es -v y no se le dan largo del nombre
//retorna 10-> si el input es valido la opcion es -v
//retorna 7-> si el input es valido la opcion es -D y no se le dan cifras
//retorna 14-> si el input es valido la opcion es -D

int validator(int argc, const char * argv[], int *optionalValue);
//funcion que recibe el nombre de una columna y retorna si en el se encuentra el nombre 
//de algun mineral, retonra 0 si no existe ningun nombre ,1 si le mineral es cu o fe y 2 en otro caso
int searchSubstring(std::string name);
//funcion que recibe parte de una linea de csv, variables para guardar el int, float, o string y la cantidad
//de caracteres leidos, retorna 0 si se leyo un  int , 1 para un float, 2 para un string y 3 para null
int classifyType(char * str, long *value, double *f_value, char *str_readed, int * numCharReaded);