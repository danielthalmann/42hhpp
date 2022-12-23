#ifndef NETWORKSTREAM_HPP
#define NETWORKSTREAM_HPP

#include "NetworkException.hpp"
#include "NetworkBuffer.hpp"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <unistd.h>

// so, this stream runs the basic reading and writing from the network,
// platform independently (except where specified in Platform.h), hopefully


// Special thanks to Cay S. Horstmann, who without this post: http://www.horstmann.com/cpp/iostreams.html
// I wouldn't be able to make any of this

class NetworkStream : public std::iostream {
	public: 
	
		typedef int Socket;

		// constructors
		NetworkStream();
		virtual ~NetworkStream(); 

		// other functions 

		// see if we are connected
		bool isConnected();

		void listen(const char *ip_addr, int port);
		void connect(const char *ip_addr, int port);

	protected:
		// prevent copying
		NetworkStream(const NetworkStream&);
		void operator=(const NetworkStream&);

		// internal functions to manipulate our socket.
		void setSocket(Socket socket);

		Socket getSocket();

}; 


#endif