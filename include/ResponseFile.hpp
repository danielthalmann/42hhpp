#ifndef RESPONSEFILE_HPP
#define RESPONSEFILE_HPP

#include <AResponse.hpp>
#include <string>

namespace hhpp {
	class ResponseFile : public AResponse
	{
	public:
		ResponseFile(std::string filename, std::string mimetype);
		~ResponseFile();


	private:

	};
}

#endif
