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
		void setUrl(const std::string& url);
		bool match(const std::string& query) const;
		std::string getRoot() const;
		bool isFolder() const;
		bool exists() const;
		bool removeFile();
		std::string getLocalPath() const;
		void put(std::string content);

	private:
		std::string _path;
		std::string _root;
		std::string _localPath;
		bool _exists;
		bool _isFolder;


	};
}

#endif
