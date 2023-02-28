#include "Request.hpp"
#include "utility.hpp"
#include <cstdlib>
#include <iostream>

namespace hhpp
{
	Request::Request()
	{
		_bodySize = 0;
		_port = 0;
		_methodType = METHOD_UNKNOW;
        _multipart = false;
	}

	Request::~Request()
	{
	}

	std::string Request::getMethod() const
	{
		return (_method);
	}
	std::string Request::getQuery() const
	{
		return (_query);
	}

	std::string Request::getHost() const
	{
		return (_host);
	}
	int Request::getPort() const
	{
		return (_port);
	}
	std::string Request::getUrl() const
	{
		return (_url);
	}
	std::string Request::getBody() const
	{
		return (_body);
	}
	std::string Request::getHttpVersion() const
	{
		return (_httpVersion);
	}
	int Request::getBodySize() const
	{
		return (_bodySize);
	}
	std::string Request::getBoundary() const
	{
		return (_boundary);
	}
	bool Request::isMultipart() const
	{
		return (_multipart);
	}	
	void Request::setMethod(std::string method)
	{
		_method = method;
		_methodType = METHOD_UNKNOW;
		if (_method == "GET")
		{
			_methodType = METHOD_GET;
			return;
		}
		if (_method == "HEAD")
		{
			_methodType = METHOD_HEAD;
			return;
		}
		if (_method == "POST")
		{
			_methodType = METHOD_POST;
			return;
		}
		if (_method == "PUT")
		{
			_methodType = METHOD_PUT;
			return;
		}
		if (_method == "DELETE")
		{
			_methodType = METHOD_DELETE;
			return;
		}
		if (_method == "CONNECT")
		{
			_methodType = METHOD_CONNECT;
			return;
		}
		if (_method == "OPTIONS")
		{
			_methodType = METHOD_OPTIONS;
			return;
		}
		if (_method == "TRACE")
		{
			_methodType = METHOD_TRACE;
			return;
		}
		if (_method == "PATCH")
		{
			_methodType = METHOD_PATCH;
			return;
		}
	}
	bool Request::isMethodType(method m) const
	{
		return (m == _methodType);
	}
	void Request::setQuery(std::string query)
	{
		_query = query;
	}
	void Request::setHost(std::string host)
	{
		_host = host;
	}
	void Request::setPort(int port)
	{
		_port = port;
	}
	void Request::setUrl(std::string url)
	{
		_url = url;
	}
	void Request::setBody(std::string body)
	{
		_body = body;
	}
	void Request::setHttpVersion(std::string httpVersion)
	{
		_httpVersion = httpVersion;
	}

	void Request::parseRequest(const std::string &rawRequest)
	{
		std::vector<std::string> token;
		std::vector<std::string> header;
		std::vector<std::string> query;
		std::string headerRaw;
		std::string body;

		size_t pos;

		pos = rawRequest.find("\r\n\r\n");
		if (pos != std::string::npos)
		{
			headerRaw = rawRequest.substr(0, pos);
			setBody(rawRequest.substr(pos + 4));
		}
		header = utils::split(headerRaw, "\r\n");

		_bodySize = 0;

		for (size_t i = 0; i < header.size(); i++)
		{
			if (i == 0)
			{
				token = utils::split(header[i], " ");

				if (token.size() == 3)
				{
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
				_headers.append(utils::trim(token[0]), utils::trim(token[1]));
			}
		}

		if (isMethodType(METHOD_POST))
		{
			treatContentType();
		}

		// extract host
		try
		{

			_host = _headers.get("Host");
			token = utils::split(_host, ":");
			if (token.size() == 2)
			{
				_host = token[0];
				_port = std::atoi(token[1].c_str());
			}
			else
				_port = 80;
		}
		catch (std::exception &e)
		{
		}

		try
		{
			_bodySize = std::atoi(_headers.get("Content-Length").c_str());
		}
		catch (std::exception &e)
		{
		}
	}

	void Request::treatContentType()
	{
		// 
		// detect if the post is multipart and set boundary value
		// 
		// Content-Type: multipart/form-data;boundary="boundary"
		//
		std::string contentType = _headers["Content-Type"];
		if (contentType.length() > 0)
		{
			std::vector<std::string> ct;
			std::vector<std::string> b;

			ct = utils::split(contentType, ";");
			if (ct.size() > 1)
			{
				if (utils::trim(ct[0]) == "multipart/form-data")
				{
					std::string bKeyValue = utils::trim(ct[1]);
					_multipart = true;
					b = utils::split(bKeyValue, "=");
					if (utils::trim(b[0]) == "boundary")
					{
						if (b[1][0] == '"')
						{
							_boundary = b[1].substr(1, b[1].size() - 2);
						} 
						else 
						{
							_boundary = b[1];
						}
					}
				}
			}
		}
	}

	void Request::showRequest()
	{
		std::cout << "show request" << std::endl;
		std::cout << getMethod() << " " << getUrl() << " " << getHttpVersion() << std::endl;
		std::cout << "headers:" << std::endl;
		_headers.showParams();
		std::cout << "end headers" << std::endl;

		std::cout << "body Size:" << _bodySize << std::endl;
		std::cout << "bodyContent:" << _body << std::endl;
		std::cout << "query:" << _query << std::endl;
		std::cout << "host:" << _host << std::endl;
		std::cout << "post:" << _port << std::endl;

		std::cout << "end show request" << std::endl;
	}

	hhpp::Header &Request::getHeaders()
	{
		return (_headers);
	}
} // namespace hhpp
