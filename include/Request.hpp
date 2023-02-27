#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "Header.hpp"
#include <string>

namespace hhpp
{
	class Request
	{
	public:
		Request();
		~Request();

		typedef enum e_method
		{
			METHOD_UNKNOW,
			METHOD_GET,
			METHOD_HEAD,
			METHOD_POST,
			METHOD_PUT,
			METHOD_DELETE,
			METHOD_CONNECT,
			METHOD_OPTIONS,
			METHOD_TRACE,
			METHOD_PATCH
		} method;

		std::string getMethod() const;
		std::string getQuery() const;
		std::string getHost() const;
		int getPort() const;
		std::string getUrl() const;
		std::string getBody() const;
		std::string getHttpVersion() const;
		int getBodySize() const;
		std::string getBoundary() const;

		void setMethod(std::string method);
		void setQuery(std::string query);
		void setHost(std::string host);
		void setPort(int port);
		void setUrl(std::string url);
		void setBody(std::string body);
		void setHttpVersion(std::string httpVersion);
        bool isMethodType(method m) const;
		bool isMultipart() const;

		void parseRequest(const std::string &rawRequest);
		void showRequest();
		Header &getHeaders();

    private:
    	void treatContentType();

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
		method _methodType;
        bool _multipart;
        std::string _boundary;
	};
} // namespace hhpp

#endif
