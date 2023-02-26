#include "ResponsePost.hpp"
#include "utility.hpp"

namespace hhpp
{

	ResponsePost::ResponsePost(Location *location, Request *request) : Response(), _location(location)
	{

		if (request->isMultipart())
		{
			std::vector<std::string> parts = utils::split(request->getBody(), "--" + request->getBoundary());
			for (size_t i = 0; i < parts.size(); i++)
			{
				std::cout << parts[i] << "\n\n\n"; 
			}
			const std::string head = request->getHeaders().raw();
			location->put(head + request->getBody());			
		}
		else
		{
			const std::string head; // = request->getHeaders().raw();
			location->put(head + request->getBody());
		}

	}

	ResponsePost::~ResponsePost()
	{
	}

} // namespace hhpp
