#include "ResponseCgi.hpp"

namespace hhpp {

	ResponseCgi::ResponseCgi(CGI *cgi, const Request &request) : AResponse() 
    {
        (void) cgi;
        (void) request;
        
    }

	ResponseCgi::~ResponseCgi() 
    {

    }

}
