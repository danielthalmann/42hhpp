#ifndef RESPONSEFILE_HPP
#define RESPONSEFILE_HPP

#include <MimeType.hpp>
#include <Response.hpp>
#include <string>

namespace hhpp
{
	class ResponseFile : public Response
	{
	public:
		ResponseFile(std::string filename, MimeType *mimetype);
		~ResponseFile();


	private:
	};
} // namespace hhpp

#endif
