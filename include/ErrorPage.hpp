#ifndef ERRORPAGE_HPP
#define ERRORPAGE_HPP

#include <string>

class ErrorPage
{

public:

	ErrorPage();
	~ErrorPage();

	std::string getPage(void);

	int status;
	std::string location;

};

#endif