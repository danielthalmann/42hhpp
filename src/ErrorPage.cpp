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

		page.append("<html><head>"
					"<title>The page you were looking for doesn't exist (404)</title>"
					"<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
					"</head><body>"
					"<h1>Error 404: Not Found</h1>"
					"<p>The page you were looking for doesn't exist</p>"
					"<img src=\"https://www.lesdebrouillards.com/wp-content/uploads/2019/10/Pigeon-1.jpg\" alt=\"Pigeon with 404 message\" width=\"500\" height=\"600\">"
					"</body></html>");

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
