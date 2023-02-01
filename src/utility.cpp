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

char** utils::mapStringToArray(const std::map<std::string, std::string> &m)
{
	char **a;
	char *s;
	int pos;

	a = new char*[m.size() + 1];
	a[m.size()] = 0;

	for (std::map<std::string, std::string>::const_iterator i = m.begin(); i != m.end(); i++)
	{
		int size = i->first.size() + i->second.size() + 1;
		s = new char[size + 1];
		s[size] = 0;
		pos = 0;

		for(int j = 0; j < i->first.size(); j++) {
			s[pos++] = i->first[j]; 
		}
		s[pos++] = '=';
		for(int j = 0; j < i->second.size(); j++) {
			s[pos++] = i->second[j]; 
		}
	}
	
}
