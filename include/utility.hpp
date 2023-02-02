#ifndef UTILITY_HPP
# define UTILITY_HPP

# include <vector>
# include <map>
# include <string>
//# include <iostream>
#include <sstream>

#include <fstream>
#include <unistd.h>
#include <sys/stat.h>

namespace utils {
	std::vector<std::string> split(std::string str, std::string delimiter);

	char** mapStringToArray(const std::map<std::string, std::string> &m);
	void freeArray(char** a);
	std::string readFile(std::string path);
	std::string getTime();

	template <typename T>
	std::string numberToString(T nbr)
	{
		std::ostringstream oss;
		oss << nbr;
		return oss.str();
	}

}

#endif
