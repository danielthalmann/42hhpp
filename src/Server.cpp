#include "Server.hpp"

namespace hhpp {

	Server::Server() 
	{}

	Server::~Server() 
	{}

	void Server::setSocket(const int socket) {
		(void) socket;
	}

	bool Server::isForMe(Request request) {
		(void)request;
		return (true);
	}
	
	void Server::setBinding(IBinding* binding)
	{
		(void) binding;
	}
	
	void Server::setRoot(const std::string& root)
	{
		(void) root;
	}
	
	void Server::addDomain(const std::string& domain)
	{
		(void) domain;
	}
	
	void Server::addIndex(const std::string& index)
	{
		(void) index;
	}
	
	void Server::addRedirect(Redirect* redirect)
	{
		(void) redirect;
	}
	
	void Server::addErrorPage(ErrorPage* errorpage)
	{
		(void) errorpage;
	}
	
	void Server::addLocation(Location* location)
	{
		(void) location;
	}
	
	void Server::setAutoIndex(const bool autoindex)
	{
		(void) autoindex;
	}
	
	void Server::setAccessLog(const std::string& log)
	{
		(void) log;
	}
	
	void Server::setClientMaxBodySize(const int max)
	{
		(void) max;
	}
	
	void Server::addAllowedMethod(const std::string& method)
	{
		(void) method;
	}
	
	void Server::addCGI(CGI* cgi)
	{
		(void) cgi;
	}
	
	void Server::addMimeType(MimeType* mimetype)
	{
		(void) mimetype;
	}

	Response Server::treatRequest(Request request)
	{
		(void) request;
		return Response();
	}
}

