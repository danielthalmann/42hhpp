#include "Binding.hpp"
#include "Response.hpp"
#include <algorithm>

namespace hhpp
{
	Binding::Binding()
	{
	}

	Binding::~Binding()
	{
	}

	void Binding::checkSocket(int ret, const char *str)
	{
		if (ret < 0)
		{
			std::cerr << str << std::endl;
			close(_listen_sd);
			perror(str);
			throw(Binding::socketStatus());
		}
	}

	void Binding::createSocket()
	{
		_listen_sd = socket(PF_INET, SOCK_STREAM, 0);
		if (_listen_sd < 0)
		{
			std::cerr << "[-] socket() failed" << std::endl;
			throw(Binding::socketStatus());
		}
	}

	void Binding::setNonBlocking()
	{
		int ret;
		int on = 1;

		//		allow socket to be reuseable
		ret = setsockopt(_listen_sd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
		checkSocket(ret, "[-] setsockopt() failed");

		//		set socket nonblocking
		ret = fcntl(_listen_sd, F_SETFL, O_NONBLOCK);
		checkSocket(ret, "[-] nonblocking failed");
	}

	struct sockaddr_in Binding::bindSocket()
	{
		int ret;
		struct sockaddr_in addr;

		memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
		//		addr.sin_addr.s_addr = inet_addr(_ip.c_str());
		addr.sin_port = htons(_port);

		ret = bind(_listen_sd, (struct sockaddr *)&addr, sizeof(addr));
		checkSocket(ret, "[-] bind failed");

		return (addr);
	}

	void Binding::listenSocket()
	{
		int ret;
		ret = listen(_listen_sd, 32);
		checkSocket(ret, "[-] listen failed");
	}

	void Binding::setSocket()
	{
		struct sockaddr_in addr;

		createSocket();
		setNonBlocking();
		addr = bindSocket();
		listenSocket();
	}

	void Binding::addServer(IServer *server)
	{
		_servers.push_back(server);
	}

	void Binding::setIP(const std::string &ip)
	{
		_ip = ip;
	}

	void Binding::setPort(const int port)
	{
		_port = port;
	}

	std::string Binding::getIP() const
	{
		return _ip;
	}

	int Binding::getPort() const
	{
		return _port;
	}

	int Binding::getSocket() const
	{
		return _listen_sd;
	}

	void Binding::sendData(std::string str)
	{
		(void)str;
	}

	void Binding::sendData(Response response)
	{
		(void)response;
	}

	Request Binding::readHeader(std::string header)
	{
		(void)header;
		return (Request());
	}

	const char *Binding::socketStatus::what() const throw()
	{
		return ("Socket Error");
	}

	bool Binding::isBinding(const std::string &ip, const int port)
	{
		if (_ip == ip && _port == port)
			return true;
		return false;
	}

	IServer *Binding::getServerFor(const Request &request) const
	{
		for (std::vector<IServer *>::const_iterator it = _servers.begin(); it != _servers.end(); it++)
		{
			if ((*it)->isForMe(request))
			{
				return (*it);
			}
		}
		return _servers[0];
	}

	int Binding::acceptConnection()
	{
		int new_sd;
		new_sd = accept(_listen_sd, NULL, NULL);
		if (new_sd > 0){
			t_connection* conn = new t_connection;
			conn->state = STATE_CREATED;
			conn->socket = new_sd;
			conn->len = 0;
			_connections[new_sd] = conn;
		}
		return new_sd;
	}

	bool Binding::hasConnection(const int socket)
	{
		try
		{
			_connections.at(socket);
		}
		catch (std::exception &e)
		{
			(void)e;
			return false;
		}

		return true;
	}

	bool Binding::isRequestLoaded(int socket)
	{
		if (_connections[socket]->state == STATE_LOADED)
			return true;
		return false;
	}

	std::string &Binding::getRequestBuffer(int socket) 
	{
		return _connections[socket]->buff;
	}

	void Binding::readRequest(int socket)
	{
		int ret;
		int len;
		char buffer[4096];		
		t_connection *conn = _connections[socket];

		bzero(buffer, sizeof(buffer));
		ret = recv(conn->socket, buffer, sizeof(buffer), 0);
		if (ret < 0) {
			conn->state = STATE_ERROR;
		} else if (ret == 0) {
			conn->state = STATE_LOADED;
		} else {
			conn->len += ret;
		}

		if (conn->state == STATE_CREATED)
		{
			conn->buff.append(buffer, ret);
			// vérifie la taille du body

		}


	}

	void Binding::closeConnection(int socket)
	{
		_connections.erase(std::find(_connections.begin(), _connections.end(), socket));
		close(socket);
	}

} // namespace hhpp
