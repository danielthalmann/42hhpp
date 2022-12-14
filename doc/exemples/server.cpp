#include <sys/types.h> /* Voir NOTES */
#include <sys/socket.h>
#include <errno.h>
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    void argc;
    void argv;

    // adresse localhost
    char    *ip = "127.0.0.1";
    // port TCP de la connexion
    int     port = 4242;

    int     server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    char    buffer[1024];
    int     n;

    server_sock = socket(PF_INET, SOCK_STREAM, 0);

    if (server_sock < 0)
    {
        perror("[-] socket error\n");
        exit(errno);
    }

    std::cout << "[+] TCP socket created." << std::endl;

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = PF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (n < 0)
    {
        perror("[-] bind error\n");
        exit(errno);
    }

    std::cout << "[+] bind the port number : " << port << std::endl;

    listen(server_sock, 5);

    std::cout << "[+] listening... " << std::endl;
   
    while (1)
    {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        std::cout << "[+] client connected. " << std::endl;
   
        bzero(buffer, 1024);

    }

    return (0);

}
