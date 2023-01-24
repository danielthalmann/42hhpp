#ifndef IBINDING_HPP
#define IBINDING_HPP

#include <string>
#include "Request.hpp"
#include "Response.hpp"

namespace hhpp {
	class IBinding
	{

	public:

		virtual ~IBinding() {};

		virtual void setSocket(int socket) = 0;
		virtual void setIP(std::string ip) = 0;
		virtual void setPort(int port) = 0;
		virtual void send(std::string str) = 0;
		virtual void send(Response res) = 0;
		virtual Request readHeader(std::string header) = 0;

	};
}


#endif
