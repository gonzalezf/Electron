#include <cstdio>
#include <iostream>
#include "basicHandler.h"
int BasicHandler::calc_fibonnacci(int n) {
	std::vector<int> fibonacci;
	fibonacci.push_back(0);
	if (n == 0) {
		return 0;
	}
	fibonacci.push_back(1);
	for (size_t i = 2; i <= n; i++) {
		fibonacci.push_back(fibonacci[i - 1] + fibonacci[i - 2]);
	}
	return fibonacci.back();
}
void  BasicHandler::bobo_sort(float *num, int lenght) {
	float aux;
	for (size_t i = lenght - 1; i > 1; i--) {
		for (size_t j = 0; j < i; j++) {
			if (num[j] > num[j + 1]) {
				aux = num[j];
				num[j] = num[j + 1];
				num[j + 1] = aux;
			}
		}
	}
}
void  BasicHandler::load_points(const char * fileName) {
	float value;
	char *str, line[1024];
	int aux, c;
	FILE *f;
	fopen_s(&f, fileName, "rt");
	int k = 0;
	while (fgets(line, sizeof(line), f)) {
		std::vector<float>point;
		k++;
		c = 0;
		for (int i = 0; i < 3; i++) {
			str = &line[c];
			sscanf_s(str, "%f %n", &value, &aux);
			c += aux;
			point.push_back(value);
		}
		points.resize(points.size() + 1);
		points.back() = point;
	}
	fclose(f);
}
float* BasicHandler::get_point(int index) {
	if (index <0 || index >= points.size()) {
		return NULL;
	}
	return (float*)&points[index][0];

}
float* BasicHandler::get_dimension_points(int dimension) {
	aux.clear();
	if (dimension<1 || dimension>points[0].size()) {
		return NULL;
	}
	for (size_t i = 0; i < points.size(); i++) {
		aux.push_back(points[i][dimension]);
	}
	return (float*)&aux[0];
}
int BasicHandler::hello_string(char *writeTo ,const char * name, int lenght) {
	std::string s = std::string(name);
	strcpy_s(writeTo,lenght,("hola "+s ).c_str());
	return s.size() + 5;
}