// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>

#define PORT 8080

int main(int argc, char const *argv[]) {
	int sock = 0;
	long valread;
	struct sockaddr_in serv_addr;
//	char hello[] = "GET /42lwatch.html HTTP/1.1";
	char buffer[1024] = {0};

	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Socket creation error" << std::endl;
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//	std::cout <<  inet_addr("127.0.0.1") << std::endl;

	// Convert IPv4 and IPv6 addresses from text to binary form

//	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
//	{
//		printf("\nInvalid address/ Address not supported \n");
//		return -1;
//	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cerr << "Connection Failed" << std::endl;
		return -1;
	}
	send(sock , argv[1] , strlen(argv[1]) , 0 );
	std::cout << "Hello message sent" << std::endl;
	valread = read( sock , buffer, 1024);
	std::cout << buffer << std::endl;
	return 0;
}