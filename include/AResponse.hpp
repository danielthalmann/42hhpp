#ifndef ARESPONSE_HPP
#define ARESPONSE_HPP

#include <string>
#include "Header.hpp"

class AResponse
{

public:

	AResponse();
	virtual ~AResponse();

	void setStatus(int status);
	std::string getBlob();
	Header& headers();


protected:

	int _status;
	Header _header;


};

#endif
