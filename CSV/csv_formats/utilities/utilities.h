#include <string>

const int NUM_NAMES = 17;
const std::string MINERALS_NAMES[NUM_NAMES] = {"cu","fe","cobre","hierro","copper","iron","mo","molibdeno","moli","Molybdenum","moly","au","ag","oro","plata","gold","silver" };
std::string getFileName(const char * fileName);
int validator(int argc, const char * argv[]);
int searchSubstring(std::string name);