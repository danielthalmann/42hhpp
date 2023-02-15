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

		bool isForMe(Request request);
		std::string execute(Request request);
		void setLocation(const std::string& location);
		void addExtension(const std::string& extension);

	private:

		std::vector<std::string> _extension;
		std::string _location;

	};
}

#endif
