#include "Location.hpp"
#include "utility.hpp"
#include <cstdio>
#include <fstream>
namespace hhpp
{

	Location::Location() : _path("/"), _root(""), _localPath(""), _url(""), _exists(false), _isFolder(false)
	{
	}

	Location::~Location()
	{
	}

	void Location::setPath(const std::string &path)
	{
		_path = path;
	}

	void Location::setRoot(const std::string &root)
	{
		_root = root;
	}

	void Location::setUrl(const std::string &url)
	{
		_localPath = utils::path(_root, url.substr(_path.size()));
		_url = url;
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

	std::string Location::getUrl() const
	{
		return _url;
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

	bool Location::match(const std::string &query) const
	{
		if (_path == query.substr(0, _path.size()))
			return true;
		return false;
	}

	bool Location::removeFile()
	{
		if (_exists && !_isFolder)
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

	std::string Location::getDirectory() const
	{
		size_t pos = _localPath.rfind("/");
		if (pos > 0)
			return _localPath.substr(0, pos);
		else
			return _localPath;
	}

	std::string Location::getFilename() const
	{
		size_t pos = _localPath.rfind("/");
		if (pos > 0)
			return _localPath.substr(pos + 1);
		else
			return _localPath;
	}

	void Location::put(const std::string &content)
	{
		put(content, _localPath);
	}

	void Location::put(const std::string &content, const std::string &filename)
	{
		std::ofstream ofs(filename.c_str());

		if (ofs.is_open())
		{
			ofs << content;
			ofs.close();
		}
		else
		{
			throw std::domain_error("cannot save the file");
		}
	}

} // namespace hhpp
