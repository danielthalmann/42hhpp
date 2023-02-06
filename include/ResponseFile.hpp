#ifndef RESPONSEFILE_HPP
#define RESPONSEFILE_HPP

#include <Response.hpp>
#include <MimeType.hpp>
#include <string>

namespace hhpp {
	class ResponseFile : public Response
	{
	public:
		ResponseFile(std::string filename, MimeType* mimetype);
		~ResponseFile();


	private:

	};
}

#endif
