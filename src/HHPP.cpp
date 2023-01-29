#include "HHPP.hpp"
#include <Json.hpp>
#include <stdlib.h>

namespace hhpp {
	HHPP::HHPP() {}

	HHPP::~HHPP() {
		for (std::vector<IServer*>::iterator it = _servers.begin(); it != _servers.end() ; ++it) {
			delete (*it);
		}

		for (std::vector<IBinding*>::iterator it = _bindings.begin(); it != _bindings.end() ; ++it) {
			delete (*it);
		}
	}

	void HHPP::loadConfig(std::string pathConfig) {
		
		std::string jsonString;
		json::JsonValue *jsonEl, *json;

		jsonString = readFileConfig(pathConfig);

		json = json::Json::parse(jsonString);
		
		for (size_t i = 0; i < json->at("servers")->length(); i++)
		{
			IServer* newServer = new Server();
			IBinding* newBinding = NULL;

			_servers.push_back(newServer);


			//
			// binding
			//
			std::string ip = json->at("servers")->at(i)->at("binding")->at("ip")->getString();
			int port = json->at("servers")->at(i)->at("binding")->at("port")->getInt();

			for (std::vector<IBinding*>::iterator it = _bindings.begin(); it != _bindings.end() ; ++it) {
				if ((*it)->isBinding(ip, port)) {
					newBinding = (*it);
					break;
				}
			}

			if (!newBinding) {
				newBinding = new Binding();
				_bindings.push_back(newBinding);
			}

			newServer->setBinding(newBinding);

			//
			// domain
			//
			if (json->at("servers")->at(i)->exists("domain"))
				jsonEl = json->at("servers")->at(i)->at("domain");
			else
				jsonEl = json->at("domain");

			for (size_t j = 0; j < jsonEl->length(); j++) {
				newServer->addDomain(jsonEl->at(j)->getString());
			}

			//
			// index
			//
			if (json->at("servers")->at(i)->exists("index"))
				jsonEl = json->at("servers")->at(i)->at("index");
			else
				jsonEl = json->at("index");

			for (size_t j = 0; j < jsonEl->length(); j++) {
				newServer->addIndex(jsonEl->at(j)->getString());
			}

			//
			// root
			//
			if (json->at("servers")->at(i)->exists("root"))
				newServer->setRoot(json->at("servers")->at(i)->at("root")->getString());
			else
				newServer->setRoot(json->at("root")->getString());

			//
			// redirect (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("redirect"))
				jsonEl = json->at("servers")->at(i)->at("redirect");
			else if (json->exists("redirect"))
				jsonEl = json->at("redirect");

			if (jsonEl)
			{
				Redirect* red;
				for (size_t j = 0; j < jsonEl->length(); j++) {
					red = new Redirect();
					red->setPath(jsonEl->at(j)->at("path")->getString());
					red->setDestination(jsonEl->at(j)->at("destination")->getString());
					if (jsonEl->at(j)->exists("status")) {
						red->setStatus(jsonEl->at(j)->at("status")->getInt());
					}
					newServer->addRedirect(red);
				}
			}

			//
			// error pages (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("error_pages"))
				jsonEl = json->at("servers")->at(i)->at("error_pages");
			else if (json->exists("error_pages"))
				jsonEl = json->at("error_pages");

			if (jsonEl)
			{
				ErrorPage* ep;
				std::vector<std::string> errorCodes = jsonEl->keys();
	
				for (size_t j = 0; j < errorCodes.size(); j++) {

					ep = new ErrorPage();

					ep->setLocation(jsonEl->at(errorCodes[j])->getString());
					ep->setStatus(atoi(errorCodes[j].c_str()));

					newServer->addErrorPage(ep);
				}
			}

			//
			// location (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("location"))
				jsonEl = json->at("servers")->at(i)->at("location");
			else if (json->exists("location"))
				jsonEl = json->at("location");

			if (jsonEl)
			{
				Location* loc;
				for (size_t j = 0; j < jsonEl->length(); j++) {
					loc = new Location();
					loc->setPath(jsonEl->at(j)->at("path")->getString());
					loc->setRoot(jsonEl->at(j)->at("root")->getString());
					newServer->addLocation(loc);
				}
			}


			//
			// auto_index (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("auto_index"))
				jsonEl = json->at("servers")->at(i)->at("auto_index");
			else if (json->exists("auto_index"))
				jsonEl = json->at("auto_index");
			if (jsonEl)
			{
				newServer->setAutoIndex(jsonEl->getBool());
			}			

			//
			// access_log (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("access_log"))
				jsonEl = json->at("servers")->at(i)->at("access_log");
			else if (json->exists("access_log"))
				jsonEl = json->at("access_log");
			if (jsonEl)
			{
				newServer->setAccessLog(jsonEl->getString());
			}	

			//
			// client_max_body_size (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("client_max_body_size"))
				jsonEl = json->at("servers")->at(i)->at("client_max_body_size");
			else if (json->exists("client_max_body_size"))
				jsonEl = json->at("client_max_body_size");
			if (jsonEl)
			{
				newServer->setClientMaxBodySize(jsonEl->getInt());
			}	

			//
			// allowed method
			//
			if (json->at("servers")->at(i)->exists("allowed_methods"))
				jsonEl = json->at("servers")->at(i)->at("allowed_methods");
			else
				jsonEl = json->at("allowed_methods");

			for (size_t j = 0; j < jsonEl->length(); j++) {
				newServer->addAllowedMethod(jsonEl->at(j)->getString());
			}

			//
			// cgi (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("cgi"))
				jsonEl = json->at("servers")->at(i)->at("cgi");
			else if (json->exists("cgi"))
				jsonEl = json->at("cgi");

			if (jsonEl)
			{
				CGI* cgi;
				for (size_t j = 0; j < jsonEl->length(); j++) {

					cgi = new CGI();
					cgi->setLocation(jsonEl->at(j)->at("location")->getString());
					for (size_t k = 0; k < jsonEl->at(j)->at("extension")->length(); k++) {
						cgi->addExtension(jsonEl->at(j)->at("extension")->at(k)->getString());
					}
					newServer->addCGI(cgi);
				}
			}

			//
			// mimetype
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("mime_types"))
				jsonEl = json->at("servers")->at(i)->at("mime_types");
			else
				jsonEl = json->at("mime_types");

			std::vector<std::string> mimes = jsonEl->keys();

			for (size_t j = 0; j < mimes.size(); j++) {

				for (size_t k = 0; k < json->at("mime_types")->at(mimes[j])->length(); k++)
				{
					newServer->addMimeType(mimes[j], json->at("mime_types")->at(mimes[j])->at(k)->getString() );
				}
				
			}
			

		}
		

		delete json;
	}

	void HHPP::run() {}

	std::string HHPP::readFileConfig(std::string pathConfig) {
		std::string file;
		char c;
		struct stat fileInfo;
		std::ifstream ifs(pathConfig.c_str());

		if (stat(pathConfig.c_str(), &fileInfo) != 0)
			throw(std::exception());

		if ((fileInfo.st_mode & S_IFMT) == S_IFDIR)
			throw(std::exception());


		if (!ifs.good() || pathConfig.empty())
			throw(std::exception());

		if (ifs.is_open())
		{

			c = ifs.get();

			do {
				file += c;
				c = ifs.get();
			}
			while (!ifs.eof());

			ifs.close();
		}
		else
		{
			throw(std::exception());
		}
		return (file);
	}

	void HHPP::dispatchRequest(hhpp::Request request) {
		(void)request;
	}
	
}
