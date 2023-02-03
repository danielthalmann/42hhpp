#ifndef ISERVER_HPP
#define ISERVER_HPP

#include "Request.hpp"
#include "Binding.hpp"
#include "Response.hpp"
#include "Redirect.hpp"
#include "Location.hpp"
#include "ErrorPage.hpp"
#include "CGI.hpp"
#include "MimeType.hpp"

namespace hhpp {
	class IServer
	{

	public:

		IServer() {};
		virtual ~IServer() {};

		virtual bool isForMe(const Request& request) const = 0;
		virtual void setBinding(IBinding* binding) = 0;
		virtual void setRoot(const std::string& root) = 0;
		virtual void addDomain(const std::string& domain) = 0;
		virtual void addIndex(const std::string& index) = 0;
		virtual void addRedirect(Redirect* redirect) = 0;
		virtual void addErrorPage(ErrorPage* errorpage) = 0;
		virtual void addLocation(Location* location) = 0;
		virtual void setAutoIndex(const bool autoindex) = 0;
		virtual void setAccessLog(const std::string& log) = 0;
		virtual void setClientMaxBodySize(const int max) = 0;
		virtual void addAllowedMethod(const std::string& method) = 0;
		virtual void addCGI(CGI* cgi) = 0;
		virtual void addMimeType(const std::string& mimeType, const std::string& extension) = 0;
		virtual AResponse* treatRequest(const Request& request) = 0;

	};
}

#endif
