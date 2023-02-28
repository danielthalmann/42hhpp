#include <iostream>

#include <Binding.hpp>
#include <CGI.hpp>
#include <ErrorPage.hpp>
#include <HHPP.hpp>
#include <Header.hpp>
#include <Location.hpp>
#include <MimeType.hpp>
#include <Redirect.hpp>
#include <Request.hpp>
#include <Response.hpp>
#include <ResponseFile.hpp>
#include <ResponseRedirect.hpp>
#include <Server.hpp>
#include <vector>
#include <Version.hpp>

#define CONFIG "./config/default.conf.json"

int main(int ac, char **av)
{
	std::cout << SERVER_VERSION << std::endl;

	if (ac < 1 || ac > 2)
	{
		std::cout << "error arguments" << std::endl;
		return (1);
	}

	hhpp::HHPP srv;

	std::string pathConfig = CONFIG;
	if (ac == 2) // config as param
		pathConfig = av[1];

	try
	{
		std::cout << "load config" << std::endl;
		srv.loadConfig(pathConfig);
	}
	catch (std::exception &e)
	{
		std::cout << "config loading error" << std::endl;
		return (1);
	}

	try
	{
		std::cout << "setup socket" << std::endl;
		srv.setupSocket();
	}
	catch (std::exception &e)
	{
		std::cout << "initialize socket error" << std::endl;
		return (1);
	}

	try
	{
		std::cout << "run srv" << std::endl;
		srv.run();
	}
	catch (std::exception &e)
	{
		std::cout << "server error : " << e.what() << std::endl;
		return (1);
	}

	//	const char* method[] = {"GET", "POST", "DELETE", NULL};
	//	std::cout << method[2] << std::endl;

	return (0);
}
