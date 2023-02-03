#ifndef RESPONSECGI_HPP
#define RESPONSECGI_HPP

#include <AResponse.hpp>
#include <CGI.hpp>
#include <string>

namespace hhpp {
	class ResponseCgi: public AResponse
	{
	public:
		ResponseCgi(CGI *cgi, const Request &request);
		~ResponseCgi();

	private:

	};
}

#endif
