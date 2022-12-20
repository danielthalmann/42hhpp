#include <iostream>

#include <unistd.h>

#include <arpa/inet.h>
#include <cstring>

#include <fcntl.h>

#include <sys/socket.h>

#include <fstream>

//doc
// https://www.geeksforgeeks.org/socket-programming-cc/
// https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa
// https://web.maths.unsw.edu.au/~lafaye/CCM/sockets/sockfonc.htm

// https://beej.us/guide/bgnet/html/#system-calls-or-bust
// https://stackoverflow.com/questions/6729366/what-is-the-difference-between-af-inet-and-pf-inet-in-socket-programming#:~:text=Meaning%2C%20AF_INET%20refers%20to%20addresses,protocol%2C%20usually%20sockets%2Fports.

int main() {
	std::cout << "Hello http" << std::endl << std::endl;

	std::cout << "Create a socket" << std::endl;
//	int socket(int domain, int type, int protocol);
	int server_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		std::cerr << "[-] socket error creation" << std::endl;
		return (errno);
	}

	std::cout << std::endl << "Indentify(name/naming/binding) a socket" << std::endl;
	struct sockaddr_in addr;
	int addrlen = sizeof(addr);
	const int PORT = 8080; //Where the clients can reach at
	const char *ADDRESS = "127.0.0.1"; //Where the clients can reach at

	/* htonl converts a long integer (e.g. address) to a network representation */
	/* htons converts a short integer (e.g. port) to a network representation */
//	memset((char *)&addr, 0, sizeof(addr));
	memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));

//	https://stackoverflow.com/questions/57779761/why-does-the-sin-family-member-exist
	addr.sin_family = AF_INET; // UDP,TCP, ...
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);

	//	int bind(int socket, const struct sockaddr *address, socklen_t address_len);
	if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		std::cerr << "[-] bind failed" << std::endl;
		return (errno);
	}

	std::cout << std::endl << "listen and accept" << std::endl;
//	int listen(int socket, int backlog);
	if (listen(server_fd, 3) < 0)
	{
		std::cerr << "[-] In listen" << std::endl;
		exit(errno);
	}

	while (1)
	{
	//	int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
		int new_socket = accept(server_fd, (struct sockaddr *)&addr, (socklen_t*)&addrlen);
		if (new_socket < 0)
		{
			std::cerr << "[-] In accept" << std::endl;
			exit(errno);
		}

//		std::cout << std::endl << "send and receive" << std::endl;
		char buffer[30000] = {0};
		int valread = read(new_socket, buffer, 30000);
//		printf("%s\n", buffer);
		std::string s(buffer);
//		std::cout << s << std::endl;
		if(valread < 0)
			printf("No bytes are there to read");

//		char hello[] = "HTTP/1.1 200 OK\\nContent-Type: text/plain\\nContent-Length: 12\\n\\nHello world!\"";//IMPORTANT! WE WILL GET TO IT
		if (s.find("42lwatch.html") != std::string::npos)
		{
//			std::cout << "info.html" << std::endl;
			std::string file = "";
			std::string line;
			std::ifstream ifs("42lwatch.html");
			if (ifs.fail())
			{
				std::cout << "file error" << std::endl;
				continue;
			}

			while (std::getline(ifs, line))
			{
				file += line;
			}

//			std::cout << file << std::endl;
			std::string buffer = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
			buffer.append(std::to_string(file.size()));
			buffer.append("\n\n");
			buffer.append(file);

//			std::cout << buffer << std::endl;
			write(new_socket, buffer.c_str(), strlen(buffer.c_str()));
		}
		else
		{
			std::cout << "other page" << std::endl;
			char hello[] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 11\n\nHello alex!";
			write(new_socket, hello, strlen(hello));
		}

		std::cout << std::endl << "close" << std::endl;
		close(new_socket);
	}
}
