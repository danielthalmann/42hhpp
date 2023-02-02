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

	void AResponse::setTotalStatus(int i, std::string str) {
		_totalStatus[i] = str;
	}

	void AResponse::setBody(std::string body, std::string bodyType) {
		_body = body;
		_header.append("Content-Length", utils::numberToString(_body.size()));
		_header.append("Content-Type", bodyType + "; Charset=utf-8");
		_header.append("Date", utils::getTime());
	}

	void AResponse::setErrorPage(int status) {
		std::string page;
		std::string error = "Error " + utils::numberToString(status) + ": " + _totalStatus[status];

		page.append("<html><head>"
					"<title>" + error + "</title>"
					"<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
					"</head><body>"
					"<h1>" + error + "</h1>"
					"<p>Oops! Something went wrong...</p>"
					"<p>We seem to be having some technical difficulties. Hang tight.</p>"
					"</body></html>");
		setBody(page, "text/html");
	}

	std::string AResponse::getResponse() {
		std::string response;
		Header::mapStringString params;

		response = _version + " " +  utils::numberToString(_status) + " " + _statusMessage + "\r\n";
		params = _header.getParams();
		for (Header::mapStringStringIt it = params.begin(); it != params.end() ; ++it) {
			response.append(it->first + ": " + it->second);
			response.append("\r\n");
		}
		response.append("\r\n");
		response.append(_body);
		response.append("\r\n");

		return (response);
	}

}
