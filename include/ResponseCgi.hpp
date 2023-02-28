#ifndef RESPONSECGI_HPP
#define RESPONSECGI_HPP

#include <CGI.hpp>
#include <Response.hpp>
#include <string>

namespace hhpp
{

	class ResponseCgi : public Response
	{
	public:
		ResponseCgi(CGI *cgi, std::string script, const Request *request);
		~ResponseCgi();

	protected:
		void prepareResponse();

	private:
		CGI *_cgi;
		std::string _script;
		const Request *_request;
	};
} // namespace hhpp

#endif
