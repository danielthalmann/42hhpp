#include "MimeType.hpp"

namespace hhpp {

	MimeType::MimeType() 
	: _mimeType(""), _extension("") 
	{
	}

	MimeType::~MimeType() {}

	void MimeType::setMimeType(const std::string& mimeType)
	{
		_mimeType = mimeType;
	}

	void MimeType::setExtension(const std::string& extension)
	{
		_extension = extension;
	}

	std::string MimeType::getMimeType() const
	{
		return _extension;
	}
	
	bool MimeType::match(const std::string& query) const
	{
		std::string extension = query.substr(query.size() - (_extension).size());
		if (_extension == extension)
			return true;
		return false;
	}

}
