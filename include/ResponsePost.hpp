#ifndef RESPONSEPOST_HPP
#define RESPONSEPOST_HPP

#include <Location.hpp>
#include <Request.hpp>
#include <Response.hpp>
#include <string>

namespace hhpp
{

	class ResponsePost : public Response
	{
	public:
		ResponsePost(Location *location, Request *request);
		~ResponsePost();

	private:
		Location *_location;
	};
} // namespace hhpp

#endif
