#ifndef BINDING_HPP
#define BINDING_HPP

#include "IBinding.hpp"
#include "Request.hpp"

#include <iostream>
#include <unistd.h>

#include <arpa/inet.h>
#include <cstring>

#include <fcntl.h>
#include <sys/socket.h>
#include <string>
#include <sstream>
#include <cerrno>
#include <cstdio>

namespace hhpp {
	class Binding : public IBinding
	{

	public:
		Binding();
		~Binding();

		virtual void setSocket();
		virtual void setIP(std::string ip);
		virtual void setPort(int port);
		virtual void sendData(std::string str);
		virtual void sendData(Response response);
		virtual Request readHeader(std::string header);

		void checkSocket(int ret, const char* str);

	private:
		int _listen_sd;
		std::string _ip;
		int _port;

	};
}

#endif
