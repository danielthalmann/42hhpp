#ifndef MIMETYPE_HPP
#define MIMETYPE_HPP

#include <string>

namespace hhpp {
	class MimeType
	{
	public:
		MimeType();
		~MimeType();

		void setMimeType(const std::string& mimeType);
		void setExtension(const std::string& extension);

	private:
		std::string _mimeType;
		std::string _extension;

	};
}

#endif
