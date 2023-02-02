#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "AResponse.hpp"
#include "utility.hpp"

namespace hhpp {
	class Response : public AResponse
	{
	public:
		Response();
		~Response();

		void setResponse(Request& request, int status);

		void showResponse();

	};
}

#endif
