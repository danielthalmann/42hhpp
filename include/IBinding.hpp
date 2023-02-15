#ifndef IBINDING_HPP
#define IBINDING_HPP

#include <string>
#include "Request.hpp"

namespace hhpp {
	
	class IServer;

	class Response;

	class IBinding
	{

	public:

//		IBinding() {};
		virtual ~IBinding() {};

		virtual void setSocket() = 0;
		virtual void setIP(const std::string& ip) = 0;
		virtual void setPort(const int port) = 0;
		virtual void addServer(IServer* server) = 0;
		virtual int acceptConnection() = 0;
		virtual void closeConnection(int socket) = 0; 
		virtual bool hasConnection(const int socket) = 0;
		virtual IServer* getServerFor(const Request& request) const = 0;

		virtual std::string getIP() const = 0;
		virtual int getPort() const = 0;
		virtual int getSocket() const = 0;

		virtual bool isBinding(const std::string& ip, const int port) = 0;
		virtual void sendData(std::string str) = 0;
		virtual void sendData(Response response) = 0;
		virtual Request readHeader(std::string header) = 0;

		class socketStatus: public std::exception {
		public:
			virtual const char* what() const throw();
		};
	};
}


#endif
