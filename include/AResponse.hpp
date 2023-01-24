#ifndef ARESPONSE_HPP
#define ARESPONSE_HPP

#include <string>
#include "Header.hpp"
#include "Request.hpp"

namespace hhpp {
	class AResponse
	{
	public:
		AResponse();
		virtual ~AResponse();

		void setStatus(int status);
		std::string getBlob();
		hhpp::Header& getHeaders();

		void setResponse(Request& request);

	protected:
		int _status;
		hhpp::Header _header;

	};
}

#endif
