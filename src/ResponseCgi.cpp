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

	std::string ResponseCgi::raw()
	{

		std::string statusMessage;
		int status = _status;

		try {
			statusMessage = _totalStatus.at(status);
		} catch (std::exception &e) {
			status = 200;
			statusMessage = "OK";
		}

		setBody(_cgi->execute(_script, *_request));

		prepareResponse();

		status = 200;
		statusMessage = "OK";
		setStatus(status);

		std::string dataSend;

		dataSend.append("HTTP/1.1");
		dataSend.append(" ");
		dataSend.append(utils::numberToString(status));
		dataSend.append(" ");
		dataSend.append(statusMessage);
		dataSend.append("\n");
		dataSend.append(_header.raw());
		dataSend.append("\n");
		dataSend.append(_body);

		return dataSend;
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
