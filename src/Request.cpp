#include "Request.hpp"
#include "utility.hpp"
#include <iostream>
#include <cstdlib>

namespace hhpp {
	Request::Request() {
		setPort(0);
	}
	Request::~Request() {}


std::string Request::getMethod() const { return (_method); }
std::string Request::getQuery() const { return (_query); }

std::string Request::getHost() const { return (_host); }
int Request::getPort() const { return (_port); }
std::string Request::getUrl() const { return (_url); }
std::string Request::getBody() const { return (_body); }
std::string Request::getHttpVersion() const { return (_httpVersion); }
int Request::getBodySize() const { return (_bodySize); }

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
	std::vector<std::string> query;
	bool isBody = false;

	header = utils::split(rawRequest, "\r\n");

	_bodySize = 0;

	for (size_t i = 0; i < header.size(); i++) {
		if (i == 0)
		{
			token = utils::split(header[i], " ");

			if (token.size() == 3) {
				setMethod(utils::trim(token[0]));
				query = utils::split(token[1], "?");
				if (query.size() == 2)
				{
					setUrl(query[0]);
					setQuery(query[1]);
				}
				else
					setUrl(utils::trim(token[1]));

				setHttpVersion(utils::trim(token[2]));
			}
		}
		else
		{
			token = utils::split(header[i], ": ");

			if (token.size() != 2 && !isBody)
				isBody = true;

			if (!isBody) {
				_headers.append(utils::trim(token[0]), utils::trim(token[1]));
			}
			else {
				_body.append(header[i]);
			}
		}
	}

	// extract host
	try {

		_host = _headers.get("Host");
		token = utils::split(_host, ":");
		if (token.size() == 2) {
			_host = token[0];
			_port = std::atoi(token[1].c_str());
		} else
			_port = 80;

	} catch(std::exception &e) {

	}

	try {
		_bodySize = std::atoi(_headers.get("Content-Length").c_str());
	} catch(std::exception &e) {

	}
}

	void Request::showRequest() {
		std::cout << "show request" << std::endl;
		std::cout	<< getMethod() << " "
					<< getUrl() << " "
					<< getHttpVersion() << std::endl;
		std::cout << "headers:" << std::endl;
		_headers.showParams();
		std::cout << "end headers" << std::endl;

		std::cout << "body Size:" << _bodySize << std::endl;
		std::cout << "bodyContent:" << std::endl;
		std::cout << "bodyContent:" << _body << std::endl;
		std::cout << "query:" << _query << std::endl;
		std::cout << "host:" << _host << std::endl;
		std::cout << "post:" << _port << std::endl;

		std::cout << "end show request" << std::endl;
	}

	hhpp::Header &Request::getHeaders() {
		return (_headers);
	}
}
