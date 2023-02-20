#ifndef RESPONSEERROR_HPP
#define RESPONSEERROR_HPP

#include <Response.hpp>
#include <string>

namespace hhpp {
	class ResponseError : public Response
	{
	public:
		ResponseError(int error = 0);
		~ResponseError();

	protected:
		void prepareResponse();

	private:

	};
}

#endif
