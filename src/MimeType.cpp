#include "MimeType.hpp"

hhpp::MimeType::MimeType() {}

hhpp::MimeType::MimeType(std::string mimeType, std::string extension) :
				   _mimeType(mimeType), _extension(extension) {}

hhpp::MimeType::~MimeType() {}
