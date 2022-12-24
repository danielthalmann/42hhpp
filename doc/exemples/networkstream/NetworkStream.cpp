#include "NetworkStream.hpp"

// Platform independent except for everything in Platform.h

// class network streambuff
// should handle the actual writing

// network stream constructors/destructor
NetworkStream::NetworkStream() : std::ios(0), std::iostream(new NetworkBuffer())
{

}

NetworkStream::~NetworkStream() 
{
	delete rdbuf();
}

void NetworkStream::setSocket(NetworkStream::Socket socket) 
{
	static_cast<NetworkBuffer *>(rdbuf())->setSocket(socket);
}

NetworkStream::Socket NetworkStream::getSocket() 
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


