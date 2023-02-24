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
		std::vector<std::string> statuses;
		size_t find;
		std::string result;

		try {
			result = _cgi->execute(_script, *_request);
			std::cout << result;
		} catch (...)
		{

		}
		
		setStatus(200);

		find = result.find("\r\n\r\n");
		if (find == std::string::npos)
		{
			setBody(result);
			return;
		}

		header = result.substr(0, find);

		setBody(result.substr(find));

		token = utils::split(header, "\r\n");

		for (size_t i = 0; i < token.size(); ++i) 
		{
			headers = utils::split(token[i], ":");
			if (headers.size() == 2)
			{
				_header[utils::upperKebabCase(headers[0])] = utils::trim(headers[1]);
			}
		}
		std::string strStatus = _header.get("Status");
		if (strStatus.size() > 0)
		{
			statuses = utils::split(strStatus, " ");
			setStatus(std::atoi(statuses[0].c_str()));

		}
	}
}
