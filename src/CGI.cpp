#include "CGI.hpp"

namespace hhpp {
	CGI::CGI() {}
	CGI::~CGI() {}

	std::string CGI::execute(Request request) {
		(void)request;
		return (NULL);
	}

	void CGI::addExtension(const std::string& extension)
	{
		_extension.push_back(extension);
	}

	void CGI::setLocation(const std::string& location)
	{
		_location = location;
	}

	bool CGI::match(const std::string& query) const
	{
		for (std::vector<std::string>::const_iterator it = _extension.begin(); it != _extension.end(); it++) {
			std::string extension = query.substr(query.size() - (*it).size());
			if (extension == (*it))
				return true;
		}
		return false;
	}

}
