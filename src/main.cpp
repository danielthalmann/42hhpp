#include <iostream>

#include <AResponse.hpp>
#include <Binding.hpp>
#include <CGI.hpp>
#include <ErrorPage.hpp>
#include <Header.hpp>
#include <HHPP.hpp>
#include <Location.hpp>
#include <MimeType.hpp>
#include <Redirect.hpp>
#include <Request.hpp>
#include <Response.hpp>
#include <ResponseFile.hpp>
#include <ResponseRedirect.hpp>
#include <Server.hpp>
#include <vector>

#define CONFIG "./config/default.conf.json"

int main(int ac, char** av) {
	if (ac < 1 || ac > 2)
	{
		std::cout << "error arguments" << std::endl;
		return(1);
	}

	hhpp::HHPP srv;

	std::string pathConfig = CONFIG;
	if (ac == 2)// config as param
		pathConfig = av[1];

	try
	{
//		std::cout << "load config" << std::endl;
		srv.loadConfig(pathConfig);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

//	const char* method[] = {"GET", "POST", "DELETE", NULL};
//	std::cout << method[2] << std::endl;

	return (0);
}
