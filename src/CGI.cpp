#include "CGI.hpp"

//TODO check upload into nginx for example (POST AND DELETE)

namespace hhpp {
	CGI::CGI() {}
	CGI::~CGI() {}

	std::string CGI::execute(std::string script, Request request) {
		int p[2];
//		char buffer[4096];
//TODO change to dynamic size
		char buffer[100000];

		pipe(p);
		fcntl(p[0], F_SETFL, O_NONBLOCK);
		fcntl(p[1], F_SETFL, O_NONBLOCK);

//		request.showRequest();
		(void)request;
//		std::cout << "loc:" << _location << std::endl;
//		std::cout << "ext:";
//		for (std::vector<std::string>::iterator it = _extension.begin(); it < _extension.end() ; ++it) {
//			std::cout << *it << std::endl;
//		}
//		std::cout << "script:" << script << std::endl;

		std::vector<char*> path;
		std::string test = _location;
		test = "/Users/tpinto-m/gh/42hhpp/cgi-bin/php-cgi";
		path.push_back(const_cast<char*>(test.c_str()));
		std::string test2 = script;
		test2 = script;
		path.push_back(const_cast<char*>(test2.c_str()));
		std::string test3 = "contentGet=get";
		path.push_back(const_cast<char*>(test3.c_str()));
		path.push_back(NULL);

		size_t pos = script.rfind("/");
		std::string nameScript = script.substr(pos + 1, script.size());

		std::map<std::string, std::string> env;
		if (request.getMethod() != "GET")
		{
//			env["CONTENT_LENGTH"] = "4102";
			env["GATEWAY_INTERFACE"] = "CGI/1.1";
			env["SERVER_PROTOCOL"] = "HTTP/1.1";
			env["SCRIPT_FILENAME"] = script;
			env["SCRIPT_NAME"] = nameScript;
			env["REDIRECT_STATUS"] = "200";
		}

		int pid = fork();

		if (pid == 0) {
			close(p[0]);
			dup2(p[1], STDOUT_FILENO);
//			dup2(pp[0], STDIN_FILENO); // faire l'inverse
			close(p[1]);

			execve(path[0], &path[0], utils::mapStringToArray(env));
//			execve(path[0], &path[0], NULL);
			exit(0);
		} else {
			close(p[1]);

			waitpid(pid, NULL, 0);
			bzero(&buffer, sizeof(buffer));
			read(p[0], buffer, sizeof(buffer));

//			serverResponse.setResponse(clientRequest, 200);
//			serverResponse.setBody(buffer, "text/html");
		}
//		std::cout << "resp:" << std::endl;
//		std::cout << buffer << std::endl;

		return (buffer);
	}

	void CGI::addExtension(const std::string& extension)
	{
		_extension.push_back(extension);
	}

	void CGI::setLocation(const std::string& location)
	{
		_location = location;
	}

	bool CGI::match(const std::string& query) const
	{
		for (std::vector<std::string>::const_iterator it = _extension.begin(); it != _extension.end(); it++) {
			std::string extension = query.substr(query.size() - (*it).size());
			if (extension == (*it))
				return true;
		}
		return false;
	}

}
