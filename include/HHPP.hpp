#ifndef HHPP_HPP
#define HHPP_HPP

#include <string>
#include "Server.hpp"
#include "Binding.hpp"
#include "Request.hpp"

class HHPP
{

public:

	HHPP();
	~HHPP();

	vector<IServer> _servers;
	vector<IBinding> _bindings;
	void loadConfig(std::string config);
	void run();

private:

	void dispatchRequest(Request request);

};

#endif
