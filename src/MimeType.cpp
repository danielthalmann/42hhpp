#include "MimeType.hpp"

namespace hhpp {

	MimeType::MimeType() 
	: _mimeType(""), _extension("") 
	{

	}

	void MimeType::setMimeType(const std::string& mimeType)
	{
		_mimeType = mimeType;
	}

	void MimeType::setExtension(const std::string& extension)
	{
		_extension = extension;
	}

	MimeType::~MimeType() {}
}
