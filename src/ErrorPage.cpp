#include "ErrorPage.hpp"

namespace hhpp {

	ErrorPage::ErrorPage() 
	: _status(0), _location("") 
	{

	}

	ErrorPage::~ErrorPage() {}

	std::string ErrorPage::getPage() {
		return (NULL);
	}

	void ErrorPage::setStatus(const int status)
	{
		_status = status;
	}

	void ErrorPage::setLocation(const std::string& location)
	{
		_location = location;
	}

}
