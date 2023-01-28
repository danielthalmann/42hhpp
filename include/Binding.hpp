#ifndef BINDING_HPP
#define BINDING_HPP

#include "IBinding.hpp"
#include "Request.hpp"
#include <sys/socket.h>
#include <iostream>

namespace hhpp {
	class Binding : public IBinding
	{

	public:

		Binding();
		~Binding();

		virtual void setSocket(const int socket);
		virtual void setIP(const std::string& ip);
		virtual void setPort(const int port);
		virtual void send(std::string str);
//		virtual void send(AResponse response);
		virtual Request readHeader(std::string header);

	private:

		int _socked;
		std::string _ip;
		int _port;

	};
}

#endif
