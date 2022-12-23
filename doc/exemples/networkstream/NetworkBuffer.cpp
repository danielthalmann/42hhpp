#include "NetworkBuffer.hpp"

NetworkBuffer::NetworkBuffer()
{
	_socket = 0;
	_connected = false;
	_listened = false;
}

NetworkBuffer::~NetworkBuffer()
{

}

void NetworkBuffer::setSocket(int s) 
{
	_socket = s;
}

int NetworkBuffer::getSocket() 
{
	return _socket;
}

bool NetworkBuffer::isConnected() 
{
	return _connected;
}

bool NetworkBuffer::isListened()
{
	return _listened;
}

void NetworkBuffer::closeConnection()
{
	if (_connected || _listened)
	{
		close(_socket);
		_connected = false;
		_listened = false;
		_socket = 0;
	}
}


void NetworkBuffer::startListen(const char *ip_addr, int port)
{
	struct sockaddr_in server_addr;
	int     result;

	_socket = socket(PF_INET, SOCK_STREAM, 0);

	if (_socket < 0)
		throw(Exceptions::SocketCreationError());

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip_addr);
	
	result = bind(_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

	if (result < 0)
		throw(Exceptions::BindFailed());

	result = listen(_socket, LISTEN_CONNECTION_LENGTH);

	if (result < 0)
		throw(Exceptions::ListenFailed());

	_listened = true;

}

void NetworkBuffer::startConnection(const char *ip_addr, int port)
{
	struct sockaddr_in server_addr;
	int     result;

	_socket = socket(PF_INET, SOCK_STREAM, 0);

	if (_socket < 0)
		throw(Exceptions::SocketCreationError());

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip_addr);

	result = connect(_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

	if (result < 0)
		throw(Exceptions::ConnectionFailed());

	_connected = true;
}


std::streamsize NetworkBuffer::xsputn(const char* buffer, std::streamsize size) 
{

	// transmet les données sur le socket
	int result = send(_socket, buffer, static_cast<int>(size), 0);
	
	// set up the buffer:
	_outputbuffer = buffer;

	// if that didn't work, throw an error
	if (result < 0)
	{
		_connected = false;
		throw(Exceptions::SocketSendError());
	}
	
	// NOTE: I realized after I wrote this that this throw may be useless, 
	// since I think iostream catches any errors thrown at this level, but 
	// just in case

	// set up the pointer
	if (_outputbuffer.size() == 0) {
		// do nothing. Probably throw an error in the future
		//setp(&_outputbuffer[0],&_outputbuffer[0],&_outputbuffer[0]);
	} else {
		setp(&_outputbuffer[0], &_outputbuffer[0], &_outputbuffer[_outputbuffer.size()-1] );
	}
	// now return the size
	return size;
}

std::streambuf::int_type NetworkBuffer::underflow() 
{
	const int readsize = 30;

	// first, check to make sure the buffer is not exausted:
	if(gptr() < egptr()) {
		return traits_type::to_int_type(*gptr());
	}

	// Now, let's read...

	// clear the buffer
	_inputbuffer.clear();
	_inputbuffer.resize(readsize+1); // +1 is to give our selves room to keep from crashing. Not a good solution, but it works, so...

	// lit les donnée du réseau
	int bytesread = recv(_socket, &_inputbuffer[0], static_cast<int>(readsize), 0);

	// return the end of file if we read no bytes
	if(bytesread == 0) {
		return traits_type::eof();
	}

	if(bytesread < 0)
	{
		connected = false;
		throw(Exceptions::SocketIOError("send"));
	}

	// set the pointers for the buffer...
	setg(&_inputbuffer[0], &_inputbuffer[0], &_inputbuffer[bytesread]);

	// finally, let's return the data type
	return traits_type::to_int_type(*gptr());

}