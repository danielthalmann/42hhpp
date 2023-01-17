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

	bool isForMe(Request req);
	std::string execute(Request req);
	void addExtension(std::string ext);
	std::string execute(Request res);

private:

	std::vector<std::string> _extension;
	std::string _location;

};

#endif
