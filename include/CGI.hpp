#ifndef CGI_HPP
#define CGI_HPP

#include <string>
#include <vector>
#include "Request.hpp"
#include "Request.hpp"

class CGI
{

public:

	CGI();
	~CGI();

	bool isForMe(Request request);
	std::string execute(Request request);
	void addExtension(std::string extension);

private:

	std::vector<std::string> _extension;
	std::string _location;

};

#endif
