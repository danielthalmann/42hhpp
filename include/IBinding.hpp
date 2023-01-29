#ifndef IBINDING_HPP
#define IBINDING_HPP

#include <string>
#include "Request.hpp"
#include "Response.hpp"

namespace hhpp {
	class IBinding
	{

	public:

		IBinding() {}
		virtual ~IBinding()
		{};

		virtual void setSocket(const int socket) = 0;
		virtual void setIP(const std::string& ip) = 0;
		virtual void setPort(const int port) = 0;
		virtual bool isBinding(const std::string& ip, const int port) = 0;
		virtual void send(std::string str) = 0;
		virtual void send(Response res) = 0;
		virtual Request readHeader(std::string header) = 0;

	};
}


#endif
