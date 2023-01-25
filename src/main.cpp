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

	hhpp::Request resquest;
	std::string str("GET / HTTP/1.1\n"
					"Host: www.quicksite.ch\n"
					"User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:107.0) Gecko/20100101 Firefox/107.0\n"
					"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\n"
					"Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3\n"
					"Accept-Encoding: gzip, deflate, br\n"
					"Connection: keep-alive\n"
					"Cookie: lngStatQSSession=1056898499; sharedsession=1056898499; _ga_9L3BXGSELR=GS1.1.1674650650.2.0.1674650650.0.0.0; _ga=GA1.2.1441768351.1674639513; __atuvc=2%7C4; _gid=GA1.2.1508303347.1674639514; __atuvs=63d1241a3e7d3092000; _gat=1\n"
					"Upgrade-Insecure-Requests: 1\n"
					"Sec-Fetch-Dest: document\n"
					"Sec-Fetch-Mode: navigate\n"
					"Sec-Fetch-Site: cross-site");
	resquest.setRequest(str);
//	resquest.showRequest();

	hhpp::Response Response1;
	Response1.setResponse(resquest, 200);
	Response1.showResponse();

	Response1.setTotalStatus(200, "Hello test");

	hhpp::Response Response2;
	Response2.setResponse(resquest, 200);
	Response2.showResponse();

	return (0);
}
