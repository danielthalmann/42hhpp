#ifndef RESPONSEDELETE_HPP
#define RESPONSEDELETE_HPP

#include <Location.hpp>
#include <Response.hpp>
#include <string>

namespace hhpp
{

	class ResponseDelete : public Response
	{
	public:
		ResponseDelete(Location *location);
		~ResponseDelete();

	private:
		Location *_location;
	};
} // namespace hhpp

#endif
