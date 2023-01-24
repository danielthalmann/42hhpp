#include "Binding.hpp"

hhpp::Binding::Binding() {}

hhpp::Binding::~Binding() {}

void hhpp::Binding::setSocket(int socket) {
	_socked = socket;
//	_socked = socket(PF_INET, SOCK_STREAM, 0);
//	if (_socked < 0)
//	{
//		std::cerr << "[-] socket error creation" << std::endl;
//		exit(errno);
//	}
}

void hhpp::Binding::setIP(std::string ip) {
	_ip = ip;
}

void hhpp::Binding::setPort(int port) {
	_port = port;
}

void hhpp::Binding::send(std::string str) {
	(void)str;
}

void hhpp::Binding::send(Response response) {
	(void)response;
}

hhpp::Request hhpp::Binding::readHeader(std::string header) {
	(void)header;
	return (Request());
}
