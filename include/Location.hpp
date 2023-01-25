#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>

class Location
{

public:

	Location();
	Location(std::string path, std::string root);
	~Location();

private:

	std::string _path;
	std::string _root;

};

#endif
