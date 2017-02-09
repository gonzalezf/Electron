#ifdef __cplusplus
#include <string>
extern "C" {
#endif
	__declspec(dllexport) void * create_Handler();
	__declspec(dllexport) void free_Handler(void * p);
	__declspec(dllexport) int calc_fibonnacci(void * p, int n);
	__declspec(dllexport) void bobo_sort(void * p, float *num, int lenght);
	__declspec(dllexport) void load_points(void * p, const char * fileName);
	__declspec(dllexport) float* get_point(void * p, int index);
	__declspec(dllexport) float* get_dimension_points(void * p, int dimension);
	__declspec(dllexport) int hello_string(void * p, char * writeTo, const char* name, int lenght);

#ifdef __cplusplus
}
#endif
