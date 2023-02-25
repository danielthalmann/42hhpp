#ifndef RESPONSECGI_HPP
#define RESPONSECGI_HPP

#include <Response.hpp>
#include <Location.hpp>
#include <string>

namespace hhpp {

	class ResponseDelete: public Response
	{
	public:
		ResponseDelete(Location *location);
		~ResponseDelete();

	protected:
		void prepareResponse();

	private:
		Location *_location;

	};
}

#endif
