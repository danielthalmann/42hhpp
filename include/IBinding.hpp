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

		virtual void setSocket() = 0;
		virtual void setIP(std::string ip) = 0;
		virtual void setPort(int port) = 0;
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
