#include "ResponseCgi.hpp"

namespace hhpp {

	ResponseCgi::ResponseCgi(CGI *cgi, const Request *request) 
    : Response(), _cgi(cgi), _request(request) 
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

  	std::string ResponseCgi::raw() const
	{
        return _cgi->execute(*_request);
    }  

}
