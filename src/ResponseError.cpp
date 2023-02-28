#include "ResponseError.hpp"
#include "utility.hpp"

namespace hhpp
{
	ResponseError::ResponseError(int error) : Response()
	{
		std::string page;

		setStatus(error);

		if (_status == 404)
		{
			page = get404();
		}
		else
		{
			std::string errorMsg = "Error " + utils::numberToString(_status) + ": " + _statusMessage;

			page.append("<html><head>"
			            "<title>" +
			            errorMsg +
			            "</title>"
			            "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
			            "</head><body>"
			            "<h1>" +
			            errorMsg +
			            "</h1>"
			            "<p>Oops! Something went wrong...</p>"
			            "</body></html>");
		}
		setBody(page);
		setContentType("text/html");
	}

	ResponseError::~ResponseError()
	{
	}

	void ResponseError::prepareResponse()
	{
		std::string page;

		for (size_t i = 0; i < _server->getErrorPages().size(); ++i)
		{
			if (_server->getErrorPages()[i]->getStatus() == _status)
			{
				setContentType("text/html");
				if (!_server->getErrorPages()[i]->getPage(_server->getRoot()).empty())
					page = _server->getErrorPages()[i]->getPage(_server->getRoot());
				else
					page = get404();
				setBody(page);
				break;
			}
		}
	}

} // namespace hhpp
