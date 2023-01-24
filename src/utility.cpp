#include "../include/utility.hpp"

std::vector<std::string> utils::split(std::string str, std::string delimiter) {
	size_t pos = 0;
	std::vector<std::string> vec;

	do {
		pos = str.find(delimiter);
		vec.push_back(str.substr(0, pos));
		str.erase(0, pos + delimiter.length());
	} while (pos != std::string::npos);

	return (vec);
}

//GET /danielthalmann/42hhpp/blob/sandbox/doc/sandbox/srv.cpp HTTP/2
//Host: github.com
//User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:107.0) Gecko/20100101 Firefox/107.0
//Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
//Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3
//Accept-Encoding: gzip, deflate, br
//Connection: keep-alive
//Cookie: _gh_sess=lWGsPzmTJX9%2B0WiIMqxVvmOveNT8a3WEiCTHEH803rJ5sDx7AYNyfCBl0AKyuASCcvKYepvRSLkgLWQfLF27nxcMlmN5bwWjYLWI%2BDh%2BMlfcOPMm7Is444GT027igJVDiubkj4r3IFPhp5xyZQvoA5fOy5ctxLUc43ZomirZwT0bP78282EaDXVlIyi0dUr0KTMP%2FShh0COoCwSuezaRvrBGdfI75FBmiXR4GAmnfiIODHbP78pUpxw%2BXzC7pzvI0lieohwAdxCMbwejdIpYFg%3D%3D--SAaQ8tRLGwObTAk5--aWDIwbYACugp8b%2B2ppvCJQ%3D%3D; _octo=GH1.1.2064806961.1674550506; logged_in=no; preferred_color_mode=dark; tz=Europe%2FZurich
//Upgrade-Insecure-Requests: 1
//Sec-Fetch-Dest: document
//Sec-Fetch-Mode: navigate
//Sec-Fetch-Site: cross-site
//TE: trailers
