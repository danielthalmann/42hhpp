#include "ResponseCgi.hpp"

namespace hhpp {

	ResponseCgi::ResponseCgi(CGI *cgi, const Request &request) 
    : Response() 
    {
        (void) cgi;
        (void) request;
		setStatus(501);
		setBody(getStatusMessage());
		setContentType("text/plain");

    }

	ResponseCgi::~ResponseCgi() 
    {

    }

}
