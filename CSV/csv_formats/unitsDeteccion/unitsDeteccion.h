#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "json.hpp"
const int NUM_NAMES = 17;
const std::string MINERALS_NAMES[NUM_NAMES] = { "cu","mo","fe","cobre","molibdeno","moli","hierro","au","ag","oro","plata","copper","Molybdenum","moly","iron","gold","silver"};
nlohmann::json unitDeteccion(const char * fileName);