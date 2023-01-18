#include "Request.hpp"

Request::Request() {}

Request::~Request() {}

void Request::getPort(int port) {
	(void)port;
}

void Request::setBlob(const std::string &str) {
	(void)str;
}

Header &Request::getHeaders() {
	return (_headers);
}