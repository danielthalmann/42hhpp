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

	bool Location::match(const std::string& query) const
	{
		if (_path == query)
			return true;
		return false;
	}

	std::string Location::getLocalPath(const std::string& query) const
	{
		std::string path = _root;
		if (query.rfind("titi", 0) == 0) { // pos=0 limits the search to the prefix
		// s starts with prefix
		}
	}



}
