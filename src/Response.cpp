#include "Response.hpp"

namespace hhpp {
	Response::Response() {}

	Response::~Response() {}

	//request
	//*GET / HTTP/1.1
	//*Host: www.quicksite.ch
	//User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:107.0) Gecko/20100101 Firefox/107.0
	//*Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
	//Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3
	//Accept-Encoding: gzip, deflate, br
	//Connection: keep-alive
	//Upgrade-Insecure-Requests: 1
	//Sec-Fetch-Dest: document
	//Sec-Fetch-Mode: navigate
	//Sec-Fetch-Site: none
	//Sec-Fetch-User: ?1

	//minimum
	//*HTTP/1.1 200 OK
	//*Content-Type: text/html; Charset=utf-8
	//*Content-Length: 34971
	//**Transfer-Encoding: chunked
	//**body
	//?Connection: close

	//response
	//HTTP/1.1 200 OK
	//Cache-Control: no-cache,must-revalidate
	//Content-Type: text/html; Charset=utf-8
	//Content-Encoding: gzip
	//Vary: Accept-Encoding
	//Server: Webserver
	//Set-Cookie: SiteSettings=clear; expires=Tue, 24-Jan-2023 12:51:20 GMT; path=/; secure; HttpOnly;
	//Set-Cookie: lngStatQSSession=1056898499; expires=Thu, 25-Jan-2024 12:51:20 GMT; path=/; secure; HttpOnly;
	//Access-Control-Allow-Origin: *
	//Strict-Transport-Security: max-age=63072000; includeSubDomains; preload
	//X-Frame-Options: SAMEORIGIN
	//X-Xss-Protection: 1; mode=block
	//X-Content-Type-Options: nosniff
	//Date: Wed, 25 Jan 2023 12:51:21 GMT
	//Content-Length: 34971

	//https://fr.wikipedia.org/wiki/Chunked_transfer_encoding

	void Response::setResponse(Request& request, int status) {
		_version = request.getHttpVersion();
		_status = status;
		_statusMessage = _totalStatus[_status];
		_header = request.getHeaders();
	}

	void Response::showResponse() {
		std::cout	<< _version << " "
					<< _status << " "
					<< _statusMessage << std::endl;
		_header.showParams();
		if (!_body.empty())
			std::cout << _body << std::endl;
	}

}
