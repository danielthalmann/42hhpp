#include "ErrorPage.hpp"
namespace hhpp {

	ErrorPage::ErrorPage() 
	: _status(0), _location("") 
	{

	}

	ErrorPage::~ErrorPage() {}

	std::string ErrorPage::getPage(std::string root) {
		std::string page;

		if (_location.empty())
			page.append("<html><head>"
							"<title>The page you were looking for doesn't exist (404)</title>"
							"<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
							"</head><body>"
							"<h1>Error 404: Not Found</h1>"
							"<p>Oops! Something went wrong...</p>"
							"<p>We seem to be having some technical difficulties. Hang tight.</p>"
							"</body></html>");
		else
			page = utils::readFile(utils::path(root, _location));

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
