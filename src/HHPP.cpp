#include "HHPP.hpp"
#include <Json.hpp>

namespace hhpp {
	HHPP::HHPP() {}

	HHPP::~HHPP() {
		for (std::vector<IServer*>::iterator it = _servers.begin(); it != _servers.end() ; ++it) {
			delete *it;
		}

		for (std::vector<IBinding*>::iterator it = _bindings.begin(); it != _bindings.end() ; ++it) {
			delete *it;
		}
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
