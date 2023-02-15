#include "MimeType.hpp"

namespace hhpp {

	MimeType::MimeType() 
	: _mimeType(""), _extension(""), _isBinary(false)
	{
	}

	MimeType::~MimeType() {}

	void MimeType::setMimeType(const std::string& mimeType)
	{
		_mimeType = mimeType;
		if (_mimeType.substr(0, 5) != "text/")
			_isBinary = true;
	}

	void MimeType::setExtension(const std::string& extension)
	{
		_extension = extension;
	}

	std::string MimeType::getMimeType() const
	{
		return _mimeType;
	}

	std::string MimeType::getExtension() const
	{
		return _extension;
	}

	bool MimeType::isBinary() const
	{
		return _isBinary;
	}

	bool MimeType::match(const std::string& query) const
	{
		std::string extension = query.substr(query.size() - (_extension).size());
		if (_extension == extension)
			return true;
		return false;
	}

}
