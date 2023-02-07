#include "Server.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "utility.hpp"

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

		for (std::map<std::string, MimeType*>::iterator it = _mimetypes.begin(); it != _mimetypes.end() ; ++it) {
			delete (it->second);
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
	
	void Server::addMimeType(MimeType* mime)
	{
		_mimetypes[mime->getExtension()] = mime;
	}


	bool Server::isForMe(const Request& request) const 
	{
		for (std::vector<std::string>::const_iterator it = _domains.begin(); it != _domains.end(); it++) {
			if (request.getHost() == (*it)) {
				return true;
			}
		}
		return false;
	}

	bool Server::isAllowedMethod(const std::string& method) const 
	{
		for (std::vector<std::string>::const_iterator it = _allowedMethods.begin(); it != _allowedMethods.end(); it++) {
			if (method == (*it)) {
				return true;
			}
		}
		return false;	
	}


	Redirect* Server::getUrlRedirect(const std::string& query) const 
	{
		for (std::vector<Redirect*>::const_iterator it = _redirect.begin(); it != _redirect.end(); it++) {
			if ((*it)->match(query)) {
				return (*it);
			}
		}
		return NULL;	
	}

	std::string Server::getLocalPath(const std::string& query) const
	{
		// TODO controle des / entre les path
		for (std::vector<Location*>::const_iterator it = _locations.begin(); it != _locations.end(); it++) {
			if ((*it)->match(query)) {
				return (*it)->getLocalPath(query);
			}
		}

		return utils::path(_root, query);

	}

	Response* Server::fileListIndex(const std::string& query) const
	{
		Response* r = new Response(); 
		r->setBody(query);
		return r;
	}


	CGI* Server::getCgi(const std::string& query) const 
	{
		for (std::vector<CGI*>::const_iterator it = _cgi.begin(); it != _cgi.end(); it++) {
			if ((*it)->match(query)) {
				return (*it);
			}
		}
		return NULL;	
	}


	MimeType* Server::getMimeType(const std::string& query) const 
	{
		//TODO utiliser le map aulieu de faire un parcours de tous les éléments

		for (std::map<std::string, MimeType*>::const_iterator it = _mimetypes.begin(); it != _mimetypes.end(); it++) {
			if (it->second->match(query)) {
				return (it->second);
			}
		}
		return NULL;	
	}

	Response* Server::treatRequest(const Request& request)
	{
		std::string localPath;

		// check allowed method
		if (!isAllowedMethod(request.getMethod()))
			return new ResponseError(405);

		// check size
		if (_maxBodySize > 0) {
			if (request.getBodySize() > _maxBodySize) {
				return new ResponseError(413);
			}
		}

		// search url in redirect path
		if (Redirect *redirect = getUrlRedirect(request.getUrl()) ) {
			return new ResponseRedirect(redirect->getDestination(), redirect->getStatus());
		}

		// search url in location path
		localPath = getLocalPath(request.getUrl());

		struct stat sb;
		std::cout << localPath << std::endl;

		if (stat(localPath.c_str(), &sb))
			return new ResponseError(404);

		// is folder
		if ((sb.st_mode & S_IFMT) == S_IFDIR) {
			
			bool indexFound = false;
			for (std::vector<std::string>::const_iterator it = _indexes.begin(); it != _indexes.end(); it++) {
				std::string filename = utils::path(localPath, (*it));
				if (!access(filename.c_str(), R_OK)) {
					localPath = filename;
					indexFound = true;
				}
			}

			if (!indexFound){
				if (!_autoIndex) {
					return new ResponseError(403);
				}
				return fileListIndex(localPath);
			}

		}

		// ficher présent mais pas accessible
		if (access(localPath.c_str(), R_OK))
			return new ResponseError(403);

		// search cgi
		if (CGI *cgi = getCgi(localPath) ) {
			return new ResponseCgi(cgi, request);
		}

		
		if (MimeType* mime = getMimeType(localPath) ) {
			return new ResponseFile(localPath, mime);
		}

		return new ResponseError(415);
	}
}

