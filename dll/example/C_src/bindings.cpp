#include "basicHandler.h"
extern "C" {
	//todas las funciones consiste en la ejecucion del metodo de su correspodiente metodo.
	//destacar que cada vez que se usa el objeto debe ser casteado a la clase BasicHander debido
	//a que es un puntero a vacio
	void * create_Handler() { return new BasicHandler; };
	void free_Handler(void * p) { delete p; };
	int calc_fibonnacci(void * p, int n) {
		return ((BasicHandler*)p)->calc_fibonnacci(n);
	};
	void bobo_sort(void * p, float *num, int lenght) {
		((BasicHandler*)p)->bobo_sort(num,lenght);
	};
	void load_points(void * p, const char * fileName) {
		 ((BasicHandler*)p)->load_points(fileName);
	 };
	float* get_point(void * p, int index) {
		 return ((BasicHandler*)p)->get_point(index);
	 };
	float* get_dimension_points(void * p, int dimension) {
		 return ((BasicHandler*)p)->get_dimension_points(dimension);
	 };
	int hello_string(void * p, char * writeTo, const char* name, int lenght) {
		return ((BasicHandler*)p)->hello_string(writeTo,name, lenght);
	};
}
