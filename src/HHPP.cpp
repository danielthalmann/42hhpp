#include "HHPP.hpp"
#include <Json.hpp>

namespace hhpp {
	HHPP::HHPP() {}

	HHPP::~HHPP() {
		for (std::vector<IServer*>::iterator it = _servers.begin(); it != _servers.end() ; ++it) {
			delete *it;
		}
		_servers.clear();

		for (std::vector<IBinding*>::iterator it = _bindings.begin(); it != _bindings.end() ; ++it) {
			delete *it;
		}
		_bindings.clear();
	}

	void HHPP::loadConfig(std::string pathConfig) {
		std::string jsonString;

		jsonString = readFileConfig(pathConfig);

		json::JsonValue *json = json::Json::parse(jsonString);

		for (size_t i = 0; i < json->at("servers")->length(); i++)
		{
			if (json->at("servers")->at(i)->exists("root2")){
				std::cout << json->at("servers")->at(i)->at("root")->getString() << std::endl;
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
			throw(HHPP::fileStatus());

		if ((fileInfo.st_mode & S_IFMT) == S_IFDIR)
			throw(HHPP::fileStatus());


		if (!ifs.good() || pathConfig.empty())
			throw(HHPP::fileStatus());

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
			throw(HHPP::fileStatus());
		}
		return (file);
	}

	void HHPP::setupSocket(std::string ip, int port) {
		IBinding *new_socket = new Binding();
		_bindings.push_back(new_socket);

		new_socket->setIP(ip);
		new_socket->setPort(port);
		new_socket->setSocket();
	}

	void HHPP::dispatchRequest(hhpp::Request request) {
		(void)request;
	}

	const char* HHPP::fileStatus::what() const throw() {
		return ("File Error");
	}
	
}
