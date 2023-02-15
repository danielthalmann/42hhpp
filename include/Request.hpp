#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>
#include "Header.hpp"

namespace hhpp {
	class Request
	{
	public:
		Request();
		~Request();

		std::string getMethod() const;
		std::string getQuery() const;
		std::string getHost() const;
		int getPort() const;
		std::string getUrl() const;
		std::string getBody() const;
		std::string getHttpVersion() const;
		int getBodySize() const;

		void setMethod(std::string method);
		void setQuery(std::string query);
		void setHost(std::string host);
		void setPort(int port);
		void setUrl(std::string url);
		void setBody(std::string body);
		void setHttpVersion(std::string httpVersion);

		void parseRequest(const std::string& rawRequest);
		void showRequest();
		Header& getHeaders();

	private:
		int _bodySize;
		std::string _method;
		std::string _url;
		std::string _httpVersion;
		Header _headers;
		std::string _query;
		std::string _host;
		int _port;
		std::string _body;

	};
}

#endif
