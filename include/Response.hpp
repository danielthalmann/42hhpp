#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "AResponse.hpp"

namespace hhpp {
	class Response : public AResponse
	{
	public:
		Response();
		~Response();

		void setStatus(int status);
		std::string getBlob();
		hhpp::Header& getHeaders();

		void setResponse(Request& request);

	};
}

#endif
