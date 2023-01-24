#include "Server.hpp"

hhpp::Server::Server() {}
hhpp::Server::~Server() {}

void hhpp::Server::setBinding(Binding *bind) {
	_binding = bind;
}

bool hhpp::Server::isForMe(Request request) {
	(void)request;
	return (true);
}

void hhpp::Server::bind(Binding binding) {
	(void)binding;
}

hhpp::Response hhpp::Server::treatRequest(Request request) {
	(void)request;
	return (Response());
}
