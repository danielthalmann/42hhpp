#include "Location.hpp"

namespace hhpp {
	Location::Location() {}

	Location::~Location() {}

	void Location::setPath(const std::string& path) 
	{
		_path = path;
	}

	void Location::setRoot(const std::string& root)
	{
		_root = root;
	}
}
