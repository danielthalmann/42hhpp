#include "Response.hpp"
#include "utility.hpp"
#include <sstream>

namespace hhpp {

	Response::mapIntString Response::_totalStatus = init_map();

	Response::Response() 
	{
		setStatus(200);
		setBody(getStatusMessage());
		setContentType("text/plain");
		getHeaders()["Server"] = "HHPP/0.0.1";
		getHeaders()["Connection"] = "close";
	}

	Response::~Response() {}

	std::string& Response::getVersion() {
		return (_version);
	}

	int& Response::getStatus() {
		return (_status);
	}

	std::string Response::getStatusMessage() const {
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
		try {
			_statusMessage = _totalStatus.at(_status);
		} catch (std::exception &e) {
			_status = 500;
			_statusMessage = _totalStatus.at(_status);
		}
	}

	void Response::setContentType(std::string contentType) {
		_header["Content-Type"] = contentType;
	}

	void Response::setBody(std::string str) {
		_body = str;
		_header["Content-Length"] = utils::numberToString(_body.size());
	}

	void Response::setServer(IServer *server) {
		_server = server;
	}

	IServer *Response::getServer() {
		return _server;
	}

	std::string Response::raw()
	{
		prepareResponse();

		std::string statusMessage;
		int status = _status;

		try {
			statusMessage = _totalStatus.at(status);
		} catch (std::exception &e) {
			status = 200;
			statusMessage = "OK";
		}

		std::string dataSend;
		dataSend.append("HTTP/1.1");
		dataSend.append(" ");
		dataSend.append(utils::numberToString(status));
		dataSend.append(" ");
		dataSend.append(statusMessage);
		dataSend.append("\r\n");
		dataSend.append(_header.raw());
		dataSend.append("\r\n");
		dataSend.append(_body);

		return dataSend;
	}

	void Response::prepareResponse() {}

	std::string Response::get404() {
		std::string page;

		page.append("<html><head>"
					"<title>The page you were looking for doesn't exist (404)</title>"
					"<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
					"</head><body>"
					"<h1>Error 404: Not Found</h1>"
					"<p>The page you were looking for doesn't exist</p>"
					"<img src=\"https://www.lesdebrouillards.com/wp-content/uploads/2019/10/Pigeon-1.jpg\" alt=\"Pigeon with 404 message\" width=\"500\" height=\"600\">"
					"</body></html>");

		return (page);
	}

}
