#include "ResponseRedirect.hpp"

namespace hhpp {
	
	ResponseRedirect::ResponseRedirect(std::string url, int status) {
		(void) url;
		(void) status;
	}

	ResponseRedirect::~ResponseRedirect() {}

	void ResponseRedirect::redirect(std::string redirect) {
		(void)redirect;
	}
}
