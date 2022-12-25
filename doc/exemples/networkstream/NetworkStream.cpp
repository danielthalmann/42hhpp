#include "NetworkStream.hpp"

// Platform independent except for everything in Platform.h

// class network streambuff
// should handle the actual writing

// network stream constructors/destructor
NetworkStream::NetworkStream() : std::ios(0), std::iostream(new NetworkBuffer())
{
}

NetworkStream::NetworkStream(int socket) : std::ios(0), std::iostream(new NetworkBuffer())
{
	static_cast<NetworkBuffer *>(rdbuf())->setSocket(socket);
}

NetworkStream::~NetworkStream() 
{
	delete rdbuf();
}

void NetworkStream::setSocket(int socket) 
{
	static_cast<NetworkBuffer *>(rdbuf())->setSocket(socket);
}

int NetworkStream::getSocket() 
{
	return static_cast<NetworkBuffer *>(rdbuf())->getSocket();
}

bool NetworkStream::isConnected()
{
	return static_cast<NetworkBuffer *>(rdbuf())->isConnected();
}

void NetworkStream::listen(const char *ip_addr, int port)
{
	static_cast<NetworkBuffer *>(rdbuf())->startListen(ip_addr, port);
}

void NetworkStream::connect(const char *ip_addr, int port)
{
	static_cast<NetworkBuffer *>(rdbuf())->startConnection(ip_addr, port);
}

void NetworkStream::close()
{
	static_cast<NetworkBuffer *>(rdbuf())->closeConnection();
}

void NetworkStream::accept(NetworkStream stream)
{
	int socket = static_cast<NetworkBuffer *>(rdbuf())->acceptConnection();

	stream.setSocket(socket);
}


