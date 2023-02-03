#include "ResponseError.hpp"

namespace hhpp {
	ResponseError::ResponseError(int error = 0) : AResponse() {}

	ResponseError::~ResponseError() {}

	void ResponseError::filename(std::string filename) {
		(void)filename;
	}
}
