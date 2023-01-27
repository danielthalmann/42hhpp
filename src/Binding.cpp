#include "Binding.hpp"

namespace hhpp {
	Binding::Binding() {}

	Binding::~Binding() {}

	void Binding::setSocket(int socket) {
		_socked = socket;
	//	_socked = socket(PF_INET, SOCK_STREAM, 0);
	//	if (_socked < 0)
	//	{
	//		std::cerr << "[-] socket error creation" << std::endl;
	//		exit(errno);
	//	}
	}

	void Binding::setIP(std::string ip) {
		_ip = ip;
	}

	void Binding::setPort(int port) {
		_port = port;
	}

	void Binding::send(std::string str) {
		(void)str;
	}

//	void Binding::send(Response response) {
//		(void)response;
//	}

	Request Binding::readHeader(std::string header) {
		(void)header;
		return (Request());
	}
}
