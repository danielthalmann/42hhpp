#include <iostream>

#include <sys/socket.h>

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
	struct sockaddr_in address;
	const int PORT = 8080; //Where the clients can reach at

	/* htonl converts a long integer (e.g. address) to a network representation */
	/* htons converts a short integer (e.g. port) to a network representation */
	memset((char *)&address, 0, sizeof(address));

//	https://stackoverflow.com/questions/57779761/why-does-the-sin-family-member-exist
	address.sin_family = AF_INET; // UDP,TCP, ...
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);

	//	int bind(int socket, const struct sockaddr *address, socklen_t address_len);
	if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0)
	{
		std::cerr << "[-] bind failed" << std::endl;
		return (errno);
	}
}
