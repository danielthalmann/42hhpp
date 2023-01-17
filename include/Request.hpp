#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include "Header.hpp"

class Request
{

public:

	std::string _method;
	std::string _query;
	std::string _host;
	int _port;
	std::string _url;
	std::string _body;
	std::string _httpVersion;

	void getPort(int port);
	void setBlob(const std::string& str);
	Header& getHeaders();

private:

	Header _headers;

};

#endif
