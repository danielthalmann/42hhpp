#ifndef HHPP_HPP
#define HHPP_HPP

#include <algorithm>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include "Binding.hpp"
#include "MimeType.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Server.hpp"

namespace hhpp
{
	class HHPP
	{
	public:
		HHPP();
		~HHPP();

		void loadConfig(std::string pathConfig);
		void run();

		void setupSocket();

		class fileStatus : public std::exception
		{
		public:
			virtual const char *what() const throw();
		};

	private:
		std::vector<IServer *> _servers;
		std::vector<IBinding *> _bindings;

		IBinding *isListen(int socket);
		IBinding *getBindingFromSocket(int socket);

		std::string readFileConfig(std::string pathConfig);
		void dispatchRequest(Request request);
	};
} // namespace hhpp

#endif
