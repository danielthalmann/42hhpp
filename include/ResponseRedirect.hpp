#ifndef RESPONSEREDIRECT_HPP
#define RESPONSEREDIRECT_HPP

#include <AResponse.hpp>
#include <string>

namespace hhpp {
	class ResponseRedirect : public AResponse
	{
	public:
		ResponseRedirect(std::string url, int status = 301);
		~ResponseRedirect();

		void redirect(std::string redirect);

	private:

	};
}

#endif
