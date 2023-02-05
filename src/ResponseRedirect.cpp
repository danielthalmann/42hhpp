#include "ResponseRedirect.hpp"

namespace hhpp {
	
	ResponseRedirect::ResponseRedirect(std::string url, int status) 
	: Response()
	{
		getHeaders()["Location"] = url;
		setStatus(status);
	}

	ResponseRedirect::~ResponseRedirect() {}

	void ResponseRedirect::redirect(std::string redirect) {
		(void)redirect;
	}
}
