#include "ErrorPage.hpp"

namespace hhpp {

	ErrorPage::ErrorPage(const int status, const std::string& location) 
	: _status(status), _location(location) 
	{

	}

	ErrorPage::~ErrorPage() {}

	std::string ErrorPage::getPage() {
		return (NULL);
	}
}
