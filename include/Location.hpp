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
		bool match(const std::string& query) const;
		std::string getLocalPath(const std::string& query) const;

	private:
		std::string _path;
		std::string _root;

	};
}

#endif
