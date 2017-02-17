#include "unitsDeteccion.h"
bool searchSubstring(std::string name) {
	//std::string lower_name = name;
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	for (size_t i = 0; i < NUM_NAMES; i++){
		if (name.find(MINERALS_NAMES[i])!= std::string::npos) {
			return true;
		}
	}
	return false;
}
nlohmann::json unitDeteccion(const char * fileName) {
	std::vector<std::string> types, units, columnName;
	std::vector<std::vector<long>> arrayCounters;
	std::vector<bool> percent_flag;
	//0->int 1->float 2->string 3-> null
	std::vector<long> counterColumns = { 0,0,0,0,0 };
	char *str, line[1024], str_readed[1024];
	int c, numCharReaded = 0, numCharReaded2, totalColumns = 0;
	long value = 0, value2;
	double f_value;
	FILE *f;
	fopen_s(&f, fileName, "rt");
	if (!f) {
		std::cerr << "No se puden abrir el archivo de datos: " << fileName <<std::endl;
		throw std::exception();
	}
	fgets(line, sizeof(line), f);
	c = 0;
	str = &line[c];
	while (true) {
		totalColumns++;
		sscanf(str, "%[^,] %n", &str_readed, &numCharReaded);
		arrayCounters.push_back(counterColumns);
		c += numCharReaded + 1;
		
		if (line[c - 1] == '\0') {
			str_readed[numCharReaded - 1] = '\0';
			columnName.push_back(std::string(str_readed));
			percent_flag.push_back(true);
			break;
		}
		columnName.push_back(std::string(str_readed));
		percent_flag.push_back(true);
		str = &line[c];
	}
	fgets(line, sizeof(line), f);
	while (fgets(line, sizeof(line), f)) {
		c = 0;
		int k = 0;
		str = &line[c];
		while (true) {
			if (sscanf(str, "%i %n", &value, &numCharReaded)) {
				if (str[numCharReaded] == ',' || str[numCharReaded + 1] == '\0') {
					if (f_value < 0) {
						arrayCounters[k][3]++;
					}
					else {
						arrayCounters[k][0]++;
					}
				}
				else {
					if (str[numCharReaded] != '.') {
						sscanf(str, "%[^,] %n", &str_readed, &numCharReaded);
						arrayCounters[k][2]++;
					}
					else {
						sscanf(&str[numCharReaded + 1], "%i %n", &value2, &numCharReaded2);
						if (value2==0) {
							arrayCounters[k][0]++;
							numCharReaded += numCharReaded2+1;
						}
						else {
							sscanf(str, "%lf %n", &f_value, &numCharReaded);
							if (f_value < 0) {
								arrayCounters[k][3]++;
							}
							else {
								arrayCounters[k][1]++;
								
								if (percent_flag[k] && f_value>100) {
									percent_flag[k] = false;
								}
							}
						}
					}
				}
			}
			else {
				sscanf(str, "%[^,] %n", &str_readed, &numCharReaded);
				arrayCounters[k][2]++;
			}
			c += numCharReaded + 1;
			k++;
			if (line[c - 1] == '\0' || k == totalColumns) {
				break;
			}
			str = &line[c];
		}
	}
	std::fclose(f);
	nlohmann::json file;
	for (size_t i = 0; i<(size_t) totalColumns; i++){
		if (arrayCounters[i][1] > arrayCounters[i][0] && arrayCounters[i][1] > arrayCounters[i][2]) {
			types.push_back("Continuous");
			if (percent_flag[i]) {
				if (searchSubstring(columnName[i])) {
					units.push_back("%");
				}
				else {
					units.push_back("t/m^3");
				}
			}
			else {
				units.push_back("PPM (eje)");
			}
			
		}
		else if (arrayCounters[i][2] > arrayCounters[i][0]) {
			types.push_back("Categorical");
			units.push_back("''");
		}
		else {
			if (searchSubstring(columnName[i])) {
				types.push_back("Continuous");
				units.push_back("ppm");
			}
			else {
				types.push_back("Categorical");
				units.push_back("''");
			}
			
		}
	}
	file["header"] = columnName;
	file["types"] = types;
	file["units"] = units;
	return file;
}