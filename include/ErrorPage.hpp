#ifndef ERRORPAGE_HPP
#define ERRORPAGE_HPP

#include <string>

namespace hhpp {
	class ErrorPage
	{
	public:
		ErrorPage();
		~ErrorPage();

		void setStatus(const int status);
		void setLocation(const std::string& location);

		std::string getPage(void);
	
	private:
		int _status;
		std::string _location;
	};
}

#endif
