#include <vector>
#include <string>

class BasicHandler {
private:
	//estrctura que guarda un vector de puntos
	std::vector<std::vector<float>> points;
	//estructura auxiliar que sirve para mantener la memoria reservada del arreglo que se envia al
	//javaScript
	std::vector<float> aux;
public:
	//retorna el numero n de la serie de fibonacci
	int calc_fibonnacci(int n);
	//Implementacion basica de booble-sort, recive un arreglo desordenado y ordena los datos
	//no retorna nada, trabaja sobre el mismo arreglo
	void bobo_sort(float *num, int lenght);
	//recive el nombre del archivo y guarda los datos en la estrctura points del objeto
	void load_points(const char * fileName);
	//retorna un punto especifico, segun el indice que este tiene en el vector de puntos
	float* get_point(int index);
	//retorna un arreglo con la componente de todos los puntos de la dimension especificada
	float* get_dimension_points(int dimension);
	//recibe un buffer de escritura, un nombre y largo del buffer, escribe sobre dicho buffer
	// y retorna la cantidad de caracteres escritos.
	int hello_string(char *writeTo, const char * name, int  lenght);
};
