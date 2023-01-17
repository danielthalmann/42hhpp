#ifndef ARESPONSE_HPP
#define ARESPONSE_HPP

#include <string>
#include "Header.hpp"

class AResponse
{

public:

	void setStatus(int status);
	std::string getBlob();
	Header& headers();


private:

	int _status;
	Header _header;


};

#endif
