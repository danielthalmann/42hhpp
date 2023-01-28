#include "Redirect.hpp"

namespace hhpp {

	Redirect::Redirect(std::string& path, std::string& destination, int status) 
	: _path(path), _destination(destination), _status(status)
	{

	}

	Redirect::~Redirect() {}
}
