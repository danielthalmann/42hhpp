#include "Request.hpp"
#include "utility.hpp"
#include <iostream>

//GET /danielthalmann/42hhpp/blob/sandbox/doc/sandbox/srv.cpp HTTP/2
//Host: github.com
//User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:107.0) Gecko/20100101 Firefox/107.0
//Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
//Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3
//Accept-Encoding: gzip, deflate, br
//Connection: keep-alive
//Cookie: _gh_sess=lWGsPzmTJX9%2B0WiIMqxVvmOveNT8a3WEiCTHEH803rJ5sDx7AYNyfCBl0AKyuASCcvKYepvRSLkgLWQfLF27nxcMlmN5bwWjYLWI%2BDh%2BMlfcOPMm7Is444GT027igJVDiubkj4r3IFPhp5xyZQvoA5fOy5ctxLUc43ZomirZwT0bP78282EaDXVlIyi0dUr0KTMP%2FShh0COoCwSuezaRvrBGdfI75FBmiXR4GAmnfiIODHbP78pUpxw%2BXzC7pzvI0lieohwAdxCMbwejdIpYFg%3D%3D--SAaQ8tRLGwObTAk5--aWDIwbYACugp8b%2B2ppvCJQ%3D%3D; _octo=GH1.1.2064806961.1674550506; logged_in=no; preferred_color_mode=dark; tz=Europe%2FZurich
//Upgrade-Insecure-Requests: 1
//Sec-Fetch-Dest: document
//Sec-Fetch-Mode: navigate
//Sec-Fetch-Site: cross-site
//TE: trailers

hhpp::Request::Request() {
	setPort(0);
}
hhpp::Request::~Request() {}


std::string hhpp::Request::getMethod() { return (_method); }
std::string hhpp::Request::getQuery() { return (_query); }
std::string hhpp::Request::getHost() { return (_host); }
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

void hhpp::Request::setRequest(const std::string& rawRequest) {
	std::vector<std::string> token;
	std::vector<std::string> header;

	header = utils::split(rawRequest, "\n");
	for (size_t i = 0; i < header.size(); i++) {
		size_t pos;
		pos = header[i].find(":");
		if (pos == std::string::npos)
			token = utils::split(header[i], " ");
		else
			token = utils::split(header[i], ": ");

		if (pos == std::string::npos)
		{
			setMethod(token[0]);
			setUrl(token[1]);
			setHttpVersion(token[2]);
		}
		else
			_headers.append(token[0], token[1]);
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
