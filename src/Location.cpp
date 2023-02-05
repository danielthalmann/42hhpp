#include "Location.hpp"
#include "utility.hpp"

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
		if (_path == query.substr(0, _path.size()))
			return true;
		return false;
	}


	// query : /script/test.cgi
	// /var/www/cgi/test.cgi
	std::string Location::getLocalPath(const std::string& query) const
	{
		return utils::path(_root, query.substr(_path.size()));
	}

}
