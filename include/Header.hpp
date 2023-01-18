#ifndef HEADER_HPP
#define HEADER_HPP

#include <string>
#include <map>

class Header
{

public:

	Header();
	~Header();

	std::string get(std::string key);
	void remove(std::string key);
	void append(std::string key, std::string value);

private:

	std::map<std::string, std::string> _params;

};

#endif
