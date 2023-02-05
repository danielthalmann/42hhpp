#include "ResponseError.hpp"
#include "utility.hpp"

namespace hhpp {
	ResponseError::ResponseError(int error) 
	: Response() 
	{
		setStatus(error);
		setBody(getStatusMessage());
		setContentType("text/plain");
	}

	ResponseError::~ResponseError() {}

	void ResponseError::filename(std::string filename) {
		(void)filename;
	}

}
