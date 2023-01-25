#ifndef ARESPONSE_HPP
#define ARESPONSE_HPP

#include <string>
#include "Header.hpp"
#include "Request.hpp"

namespace hhpp {
	class AResponse
	{
	public:
		AResponse();
		virtual ~AResponse();

		std::string& getVersion();
		int& getStatus();
		std::string& getStatusMessage();
		Header& getHeaders();
		std::string& getBody();

		void setStatus(int status);
		void setStatusMessage(std::string statusMessage);
		virtual void setResponse(Request& request, int status) = 0;

		typedef std::map<int, std::string>	mapIntString;
		void setTotalStatus(int i, std::string str);

	protected:
		std::string _version;
		int _status;
		std::string _statusMessage;
		Header _header;
		std::string _body;
		static std::map<int, std::string> _totalStatus;

		static mapIntString init_map() {
			mapIntString some_map;
			some_map[101] = "Switching Protocols";
			some_map[102] = "Processing";
			some_map[103] = "Early Hints";
			some_map[200] = "OK";
			some_map[201] = "Created";
			some_map[202] = "Accepted";
			some_map[203] = "Non-Authoritative Information";
			some_map[204] = "No Content";
			some_map[205] = "Reset Content";
			some_map[206] = "Partial Content";
			some_map[207] = "Multi-Status";
			some_map[208] = "Already Reported";
			some_map[226] = "IM Used";
			some_map[300] = "Multiple Choices";
			some_map[301] = "Moved Permanently";
			some_map[302] = "Found";
			some_map[303] = "See Other";
			some_map[304] = "Not Modified";
			some_map[305] = "Use Proxy";
			some_map[306] = "Switch Proxy";
			some_map[307] = "Temporary Redirect";
			some_map[308] = "Permanent Redirect";
			some_map[400] = "Bad Request";
			some_map[401] = "Unauthorized";
			some_map[402] = "Payment Required";
			some_map[403] = "Forbidden";
			some_map[404] = "Not Found";
			some_map[405] = "Method Not Allowed";
			some_map[406] = "Not Acceptable";
			some_map[407] = "Proxy Authentication Required";
			some_map[408] = "Request Timeout";
			some_map[409] = "Conflict";
			some_map[410] = "Gone";
			some_map[411] = "Length Required";
			some_map[412] = "Precondition Failed";
			some_map[413] = "Payload Too Large";
			some_map[414] = "URI Too Long";
			some_map[415] = "Unsupported Media Type";
			some_map[416] = "Range Not Satisfiable";
			some_map[417] = "Expectation Failed";
			some_map[418] = "I'm a teapo";
			some_map[421] = "Misdirected Request";
			some_map[422] = "Unprocessable Entity";
			some_map[423] = "Locked";
			some_map[424] = "Failed Dependency";
			some_map[425] = "Too Early";
			some_map[426] = "Upgrade Required";
			some_map[428] = "Precondition Required";
			some_map[429] = "Too Many Requests";
			some_map[431] = "Request Header Fields Too Large";
			some_map[451] = "Unavailable For Legal Reasons";
			some_map[500] = "Internal Server Error";
			some_map[501] = "Not Implemented";
			some_map[502] = "Bad Gateway";
			some_map[503] = "Service Unavailable";
			some_map[504] = "Gateway Timeout";
			some_map[505] = "HTTP Version Not Supported";
			some_map[506] = "Variant Also Negotiates";
			some_map[507] = "Insufficient Storage";
			some_map[508] = "Loop Detected";
			some_map[510] = "Not Extended";
			some_map[511] = "Network Authentication Required";
			return some_map;
		}

	};
}

#endif
