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
//#include <stdlib.h>
//#include <unistd.h>

namespace hhpp {
	class CGI
	{

	public:

		CGI();
		~CGI();

		std::string execute(std::string script, Request request);
		void setLocation(const std::string& location);
		void addExtension(const std::string& extension);
		bool match(const std::string& query) const;

	private:

		std::vector<std::string> _extension;
		std::string _location;

	};
}

#endif
