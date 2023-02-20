#include "ResponseCgi.hpp"

namespace hhpp {

	ResponseCgi::ResponseCgi(CGI *cgi, std::string script, const Request *request)
			: Response(), _cgi(cgi), _script(script), _request(request)
	{
		//_cgi = cgi;
		//_request = request;
		setStatus(501);
		setBody(getStatusMessage());
		setContentType("text/plain");

	}

	ResponseCgi::~ResponseCgi()
	{

	}

	std::string ResponseCgi::raw()
	{
		return _cgi->execute(*_request);
	}

	void ResponseCgi::prepareResponse() {

	}

}
