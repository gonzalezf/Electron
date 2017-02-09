#include "basicHandler.h"
extern "C" {
	__declspec(dllexport) void * create_Handler() { return new BasicHandler; };
	__declspec(dllexport) void free_Handler(void * p) { delete p; };
	__declspec(dllexport) int calc_fibonnacci(void * p, int n) { return ((BasicHandler*)p)->calc_fibonnacci(n);};
	__declspec(dllexport) void bobo_sort(void * p, float *num, int lenght) { ((BasicHandler*)p)->bobo_sort(num,lenght); };
	__declspec(dllexport) void load_points(void * p, const char * fileName) { ((BasicHandler*)p)->load_points(fileName); };
	__declspec(dllexport) float* get_point(void * p, int index) { return ((BasicHandler*)p)->get_point(index); };
	__declspec(dllexport) float* get_dimension_points(void * p, int dimension) { return ((BasicHandler*)p)->get_dimension_points(dimension); };
	__declspec(dllexport) int hello_string(void * p, char * writeTo, const char* name, int lenght) {return ((BasicHandler*)p)->hello_string(writeTo,name, lenght);};

}