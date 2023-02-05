#ifndef RESPONSECGI_HPP
#define RESPONSECGI_HPP

#include <Response.hpp>
#include <CGI.hpp>
#include <string>

namespace hhpp {
	class ResponseCgi: public Response
	{
	public:
		ResponseCgi(CGI *cgi, const Request &request);
		~ResponseCgi();

	private:

	};
}

#endif
