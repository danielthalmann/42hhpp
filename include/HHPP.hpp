#ifndef HHPP_HPP
#define HHPP_HPP

#include <string>
#include <algorithm>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>

#include "Server.hpp"
#include "Binding.hpp"
#include "Request.hpp"

namespace json { class JsonValue; } // TODO a supprimer

class HHPP
{

public:

	HHPP();
	~HHPP();

	void loadConfig(std::string pathConfig);
	void run();

private:

	std::vector<IServer*> _servers;
	std::vector<IBinding*> _bindings;

	std::string readFileConfig(std::string pathConfig);
	void dispatchRequest(Request request);

};

#endif
