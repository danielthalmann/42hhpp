#include "NetworkBuffer.hpp"

NetworkBuffer::NetworkBuffer()
{
	_socket = 0;
	_connected = false;
	_listened = false;
	_inputbuffer = new char[NETWORK_BUFFER_LENGTH];
	_outputbuffer = new char[NETWORK_BUFFER_LENGTH];
}

NetworkBuffer::~NetworkBuffer()
{
	delete _inputbuffer;
	delete _outputbuffer;
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
		throw(NetworkException::SocketCreationError());

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip_addr);
	
	result = bind(_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

	if (result < 0)
		throw(NetworkException::BindFailed());

	result = listen(_socket, LISTEN_CONNECTION_LENGTH);

	if (result < 0)
		throw(NetworkException::ListenFailed());

	_listened = true;

}

void NetworkBuffer::startConnection(const char *ip_addr, int port)
{
	struct sockaddr_in server_addr;
	int     result;

	_socket = socket(PF_INET, SOCK_STREAM, 0);

	if (_socket < 0)
		throw(NetworkException::SocketCreationError());

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip_addr);

	result = connect(_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

	if (result < 0)
		throw(NetworkException::ConnectionFailed());

	_connected = true;
}


std::streamsize NetworkBuffer::xsputn(const char* buffer, std::streamsize size) 
{

	// transmet les données sur le socket
	int result = send(_socket, buffer, static_cast<int>(size), 0);
	
	// set up the buffer:
	strncpy(_outputbuffer, buffer, result);

	// if that didn't work, throw an error
	if (result < 0)
	{
		_connected = false;
		_listened = false;
		throw(NetworkException::SocketSendError());
	}
	
	// set up the pointer
	if (result == 0) {
		// do nothing. Probably throw an error in the future
	} else {
		setp(&_outputbuffer[0], &_outputbuffer[result] );
	}
	// now return the size
	return result;
}

std::streambuf::int_type NetworkBuffer::underflow() 
{
	// first, check to make sure the buffer is not exausted:
	if(gptr() < egptr()) {
		return traits_type::to_int_type(*gptr());
	}

	// lit les donnée du réseau
	int bytesread = recv(_socket, &_inputbuffer[0], NETWORK_BUFFER_LENGTH, 0);

	// return the end of file if we read no bytes
	if(bytesread == 0) {
		return traits_type::eof();
	}

	if(bytesread < 0)
	{
		_connected = false;
		_listened = false;
		throw(NetworkException::SocketReadError());
	}

	// set the pointers for the buffer...
	setg(&_inputbuffer[0], &_inputbuffer[0], &_inputbuffer[bytesread]);

	// finally, let's return the data type
	return traits_type::to_int_type(*gptr());

}

int NetworkBuffer::acceptConnection()
{
	struct sockaddr_in address; 
	int addrlen = sizeof(address);

 	return accept(_socket, 
                    (struct sockaddr *)&address, (socklen_t*)&addrlen);
}