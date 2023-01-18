#include "Binding.hpp"

Binding::Binding() {}

Binding::~Binding() {}

void Binding::setSocket(int socket) {
	(void)socket;
}

void Binding::setIP(std::string ip) {
	(void)ip;
}

void Binding::setPort(int port) {
	(void)port;
}

void Binding::send(std::string str) {
	(void)str;
}

void Binding::send(Response response) {
	(void)response;
}

Request Binding::readHeader(std::string header) {
	(void)header;
	return (Request());
}
