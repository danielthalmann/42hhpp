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

		virtual void setSocket();
		virtual void setIP(const std::string& ip);
		virtual void setPort(const int port);
		virtual void sendData(std::string str);
		virtual void sendData(Response response);
		virtual Request readHeader(std::string header);
		virtual bool isBinding(const std::string& ip, const int port);

		void checkSocket(int ret, const char* str);

	private:
		void createSocket();
		void setNonBlocking();
		sockaddr_in bindSocket();
		void listenSocket();

		int _listen_sd;
		std::string _ip;
		int _port;

	};
}

#endif
