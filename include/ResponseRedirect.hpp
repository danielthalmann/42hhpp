#ifndef RESPONSEREDIRECT_HPP
#define RESPONSEREDIRECT_HPP

#include <Response.hpp>
#include <string>

namespace hhpp
{
	class ResponseRedirect : public Response
	{
	public:
		ResponseRedirect(std::string url, int status = 301);
		~ResponseRedirect();

		void redirect(std::string redirect);

	private:
	};
} // namespace hhpp

#endif
