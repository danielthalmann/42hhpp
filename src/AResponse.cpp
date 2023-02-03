#include "AResponse.hpp"
#include "utility.hpp"

namespace hhpp {

	AResponse::mapIntString AResponse::_totalStatus = init_map();

	AResponse::AResponse() {}

	AResponse::~AResponse() {}

	std::string& AResponse::getVersion() {
		return (_version);
	}

	int& AResponse::getStatus() {
		return (_status);
	}

	std::string& AResponse::getStatusMessage() {
		return (_statusMessage);
	}

	Header& AResponse::getHeaders() {
		return (_header);
	}

	std::string& AResponse::getBody() {
		return (_body);
	}

	void AResponse::setStatus(int status) {
		_status = status;
	}

	void AResponse::setStatusMessage(std::string statusMessage) {
		_statusMessage = statusMessage;
	}

	void AResponse::setResponse(Request& request, int status) {
		(void) request;
		(void) status;
	}

	void AResponse::setTotalStatus(int i, std::string str) {
		_totalStatus[i] = str;
	}

	void AResponse::setBody(std::string str) {
		_body = str;
//		str.size();
		_header.append("Content-Length", utils::numberToString(_body.size()));
	}

}
