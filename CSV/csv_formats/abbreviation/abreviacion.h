// for convenience
#include "json.hpp"
#include <string>
using json = nlohmann::json;



bool replaceSubString(std::string& str, const std::string& from, const std::string& to);
json AbreviarArchivo(std::string file_name, int cantidad_caracteres);