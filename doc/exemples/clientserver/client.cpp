#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
 
int main(int argc, char** argv)
{
 
	const char *ip = "127.0.0.1";

	int port = 8080;

	int ret;
	int sock;
	struct sockaddr_in addr;

	char buffer[1024];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		std::cerr << "[-] Socket error" << std::endl;	
		return (errno);
	}

	std::cout << "[+] TCP server socket created." << std::endl;	

	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);

	connect(sock, (struct sockaddr*)&addr, sizeof(addr));

	std::cout << "[+] Connected to the server." << std::endl;

	bzero(buffer, 1024);
	if (argc < 2)
		strcpy(buffer, "HELLO, THIS IS CLIENT.");
	else
		strcpy(buffer, argv[1]);

	std::cout << "[+] Client: " << buffer << std::endl;
	ret = send(sock, buffer, strlen(buffer), 0);

	if (ret < 0)
	{
		std::cerr << "[-] send error" << std::endl;	
		return (errno);
	}

	std::cout << "[+] bytes sended : " << ret << std::endl;

	do
	{
		bzero(buffer, 1024);
		ret = recv(sock, buffer, sizeof(buffer), 0);
		if (ret < 0)
		{
			std::cerr << "[-] recv error" << std::endl;	
			return (errno);
		}
		std::cout << "[+] bytes recived : " << ret << std::endl;
		if (ret > 0)
			std::cout << "[+] Server : " << buffer << std::endl;
	}while (ret > 0);

	close(sock);
	std::cout << "[+] Disconnected from the server." << std::endl;

	return 0;
}
