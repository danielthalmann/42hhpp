#ifndef BINDING_HPP
#define BINDING_HPP

#include "IBinding.hpp"
#include "Request.hpp"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <map>

#include <arpa/inet.h>
#include <cstring>

#include <cerrno>
#include <cstdio>
#include <fcntl.h>
#include <sstream>
#include <string>
#include <sys/socket.h>

namespace hhpp
{
	class Binding : public IBinding
	{
	public:

		typedef enum e_state {
			STATE_CREATED,
			STATE_READ,
			STATE_LOADED,
			STATE_ERROR
		} t_state;
		typedef struct s_connection {
			int socket;
			int len;
			std::string buff;
			t_state state;
		} t_connection;

	public:
		Binding();
		virtual ~Binding();

		virtual void setSocket();
		virtual void setIP(const std::string &ip);
		virtual void setPort(const int port);
		virtual void addServer(IServer *server);
		virtual int acceptConnection();
		virtual void closeConnection(int socket);
		virtual bool hasConnection(const int socket);
		virtual bool isRequestLoaded(int socket);
		virtual std::string &getRequestBuffer(int socket);
		virtual void readRequest(int socket);

		virtual IServer *getServerFor(const Request &request) const;

		virtual std::string getIP() const;
		virtual int getPort() const;
		virtual int getSocket() const;

		virtual void sendData(std::string str);
		virtual void sendData(Response response);
		virtual Request readHeader(std::string header);
		virtual bool isBinding(const std::string &ip, const int port);

		void checkSocket(int ret, const char *str);

	private:
		void createSocket();
		void setNonBlocking();
		struct sockaddr_in bindSocket();
		void listenSocket();

		std::vector<IServer *> _servers;
		std::map<int, t_connection *> _connections;
		int _listen_sd;
		std::string _ip;
		int _port;
	};
} // namespace hhpp

#endif
