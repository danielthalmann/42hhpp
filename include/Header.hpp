#ifndef HEADER_HPP
#define HEADER_HPP

#include "iostream"
#include <map>
#include <string>

namespace hhpp
{
	class Header
	{
	public:

		typedef std::map<std::string, std::string> mapStringString;
		typedef std::map<std::string, std::string>::iterator mapStringStringIt;

		Header();
		~Header();

		std::string get(std::string key);
		void remove(std::string key);
		void removeAll();
		void append(std::string key, std::string value);
		void showParams();
		std::string raw() const;
		mapStringString &map();

		std::string &operator[](const std::string &key);


		mapStringString getParams();

	private:
		mapStringString _params;
	};
} // namespace hhpp

#endif
