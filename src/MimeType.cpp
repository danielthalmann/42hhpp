#include "MimeType.hpp"

namespace hhpp {

	MimeType::MimeType() {}

	MimeType::MimeType(std::string mimeType, std::string extension) :
					   _mimeType(mimeType), _extension(extension) {}

	MimeType::~MimeType() {}
}
