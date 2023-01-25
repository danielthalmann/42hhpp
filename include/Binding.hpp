#ifndef BINDING_HPP
#define BINDING_HPP

#include "IBinding.hpp"
#include "Request.hpp"
#include <sys/socket.h>
#include <iostream>

class Binding : public IBinding
{

public:

	Binding();
	~Binding();

	virtual void setSocket(int socket);
	virtual void setIP(std::string ip);
	virtual void setPort(int port);
	virtual void send(std::string str);
	virtual void send(Response response);
	virtual Request readHeader(std::string header);

private:

	int _socked;
	std::string _ip;
	int _port;

};

#endif
