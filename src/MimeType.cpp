#include "MimeType.hpp"

MimeType::MimeType() {}

MimeType::MimeType(std::string mimeType, std::string extension) :
				   _mimeType(mimeType), _extension(extension) {}

MimeType::~MimeType() {}