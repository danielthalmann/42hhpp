#ifndef CGI_HPP
#define CGI_HPP

#include <string>
#include <vector>
#include "Request.hpp"

#include "utility.hpp"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>

namespace hhpp {
	class CGI
	{

	public:

		CGI();
		~CGI();

		std::string execute(std::string scriptPath, Request request);
		void setLocation(const std::string& location);
		void addExtension(const std::string& extension);
		bool match(const std::string& query) const;

	private:

		std::vector<char*> preparePath(const std::string &query);
		std::map<std::string, std::string> prepareEnv(Request request);

		std::vector<std::string> _extension;
		std::string _location;
		std::string _scriptPath;
		std::string _query;

	};
}

#endif
