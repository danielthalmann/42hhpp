#include "HHPP.hpp"

namespace hhpp {
	HHPP::HHPP() {}

	HHPP::~HHPP() {
		for (std::vector<hhpp::IServer*>::iterator it = _servers.begin(); it != _servers.end() ; ++it) {
			delete *it;
		}

		for (std::vector<hhpp::IBinding*>::iterator it = _bindings.begin(); it != _bindings.end() ; ++it) {
			delete *it;
		}
	}

	void HHPP::loadConfig(std::string pathConfig) {
		readFileConfig(pathConfig);
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
