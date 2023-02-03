#ifndef RESPONSEERROR_HPP
#define RESPONSEERROR_HPP

#include <AResponse.hpp>
#include <string>

namespace hhpp {
	class ResponseError: public AResponse
	{
	public:
		ResponseError(int error = 0);
		~ResponseError();

		void filename(std::string filename);

	private:

	};
}

#endif
