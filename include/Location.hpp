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
		std::string getDirectory() const;
		std::string getFilename() const;
		std::string getUrl() const;
		void put(const std::string &content);
		void put(const std::string &content, const std::string &filename);

	private:
		std::string _path;
		std::string _root;
		std::string _localPath;
		std::string _url;
		bool _exists;
		bool _isFolder;


	};
}

#endif
