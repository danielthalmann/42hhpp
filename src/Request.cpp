#include "Request.hpp"
#include "utility.hpp"
#include <iostream>
#include <cstdlib>

//GET / HTTP/1.1
//Host: www.quicksite.ch
//User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:107.0) Gecko/20100101 Firefox/107.0
//Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
//Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3
//Accept-Encoding: gzip, deflate, br
//Connection: keep-alive
//Upgrade-Insecure-Requests: 1
//Sec-Fetch-Dest: document
//Sec-Fetch-Mode: navigate
//Sec-Fetch-Site: none
//Sec-Fetch-User: ?1

hhpp::Request::Request() {
	setPort(0);
}
hhpp::Request::~Request() {}


std::string hhpp::Request::getMethod() const { return (_method); }
std::string hhpp::Request::getQuery() const { return (_query); }
std::string hhpp::Request::getQueryLocation() const { return (_query); /* TODO */ }

std::string hhpp::Request::getHost() const { return (_host); }
int hhpp::Request::getPort() { return (_port); }
std::string hhpp::Request::getUrl() { return (_url); }
std::string hhpp::Request::getBody() { return (_body); }
std::string hhpp::Request::getHttpVersion() { return (_httpVersion); }

void hhpp::Request::setMethod(std::string method) { _method = method; }
void hhpp::Request::setQuery(std::string query) { _query = query; }
void hhpp::Request::setHost(std::string host) { _host = host; }
void hhpp::Request::setPort(int port) { _port = port; }
void hhpp::Request::setUrl(std::string url) { _url = url; }
void hhpp::Request::setBody(std::string body) { _body = body; }
void hhpp::Request::setHttpVersion(std::string httpVersion) { _httpVersion = httpVersion; }

void hhpp::Request::parseRequest(const std::string& rawRequest) {
	std::vector<std::string> token;
	std::vector<std::string> header;

	header = utils::split(rawRequest, "\n");

	for (size_t i = 0; i < header.size(); i++) {

		if (i == 0)
		{
			token = utils::split(header[i], " ");

			if (token.size() == 3) {
				setMethod(utils::trim(token[0]));
				setUrl(utils::trim(token[1]));
				setHttpVersion(utils::trim(token[2]));
			}
		}
		else {
			
			token = utils::split(header[i], ": ");
			
			if (token.size() == 2) {
				_headers.append(utils::trim(token[0]), utils::trim(token[1]));
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

}

void hhpp::Request::showRequest() {
	std::cout	<< getMethod() << " "
				<< getUrl() << " "
				<< getHttpVersion() << std::endl;
	_headers.showParams();
}

hhpp::Header &hhpp::Request::getHeaders() {
	return (_headers);
}
