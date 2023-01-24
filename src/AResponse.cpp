#include "AResponse.hpp"

hhpp::AResponse::AResponse() {}

hhpp::AResponse::~AResponse() {}

void hhpp::AResponse::setStatus(int status) {
	(void)status;
}

std::string hhpp::AResponse::getBlob() {
	return(NULL);
}

hhpp::Header& hhpp::AResponse::headers() {
	return(_header);
}
