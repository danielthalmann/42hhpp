#include "ResponseError.hpp"

namespace hhpp {
	ResponseError::ResponseError(int error) 
	: AResponse() 
	{
		(void)error;
	}

	ResponseError::~ResponseError() {}

	void ResponseError::filename(std::string filename) {
		(void)filename;
	}
}
