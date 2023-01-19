#include "AResponse.hpp"

AResponse::AResponse() {}

AResponse::~AResponse() {}

void AResponse::setStatus(int status) {
	(void)status;
}

std::string AResponse::getBlob() {
	return(NULL);
}

Header& AResponse::headers() {
	return(_header);
}
