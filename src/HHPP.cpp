#include "HHPP.hpp"
#include <Json.hpp>

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
			int port = json->at("servers")->at(i)->at("binding")->at("port")->getString();

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
				jsonEl = json->("domain");

			for (size_t j = 0; j < jsonEl->length(); j++) {
				newServer->addDomain(jsonEl->at(j)->getString());
			}

			//
			// index
			//
			if (json->at("servers")->at(i)->exists("index"))
				jsonEl = json->at("servers")->at(i)->at("index");
			else
				jsonEl = json->("index");

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
				jsonEl = json->("redirect");

			if (jsonEl)
			{
				Redirect* red;
				for (size_t j = 0; j < jsonEl->length(); j++) {
					int status = 302;
					// status (optional)
					if (jsonEl->at(j)->exists("status")) {
						status = jsonEl->at(j)->at("status")->getInt();
					}

					red = new Redirect(jsonEl->at(j)->at("path"), jsonEl->at(j)->at("destination"), status);
					newServer->addRedirect(red);
				}
			}

			//
			// error pages (optional)
			//

			/*
			TODO

			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("error_pages"))
				jsonEl = json->at("servers")->at(i)->at("error_pages");
			else if (json->exists("error_pages"))
				jsonEl = json->("error_pages");

			if (jsonEl)
			{
				ErrorPage* ep;
				for (size_t j = 0; j < jsonEl->length(); j++) {
					int status = 302;
					// status (optional)
					if (jsonEl->at(j)->exists("status")) {
						status = jsonEl->at(j)->at("status")->getInt();
					}

					ep = new ErrorPage(jsonEl->at(j)->key(), jsonEl->at(j)->value());
					newServer->addErrorPages(ep);
				}
			}
			*/

			//
			// location (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("location"))
				jsonEl = json->at("servers")->at(i)->at("location");
			else if (json->exists("location"))
				jsonEl = json->("location");

			if (jsonEl)
			{
				Location* loc;
				for (size_t j = 0; j < jsonEl->length(); j++) {
					loc = new Location(jsonEl->at(j)->at("path"), jsonEl->at(j)->at("root"));
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
				jsonEl = json->("auto_index");
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
				jsonEl = json->("access_log");
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
				jsonEl = json->("client_max_body_size");
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
				jsonEl = json->("allowed_methods");

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
				jsonEl = json->("cgi");

			if (jsonEl)
			{
				CGI* cgi;
				for (size_t j = 0; j < jsonEl->length(); j++) {

					cgi = new CGI();
					cgi->setLocation(jsonEl->at(j)->at("location")->getString())
					for (size_t k = 0; k < jsonEl->at(j)->at("extension")->length(); k++) {
						cgi->addExtension(jsonEl->at(j)->at("extension")->at(k)->getString());
					}
					newServer->addCGI(cgi);
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
