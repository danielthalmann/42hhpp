#include "Server.hpp"

Server::Server() {}
Server::~Server() {}

void Server::setBinding(Binding *bind) {
	_binding = bind;
}

bool Server::isForMe(Request request) {
	(void)request;
	return (true);
}

void Server::bind(Binding binding) {
	(void)binding;
}

Response Server::treatRequest(Request request) {
	(void)request;
	return (Response());
}