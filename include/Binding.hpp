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
		virtual ~Binding();

		virtual void setSocket();
		virtual void setIP(const std::string& ip);
		virtual void setPort(const int port);

		virtual std::string getIP() const;
		virtual int getPort() const;
		virtual int getSocket() const;

		virtual void sendData(std::string str);
		virtual void sendData(Response response);
		virtual Request readHeader(std::string header);
		virtual bool isBinding(const std::string& ip, const int port);

		void checkSocket(int ret, const char* str);

	private:
		void createSocket();
		void setNonBlocking();
		struct sockaddr_in bindSocket();
		void listenSocket();

		int _listen_sd;
		std::string _ip;
		int _port;

	};
}

#endif
