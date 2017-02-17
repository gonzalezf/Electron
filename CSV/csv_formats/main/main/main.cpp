#include "utilities.h"
#include "unitsDeteccion.h"
#include <chrono>
#include <fstream>
using json = nlohmann::json;
using namespace std;

int main(int argc, const char * argv[]) {
	clock_t c_start = clock();
	int option;
	option = validator(argc, argv);
	if (!option) {
		return 1;
	}
	json final;
	for (size_t i = 1; option==1 && i < argc - 1; i++) {
		try {
			json j = unitDeteccion(argv[i]);
			final["SW"][getFileName(argv[i])] = j;
		}
		catch(exception&){
			return 2;
		}
		
	}
	for (size_t i = 1; (option == 3 || option == 6) && i < argc - (2 - option % 2 ); i++) {
		final["SW"][getFileName(argv[i])] = "d" + to_string(i);
	}
	for (size_t i = 1; (option == 5 || option == 10) && i < argc - (2 - option % 2); i++) {
		final["SW"][getFileName(argv[i])] = "v" + to_string(i);
	}
	std::ofstream ofs("file.json", std::ofstream::out);
	ofs << setw(4) << final;
	clock_t c_end = clock();
	cerr<<"Tiempo total: "<< 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n" ;
	return 0;
}