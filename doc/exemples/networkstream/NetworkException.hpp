#ifndef NETWORKEXCEPTION_H
#define NETWORKEXCEPTION_H

#include <exception>
#include <string>

namespace NetworkException {

	class NoRouteToHost : public std::exception {
		public:
		virtual const char* what() {
			return "Could not resolve host or port";
		}
	};

	class ConnectionFailed : public std::exception {
		public:
		virtual const char* what() throw(){
			return "Unable to connect to host";
		}
	};

	class BindFailed : public std::exception {
		public:
		virtual const char* what() throw(){
			return "Bind failed";
		}
	};

	class ListenFailed : public std::exception {
		public:
		virtual const char* what() throw(){
			return "Listen failed";
		}
	};

	class SocketCreationError : public std::exception {
		public:
		virtual const char* what() throw(){
			return "Socket creation failed";
		}
	};

	// io errors
	class SocketIOError : public std::exception {
		public:
			virtual const char* what() throw(){
				return "Socket encouneted a io error from the socket";
			}
	};

	// io errors
	class SocketSendError : public SocketIOError {
		public:
			virtual const char* what() throw(){
				return "Socket encouneted a send error from the socket";
			}
	};

	// io errors
	class SocketReadError : public SocketIOError {
		public:
			virtual const char* what() throw(){
				return "Socket encouneted a read error from the socket";
			}
	};

};

#endif