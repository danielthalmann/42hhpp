#include "ResponseCgi.hpp"

namespace hhpp {

	ResponseCgi::ResponseCgi(CGI *cgi, std::string script, const Request *request)
			: Response(), _cgi(cgi), _script(script), _request(request)
	{
//		_cgi = cgi;
//		_request = request;
		setStatus(501);
		setBody(getStatusMessage());
		setContentType("text/plain");

	}

	ResponseCgi::~ResponseCgi()
	{

	}

	std::string ResponseCgi::raw()
	{
//		prepareResponse();
//
		std::string statusMessage;
		int status = _status;

		try {
			statusMessage = _totalStatus.at(status);
		} catch (std::exception &e) {
			status = 200;
			statusMessage = "OK";
		}

		std::string dataSend;
		dataSend.append("HTTP/1.1");
		dataSend.append(" ");
		dataSend.append(utils::numberToString(status));
		dataSend.append(" ");
		dataSend.append(statusMessage);
		dataSend.append("\n");
		dataSend.append(_header.raw());
		dataSend.append("\n");
//		dataSend.append(_body);
//
//		return dataSend;


//		std::cout << "raw cgi" << std::endl;

		dataSend.append(_cgi->execute(_script, *_request));
//		std::cout << dataSend << std::endl;

		return dataSend;
	}

	void ResponseCgi::prepareResponse() {

	}

}
