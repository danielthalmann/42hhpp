#ifndef MIMETYPE_HPP
#define MIMETYPE_HPP

#include <string>

namespace hhpp {
	class MimeType
	{
	public:
		MimeType();
		MimeType(std::string mimeType, std::string extension);
		~MimeType();

	//TODO (add)?
	//	void (add)MimeType(std::string mimeType, std::string extension);

	private:
		std::string _mimeType;
		std::string _extension;

	};
}

#endif
