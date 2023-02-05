#include "Response.hpp"
#include "utility.hpp"

namespace hhpp {

	Response::mapIntString Response::_totalStatus = init_map();

	Response::Response() {}

	Response::~Response() {}

	std::string& Response::getVersion() {
		return (_version);
	}

	int& Response::getStatus() {
		return (_status);
	}

	std::string& Response::getStatusMessage() {
		return (_statusMessage);
	}

	Header& Response::getHeaders() {
		return (_header);
	}

	std::string& Response::getBody() {
		return (_body);
	}

	void Response::setStatus(int status) {
		_status = status;
	}

	void Response::setStatusMessage(std::string statusMessage) {
		_statusMessage = statusMessage;
	}

	void Response::setResponse(Request& request, int status) {
		(void) request;
		(void) status;
	}

	void Response::setTotalStatus(int i, std::string str) {
		_totalStatus[i] = str;
	}

	void Response::setBody(std::string str) {
		_body = str;
//		str.size();
		_header.append("Content-Length", utils::numberToString(_body.size()));
	}

	std::string Response::raw() const
	{
		std::string dataSend;
		dataSend = "HTTP/1.1 200 OK\n";
		dataSend.append("Content-Type: text/plain\n");
		dataSend.append("Content-Length: 7\n");
		dataSend.append("\n");
		dataSend.append("Hello !");

		return dataSend;
	}

}
