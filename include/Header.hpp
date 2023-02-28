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
		Header();
		~Header();

		std::string get(std::string key);
		void remove(std::string key);
		void removeAll();
		void append(std::string key, std::string value);
		void showParams();
		std::string raw() const;

		std::string &operator[](const std::string &key);


		typedef std::map<std::string, std::string> mapStringString;
		typedef std::map<std::string, std::string>::iterator mapStringStringIt;

		mapStringString getParams();

	private:
		mapStringString _params;
	};
} // namespace hhpp

#endif
