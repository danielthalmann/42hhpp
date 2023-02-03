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
		std::string getMimeType() const;
		void setExtension(const std::string& extension);
		bool match(const std::string& query) const;

	private:
		std::string _mimeType;
		std::string _extension;

	};
}

#endif
