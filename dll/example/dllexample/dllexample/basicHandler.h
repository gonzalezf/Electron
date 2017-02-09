#include <vector>
#include <string>

class BasicHandler {
private:
	std::vector<std::vector<float>> points;
	std::vector<float> aux;
public:
	int calc_fibonnacci(int n);
	void bobo_sort(float *num, int lenght);
	void load_points(const char * fileName);
	float* get_point(int index);
	float* get_dimension_points(int dimension);
	int hello_string(char *writeTo, const char * name, int  lenght);
};
