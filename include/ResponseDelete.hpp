#ifndef RESPONSEDELETE_HPP
#define RESPONSEDELETE_HPP

#include <Response.hpp>
#include <Location.hpp>
#include <string>

namespace hhpp {

	class ResponseDelete: public Response
	{
	public:
		ResponseDelete(Location *location);
		~ResponseDelete();

	private:
		Location *_location;

	};
}

#endif
