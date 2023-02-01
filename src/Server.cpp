#include "Server.hpp"

namespace hhpp {

	Server::Server() 
	{
		// default value
		_autoIndex = false;
		_maxBodySize = 0;
	}

	Server::~Server() 
	{
		for (std::vector<CGI*>::iterator it = _cgi.begin(); it != _cgi.end() ; ++it) {
			delete (*it);
		}

		for (std::vector<Location*>::iterator it = _locations.begin(); it != _locations.end() ; ++it) {
			delete (*it);
		}

		for (std::vector<Redirect*>::iterator it = _redirect.begin(); it != _redirect.end() ; ++it) {
			delete (*it);
		}

		for (std::vector<ErrorPage*>::iterator it = _errorPages.begin(); it != _errorPages.end() ; ++it) {
			delete (*it);
		}

	}

	void Server::setSocket(const int socket) {
		(void) socket;
	}

	void Server::setBinding(IBinding* binding)
	{
		_binding = binding;
	}
	
	void Server::setRoot(const std::string& root)
	{
		_root = root;
	}
	
	void Server::addDomain(const std::string& domain)
	{
		_domains.push_back(domain);
	}
	
	void Server::addIndex(const std::string& index)
	{
		_indexes.push_back(index);
	}
	
	void Server::addRedirect(Redirect* redirect)
	{
		_redirect.push_back(redirect);
	}
	
	void Server::addErrorPage(ErrorPage* errorpage)
	{
		_errorPages.push_back(errorpage);
	}
	
	void Server::addLocation(Location* location)
	{
		_locations.push_back(location);
	}
	
	void Server::setAutoIndex(const bool autoindex)
	{
		_autoIndex = autoindex;
	}
	
	void Server::setAccessLog(const std::string& log)
	{
		_accessLog = log;
	}
	
	void Server::setClientMaxBodySize(const int max)
	{
		_maxBodySize = max;
	}
	
	void Server::addAllowedMethod(const std::string& method)
	{
		_allowedMethods.push_back(method);
	}
	
	void Server::addCGI(CGI* cgi)
	{
		_cgi.push_back(cgi);
	}
	
	void Server::addMimeType(const std::string& mimeType, const std::string& extension)
	{
		_mimetypes[extension] = mimeType;
	}


	bool Server::isForMe(const Request& request) const 
	{
		for (std::vector<std::string>::const_iterator it; it != _domains.end(); it++) {
			if (request.getHost() == (*it)) {
				return true;
			}
		}
		return false;
	}

	bool Server::isAllowedMethod(const std::string& method) const 
	{
		for (std::vector<std::string>::const_iterator it; it != _allowedMethods.end(); it++) {
			if (method == (*it)) {
				return true;
			}
		}
		return false;	
	}


	Redirect* Server::getUrlRedirect(const std::string& query) const 
	{
		for (std::vector<Redirect*>::const_iterator it; it != _redirect.end(); it++) {
			if ((*it)->match(query)) {
				return (*it);
			}
		}
		return NULL;	
	}

	std::string Server::getLocalPath(const std::string& query) const
	{
		for (std::vector<Location*>::const_iterator it; it != _locations.end(); it++) {
			if ((*it)->match(query)) {
				return (*it)->getLocalPath(query);
			}
		}
		
	}

	Response Server::treatRequest(const Request& request)
	{
		// check allowed method
		if (!isAllowedMethod(request.getMethod()))
			return ResponseError(405);

		// check size
		if (_maxBodySize > 0) {
			// TODO check size of body and return error
		}

		// search url in redirect path
		if (Redirect *redirect = getUrlRedirect(request.getQueryLocation()) ) {
			return ResponseRedirect(redirect->getDestination(), redirect->getStatus());
		}

		// search url in location path
		std::string localPath = getLocalPath(request.getQueryLocation());

		return Response();
	}
}

