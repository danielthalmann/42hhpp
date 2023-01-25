#include "utility.hpp"

std::vector<std::string> utils::split(std::string str, std::string delimiter) {
	size_t pos;
	std::vector<std::string> vec;

	do {
		pos = str.find(delimiter);
		vec.push_back(str.substr(0, pos));
		str.erase(0, pos + delimiter.length());
	} while (pos != std::string::npos);

	return (vec);
}
