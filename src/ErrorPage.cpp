#include "ErrorPage.hpp"
#include <iostream>
namespace hhpp {

	ErrorPage::ErrorPage() 
	: _status(0), _location("") 
	{

	}

	ErrorPage::~ErrorPage() {}

	std::string ErrorPage::getPage(std::string root) {
		std::string page;

		try
		{
			page = utils::readFile(utils::path(root, _location));
		}
		catch (...)
		{
			return (page);
		}

		return (page);
	}

	void ErrorPage::setStatus(const int status)
	{
		_status = status;
	}

	void ErrorPage::setLocation(const std::string& location)
	{
		_location = location;
	}

	int ErrorPage::getStatus() {
		return _status;
	}

}
