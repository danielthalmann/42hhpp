#ifndef UTILITY_HPP
# define UTILITY_HPP

# include <vector>
# include <string>
//# include <iostream>
#include <sstream>

namespace utils {
	std::vector<std::string> split(std::string str, std::string delimiter);

	template <typename T>
	std::string numberToString(T pNumber)
	{
		std::ostringstream oss;
		oss << pNumber;
		return oss.str();
	}
}

#endif
