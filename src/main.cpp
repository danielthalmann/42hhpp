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

	hhpp::Request resquest;
	std::string str("GET /danielthalmann/42hhpp/blob/sandbox/doc/sandbox/srv.cpp HTTP/2\n"
					"Host: github.com\n"
					"User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:107.0) Gecko/20100101 Firefox/107.0\n"
					"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\n"
					"Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3\n"
					"Accept-Encoding: gzip, deflate, br\n"
					"Connection: keep-alive\n"
					"Cookie: _gh_sess=lWGsPzmTJX9%2B0WiIMqxVvmOveNT8a3WEiCTHEH803rJ5sDx7AYNyfCBl0AKyuASCcvKYepvRSLkgLWQfLF27nxcMlmN5bwWjYLWI%2BDh%2BMlfcOPMm7Is444GT027igJVDiubkj4r3IFPhp5xyZQvoA5fOy5ctxLUc43ZomirZwT0bP78282EaDXVlIyi0dUr0KTMP%2FShh0COoCwSuezaRvrBGdfI75FBmiXR4GAmnfiIODHbP78pUpxw%2BXzC7pzvI0lieohwAdxCMbwejdIpYFg%3D%3D--SAaQ8tRLGwObTAk5--aWDIwbYACugp8b%2B2ppvCJQ%3D%3D; _octo=GH1.1.2064806961.1674550506; logged_in=no; preferred_color_mode=dark; tz=Europe%2FZurich\n"
					"Upgrade-Insecure-Requests: 1\n"
					"Sec-Fetch-Dest: document\n"
					"Sec-Fetch-Mode: navigate\n"
					"Sec-Fetch-Site: cross-site\n"
					"TE: trailers");
//	srv._bindings.read
	resquest.parseRequest(str);
	resquest.showRequest();
	std::cout << resquest.getHttpVersion() << std::endl;

	return (0);
}
