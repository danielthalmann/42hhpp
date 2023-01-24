#include "CGI.hpp"

hhpp::CGI::CGI() {}
hhpp::CGI::~CGI() {}

bool hhpp::CGI::isForMe(Request request) {
	(void)request;
	return (true);
}

std::string hhpp::CGI::execute(Request request) {
	(void)request;
	return (NULL);
}

void hhpp::CGI::addExtension(std::string extension) {
	(void)extension;
}
