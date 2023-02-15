#ifndef RESPONSECGI_HPP
#define RESPONSECGI_HPP

#include <Response.hpp>
#include <CGI.hpp>
#include <string>

namespace hhpp {

	class ResponseCgi: public Response
	{
	public:
		ResponseCgi(CGI *cgi, std::string script, const Request *request);
		~ResponseCgi();

		virtual std::string raw();

	protected:
		void prepareResponse();

	private:

		CGI *_cgi;
		std::string _script;
		const Request *_request;

	};
}

#endif
