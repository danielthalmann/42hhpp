#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <map>
#include "IServer.hpp"
#include "CGI.hpp"
#include "Location.hpp"
#include "Redirect.hpp"
#include "ErrorPage.hpp"

class Server : public IServer
{

public:

	Server();
	~Server();

	std::string host;
	void setBinding(Binding* bind);

	virtual bool isForMe(Request request);
	virtual void bind(Binding binding);
	virtual Response treatRequest(Request request);

private:

	Binding* _binding;
	std::string _root;
	std::vector<CGI> _cgi;
	std::map<std::string, std::string> _mimetypes;
	std::vector<std::string> _domains;
	std::vector<std::string> _indexes;
	std::vector<Location> _locations;
	std::vector<Redirect> _redirect;
	std::string _accessLog;
	std::vector<ErrorPage> _errorPages;
	std::vector<std::string> _allowedMethods;
	bool _autoIndex;

};

#endif
