#include <netdb.h>
#include "Binding.hpp"

namespace hhpp {
	Binding::Binding() {}

	Binding::~Binding() {}

	void Binding::checkSocket(int ret, const char* str) {
		if (ret < 0)
		{
			std::cerr << str << std::endl;
			close(_listen_sd);
			perror(str);
			throw(Binding::socketStatus());
		}
	}

	void Binding::createSocket() {
		_listen_sd = socket(PF_INET, SOCK_STREAM, 0);
		if (_listen_sd < 0)
		{
			std::cerr << "[-] socket() failed" << std::endl;
			throw(Binding::socketStatus());
		}
	}

	void Binding::setNonBlocking() {
		int ret;
		int on = 1;

//		allow socket to be reuseable
		ret = setsockopt(_listen_sd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
		checkSocket(ret, "[-] setsockopt() failed");

//		set socket nonblocking
		ret = fcntl(_listen_sd, F_SETFL, O_NONBLOCK);
		checkSocket(ret, "[-] nonblocking failed");
	}

	sockaddr_in Binding::bindSocket() {
		int ret;
		sockaddr_in addr;

		memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
//		addr.sin_addr.s_addr = inet_addr(_ip.c_str());
		addr.sin_port = htons(_port);

		ret = bind(_listen_sd, (struct sockaddr *)&addr, sizeof(addr));
		checkSocket(ret, "[-] bind failed");

		return (addr);
	}

	void Binding::listenSocket() {
		int ret;
		ret = listen(_listen_sd, 15);
		checkSocket(ret, "[-] listen failed");
	}

	void Binding::setSocket() {
		sockaddr_in addr;

		createSocket();

		setNonBlocking();

		addr = bindSocket();

		listenSocket();

//TODO put to run and lean
		int ret;
		fd_set current_set;
		fd_set working_set;
		int max_sd, new_sd;

//		init fds
		FD_ZERO(&current_set);
		max_sd = _listen_sd;
		FD_SET(_listen_sd, &current_set);

		int desc_ready, end_server = 0;
		int close_conn;
		int len;
		char buffer[80];
		struct timeval timeout;
		timeout.tv_sec  = 10;
		timeout.tv_usec = 0;
		do
		{
//			copy into working set
			memcpy(&working_set, &current_set, sizeof(current_set));

//			select
			std::cout << "Waiting on select()..." << std::endl;
			ret = select(max_sd + 1, &working_set, NULL, NULL, &timeout);
			if (ret < 0)
			{
				std::cerr << "[-] select() failed" << std::endl;
				break;
			}
			if (ret == 0)
			{
				std::cerr << "[-] select() timed out" << std::endl;
				break;
			}

			desc_ready = ret;
			for (int i = 0; i <= max_sd && desc_ready > 0; ++i)
			{
				if (FD_ISSET(i, &working_set))
				{
					desc_ready -= 1;
					if (i == _listen_sd)
					{
						std::cout << "Listening socket is readable" << std::endl;
						do
						{
							new_sd = accept(_listen_sd, NULL, NULL);
							if (new_sd < 0)
							{
								if (errno != EWOULDBLOCK)
								{
									std::cerr << "[-] accept() failed" << std::endl;
									end_server = 1;
								}
								break;
							}
							std::cout << "New incoming connection - " << new_sd << std::endl;
							FD_SET(new_sd, &current_set);
							if (new_sd > max_sd)
								max_sd = new_sd;

						} while (new_sd != -1);
					}
					else
					{
						std::cout << "Descriptor " << i << " is readable" << std::endl;
						close_conn = 0;
						do
						{
							ret = recv(i, buffer, sizeof(buffer), 0);
							if (ret < 0)
							{
								if (errno != EWOULDBLOCK)
								{
									std::cout << "recv() finish" << std::endl;
									close_conn = 1;
								}
								break;
							}
							if (ret == 0)
							{
								std::cout << "Connection closed" << std::endl;
								close_conn = 1;
								break;
							}
							len = ret;
							std::cout << len << " bytes received" << std::endl;

//							send data to client
							char hello[] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 10\n\nHello test!";
							ret = send(i, hello, strlen(hello), 0);
							if (ret < 0)
							{
								std::cerr << "[-] send() failed" << std::endl;
								close_conn = 1;
								break;
							}

						} while (1);

						if (close_conn)
						{
							close(i);
							FD_CLR(i, &current_set);
							if (i == max_sd)
							{
								while (FD_ISSET(max_sd, &current_set) == 0)
									max_sd -= 1;
							}
						}
					}
				}
			}

		} while (end_server == 0);
	}

	void Binding::setIP(std::string ip) {
		_ip = ip;
	}

	void Binding::setPort(int port) {
		_port = port;
	}

	void Binding::sendData(std::string str) {
		(void)str;
	}

	void Binding::sendData(Response response) {
		(void)response;
	}

	Request Binding::readHeader(std::string header) {
		(void)header;
		return (Request());
	}

	const char* Binding::socketStatus::what() const throw() {
		return ("Socket Error");
	}
}
