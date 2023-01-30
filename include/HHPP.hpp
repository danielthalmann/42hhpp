#ifndef HHPP_HPP
#define HHPP_HPP

#include <string>
#include <algorithm>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>

#include "Server.hpp"
#include "Binding.hpp"
#include "Request.hpp"

namespace json { class JsonValue; } // TODO a supprimer

namespace hhpp {
	class HHPP
	{
	public:

		HHPP();
		~HHPP();

		void loadConfig(std::string pathConfig);
		void run();

		void create_socket(std::string ip, int port);

		class fileStatus: public std::exception {
		public:
			virtual const char* what() const throw();
		};

		class socketStatus: public std::exception {
		public:
			virtual const char* what() const throw();
		};

	private:

		std::vector<IServer*> _servers;
		std::vector<IBinding*> _bindings;

		std::string readFileConfig(std::string pathConfig);
		void dispatchRequest(Request request);

	};
}

#endif
