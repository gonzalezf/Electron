#include "utilities.h"
std::string getFileName(const char * fileName) {
	std::string strFileName = fileName;
	size_t aux;
	while (strFileName.find('/') != std::string::npos) {
		aux = strFileName.find('/');
		strFileName = &strFileName[aux + 1];
	}
	while (strFileName.find('\\') != std::string::npos) {
		aux = strFileName.find('\\');
		strFileName = &strFileName[aux + 1];
	}
	return strFileName;
}
int validator(int argc, const char * argv[]) {
	std::string ERROR_MESSAGE = "Modos de uso:\n    unitDeteccion file1 [fil2][file3]...[FileN] -u \n    unitDeteccion file1 [fil2][file3]...[FileN] [num_decimal] -d \n    unitDeteccion file1 [fil2][file3]...[FileN] [number_letters] -v \n";
	int n, aux;
	size_t exist_optional = 1;
	if (argc < 3) {
		std::cerr << ERROR_MESSAGE;
		return 0;
	}
	if (argv[argc - 1][0] != '-' || strlen(argv[argc - 1]) != 2 || (argv[argc - 1][1] != 'u' && argv[argc - 1][1] != 'd' && argv[argc - 1][1] != 'v')) {
		std::cerr << ERROR_MESSAGE;
		return 0;
	}
	if (argv[argc - 1][1] == 'u') {
		for (size_t i = 1; i < (argc - 1); i++) {
			if (std::string(argv[i]).find(".csv\0") == std::string::npos) {
				std::cerr << "El archivo numero " << i << " no tiene formato csv\n";
				return 0;
			}
		}
		return 1;
	}
	else {
		if (std::string(argv[argc - 2]).find(".csv\0") == std::string::npos) {
			exist_optional = 2;
			if (sscanf_s(argv[argc - 2], "%i %n", &n, &aux)) {
				if (argv[argc - 2][aux] != '\0') {
					if (argv[argc - 1][1] != 'd') {
						std::cerr << "El valor opcional number_letters debe ser entero positivo\n";
						return 0;
					}
					else {
						std::cerr << "El valor opcional num_decimal debe ser entero positivo\n";
						return 0;
					}
				}
				else if (n < 0) {
					if (argv[argc - 1][1] != 'd') {
						std::cerr << "El valor opcional number_letters debe ser entero positivo\n";
						return 0;
					}
					else {
						std::cerr << "El valor opcional num_decimal debe ser entero positivo\n";
						return 0;
					}
				}
			}
			else {
				if (argv[argc - 1][1] != 'd') {
					std::cerr << "El valor opcional num_decimal debe ser entero positivo\n";
					return 0;
				}
				else {
					std::cerr << "El valor opcional number_letters debe ser entero positivo\n";
					return 0;
				}

			}
		}
		for (size_t i = 1; i < (argc -exist_optional ); i++) {
			if (std::string(argv[i]).find(".csv\0") == std::string::npos) {
				std::cerr << "El archivo numero " << i << " no tiene formato csv\n";
				return 0;
			}
		}
		if (argv[argc - 1][1] != 'v') {
			return exist_optional * 3;
		}
		return exist_optional * 5;
	}
}