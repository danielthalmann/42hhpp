#include "CGI.hpp"

CGI::CGI() {}
CGI::~CGI() {}

bool CGI::isForMe(Request request) {
	(void)request;
	return (true);
}

std::string CGI::execute(Request request) {
	(void)request;
	return (NULL);
}

void CGI::addExtension(std::string extension) {
	(void)extension;
}
