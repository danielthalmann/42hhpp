#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>

namespace hhpp {
	class Location
	{
	public:
		Location();
		~Location();
		void setPath(const std::string& path);
		void setRoot(const std::string& root);

	private:
		std::string _path;
		std::string _root;

	};
}

#endif
