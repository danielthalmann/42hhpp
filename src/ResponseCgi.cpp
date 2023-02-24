#include "ResponseCgi.hpp"

namespace hhpp {

	ResponseCgi::ResponseCgi(CGI *cgi, std::string script, const Request *request)
			: Response(), _cgi(cgi), _script(script), _request(request)
	{
		setStatus(501);
		setBody(getStatusMessage());
		setContentType("text/html");
	}

	ResponseCgi::~ResponseCgi()
	{

	}

	void ResponseCgi::prepareResponse() {
		std::string header;
		std::vector<std::string> token;
		std::vector<std::string> headers;
		size_t find;

		find = _body.find("\r\n\r\n");
		if (find == std::string::npos)
			return;

		header = _body.substr(0, find);
		setBody(_body.substr(find));

		token = utils::split(header, "\n");

		for (size_t i = 0; i < token.size(); ++i) {
			headers = utils::split(token[i], ":");
			if (headers.size() == 2)
			{
				_header[utils::upperKebabCase(headers[0])] = utils::trim(headers[1]);
			}
		}
	}
}
