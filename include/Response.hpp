
#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "IServer.hpp"
#include <string>
#include "Header.hpp"


namespace hhpp {

	class Response
	{
	public:
		Response();
		virtual ~Response();

		std::string& getVersion();
		int& getStatus();
		Header& getHeaders();
		std::string& getBody();

		void setStatus(int status);
		void setContentType(std::string contentType);
		void setBody(std::string str);
		void setServer(IServer *server);

		IServer *getServer();

		std::string getStatusMessage() const;

		typedef std::map<int, std::string>	mapIntString;
		virtual std::string raw();

		std::string get404();
	protected:

		virtual void prepareResponse();

		IServer *_server;
		std::string _version;
		int _status;
		std::string _statusMessage;
		Header _header;
		std::string _body;
		std::string _contentType;
		static std::map<int, std::string> _totalStatus;

		static mapIntString init_map() {
			mapIntString tmp;
			tmp[101] = "Switching Protocols";
			tmp[102] = "Processing";
			tmp[103] = "Early Hints";
			tmp[200] = "OK";
			tmp[201] = "Created";
			tmp[202] = "Accepted";
			tmp[203] = "Non-Authoritative Information";
			tmp[204] = "No Content";
			tmp[205] = "Reset Content";
			tmp[206] = "Partial Content";
			tmp[207] = "Multi-Status";
			tmp[208] = "Already Reported";
			tmp[226] = "IM Used";
			tmp[300] = "Multiple Choices";
			tmp[301] = "Moved Permanently";
			tmp[302] = "Found";
			tmp[303] = "See Other";
			tmp[304] = "Not Modified";
			tmp[305] = "Use Proxy";
			tmp[306] = "Switch Proxy";
			tmp[307] = "Temporary Redirect";
			tmp[308] = "Permanent Redirect";
			tmp[400] = "Bad Request";
			tmp[401] = "Unauthorized";
			tmp[402] = "Payment Required";
			tmp[403] = "Forbidden";
			tmp[404] = "Not Found";
			tmp[405] = "Method Not Allowed";
			tmp[406] = "Not Acceptable";
			tmp[407] = "Proxy Authentication Required";
			tmp[408] = "Request Timeout";
			tmp[409] = "Conflict";
			tmp[410] = "Gone";
			tmp[411] = "Length Required";
			tmp[412] = "Precondition Failed";
			tmp[413] = "Payload Too Large";
			tmp[414] = "URI Too Long";
			tmp[415] = "Unsupported Media Type";
			tmp[416] = "Range Not Satisfiable";
			tmp[417] = "Expectation Failed";
			tmp[418] = "I'm a teapo";
			tmp[421] = "Misdirected Request";
			tmp[422] = "Unprocessable Entity";
			tmp[423] = "Locked";
			tmp[424] = "Failed Dependency";
			tmp[425] = "Too Early";
			tmp[426] = "Upgrade Required";
			tmp[428] = "Precondition Required";
			tmp[429] = "Too Many Requests";
			tmp[431] = "Request Header Fields Too Large";
			tmp[451] = "Unavailable For Legal Reasons";
			tmp[500] = "Internal Server Error";
			tmp[501] = "Not Implemented";
			tmp[502] = "Bad Gateway";
			tmp[503] = "Service Unavailable";
			tmp[504] = "Gateway Timeout";
			tmp[505] = "HTTP Version Not Supported";
			tmp[506] = "Variant Also Negotiates";
			tmp[507] = "Insufficient Storage";
			tmp[508] = "Loop Detected";
			tmp[510] = "Not Extended";
			tmp[511] = "Network Authentication Required";
			return tmp;
		}

	};
}

#endif
