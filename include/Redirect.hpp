#ifndef REDIRECT_HPP
#define REDIRECT_HPP

#include <string>

class Redirect
{

public:

	Redirect();
	~Redirect();

private:

	std::string _path;
	std::string _destination;
	int _status;

};

#endif
