#ifndef ERRORPAGE_HPP
#define ERRORPAGE_HPP

#include <string>
#include <utility.hpp>

namespace hhpp {
	class ErrorPage
	{
	public:
		ErrorPage();
		~ErrorPage();

		std::string getPage(std::string root = "");

		void setStatus(const int status);
		void setLocation(const std::string& location);
		int getStatus();

	private:
		int _status;
		std::string _location;
	};
}

#endif
