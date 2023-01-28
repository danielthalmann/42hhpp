#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>

namespace hhpp {
	class Location
	{
	public:
		Location();
		Location(const std::string& path, const std::string& root);
		~Location();

	private:
		std::string _path;
		std::string _root;

	};
}

#endif
