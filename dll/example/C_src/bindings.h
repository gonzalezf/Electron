	#ifdef __cplusplus
	extern "C" {
	#endif
	//__declspec(dllexport) es un flag requerida por el compilador de Visual estudio
	//pues solo agrega al dll las que cuentan con esta.
		//Funcion para crear el objeto Handler en C, se usa un puntero a vacio 
		//para mantener la generalidad
		__declspec(dllexport) void * create_Handler();
		//Funcion que libera la memoria usada por objeto
		__declspec(dllexport) void free_Handler(void * p);
		//el resto de las funciones son las equivalentes la de los metodos de basicHandler.h con la
		//salvedad que ademas se le debe pasar la referencia (void * p) del objeto que usara el metodo.
		__declspec(dllexport) int calc_fibonnacci(void * p, int n);
		__declspec(dllexport) void bobo_sort(void * p, float *num, int lenght);
		__declspec(dllexport) void load_points(void * p, const char * fileName);
		__declspec(dllexport) float* get_point(void * p, int index);
		__declspec(dllexport) float* get_dimension_points(void * p, int dimension);
		__declspec(dllexport) int hello_string(void * p, char * writeTo, const char* name, int lenght);

	#ifdef __cplusplus
	}
	#endif
