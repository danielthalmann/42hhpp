#include "Location.hpp"
#include "utility.hpp"
#include <cstdio>
namespace hhpp {

	Location::Location() :
		_path("/"), _root(""), _localPath(""), _exists(false), _isFolder(false)
	{

	}

	Location::~Location() {}

	void Location::setPath(const std::string& path) 
	{
		_path = path;
	}

	void Location::setRoot(const std::string& root)
	{
		_root = root;
	}		

	void Location::setUrl(const std::string& url)
	{
		_localPath = utils::path(_root, url.substr(_path.size()));
		_exists = false;
		_isFolder = false;

		struct stat sb;

		if (!stat(_localPath.c_str(), &sb))
		{
			_exists = true;

			if ((sb.st_mode & S_IFMT) == S_IFDIR)
			{
				_isFolder = true;
			}
		}
	}	

	bool Location::isFolder() const
	{
		return _isFolder;
	}

	bool Location::exists() const
	{
		return _exists;
	}

	std::string Location::getRoot() const
	{
		return _root;
	}

	bool Location::match(const std::string& query) const
	{
		if (_path == query.substr(0, _path.size()))
			return true;
		return false;
	}

	bool Location::removeFile()
	{
		if (_exists && ! _isFolder)
		{
			if (!remove(_localPath.c_str()))
			{
				return true;
			}
		}
		return false;
		
	}


	// query : /script/test.cgi
	// /var/www/cgi/test.cgi
	std::string Location::getLocalPath() const
	{
		return _localPath;
	}

}
