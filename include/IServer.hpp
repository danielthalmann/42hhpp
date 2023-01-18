#ifndef ISERVER_HPP
#define ISERVER_HPP

#include "Request.hpp"
#include "Binding.hpp"
#include "Response.hpp"

class IServer
{

public:

	virtual ~IServer() {};

	virtual bool isForMe(Request request) = 0;
	virtual void bind(Binding binding) = 0;
	virtual Response treatRequest(Request request) = 0;

};

#endif
