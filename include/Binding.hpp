#ifndef BINDING_HPP
#define BINDING_HPP

#include "IBinding.hpp"

class Binding : public IBinding
{

public:

	Binding();
	~Binding();

	virtual void setSocket(int socket);
	virtual void setIP(std::string ip);
	virtual void setPort(int port);
	virtual void send(std::string str);
	virtual void send(Response res);
	virtual Request readHeader(std::string header);

private:

	int _socked;
	std::string _ip;
	int _port;

};

#endif
