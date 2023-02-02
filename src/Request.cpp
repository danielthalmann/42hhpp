#include "Request.hpp"
#include "utility.hpp"
#include <iostream>

namespace hhpp {
	Request::Request() {
		setPort(0);
	}
	Request::~Request() {}


	std::string Request::getMethod() { return (_method); }
	std::string Request::getQuery() { return (_query); }
	std::string Request::getHost() { return (_host); }
	int Request::getPort() { return (_port); }
	std::string Request::getUrl() { return (_url); }
	std::string Request::getBody() { return (_body); }
	std::string Request::getHttpVersion() { return (_httpVersion); }
	Header &Request::getHeaders() { return (_headers); }
	std::string Request::getRequest() {
		std::string request;
		Header::mapStringString params;

		request = _method + " " + _url + " " + _httpVersion + "\n";
		params = _headers.getParams();
		for (Header::mapStringStringIt it = params.begin(); it != params.end() ; ++it) {
			request.append(it->first);
			request.append(": ");
			request.append(it->second);
			request.append("\n");
		}
		return (request);
	}

	void Request::setMethod(std::string method) { _method = method; }
	void Request::setQuery(std::string query) { _query = query; }
	void Request::setHost(std::string host) { _host = host; }
	void Request::setPort(int port) { _port = port; }
	void Request::setUrl(std::string url) { _url = url; }
	void Request::setBody(std::string body) { _body = body; }
	void Request::setHttpVersion(std::string httpVersion) { _httpVersion = httpVersion; }

	void Request::parseRequest(const std::string& rawRequest) {
		std::vector<std::string> token;
		std::vector<std::string> header;

		header = utils::split(rawRequest, "\r\n");

		for (size_t i = 0; i < header.size(); i++) {
			size_t pos;
			pos = header[i].find(":");
			if (pos == std::string::npos)
				token = utils::split(header[i], " ");
			else
				token = utils::split(header[i], ": ");

			if (pos == std::string::npos && i == 0)
			{
				setMethod(token[0]);
				setUrl(token[1]);
				setHttpVersion(token[2]);
			}
			else if (token.size() == 2)
				_headers.append(token[0], token[1]);
			if (token[0] == "Host")
			{
				_host = token[1];
			}
		}
	}

	void Request::showRequest() {
		std::cout	<< getMethod() << " "
					<< getUrl() << " "
					<< getHttpVersion() << std::endl;
		_headers.showParams();
	}
}

