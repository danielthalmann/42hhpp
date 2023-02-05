#ifndef RESPONSEFILE_HPP
#define RESPONSEFILE_HPP

#include <Response.hpp>
#include <string>

namespace hhpp {
	class ResponseFile : public Response
	{
	public:
		ResponseFile(std::string filename, std::string mimetype);
		~ResponseFile();


	private:

	};
}

#endif
