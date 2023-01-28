#ifndef ERRORPAGE_HPP
#define ERRORPAGE_HPP

#include <string>

namespace hhpp {
	class ErrorPage
	{
	public:
		ErrorPage(const int status, const std::string& location);
		~ErrorPage();

		std::string getPage(void);

		int _status;
		std::string _location;
	};
}

#endif
