#include "CGI.hpp"

namespace hhpp {
	CGI::CGI() {}
	CGI::~CGI() {}

	std::string CGI::execute(Request request) {
		int p[2];
		char buffer[4096];

		pipe(p);
		fcntl(p[0], F_SETFL, O_NONBLOCK);
		fcntl(p[1], F_SETFL, O_NONBLOCK);

//		request.showRequest();

//		std::cout << "exception" << std::endl;
//		std::cout << "query:" << request.getUrl() << std::endl;

// TODO
//		if (!match(request.getUrl()))
//			return 501 ?

		std::vector<char*> path;
		std::string test = "/usr/bin/python3";
		path.push_back(const_cast<char*>(test.c_str()));
		std::string test2 = "/Users/tpinto-m/gh/42hhpp/var/www/hello_get.py";
		path.push_back(const_cast<char*>(test2.c_str()));
		std::string test3 = "first_name=Tiago&last_name=PM";
		path.push_back(const_cast<char*>(test3.c_str()));
		path.push_back(NULL);
//
		std::map<std::string, std::string> env;
		env["CONTENT_LENGTH"] = "154";
		env["GATEWAY_INTERFACE"] = "CGI/1.1";
		env["SERVER_PROTOCOL"] = "HTTP/1.1";
		env["SCRIPT_FILENAME"] = "/Users/tpinto-m/gh/42hhpp/var/www/hello_get.py";
		env["SCRIPT_NAME"] = "hello_get.py";
		env["REDIRECT_STATUS"] = "200";

//		TODO resquest to path
		(void)request;

		int pid = fork();

		if (pid == 0) {
			close(p[0]);
			dup2(p[1], STDOUT_FILENO);
//			dup2(pp[0], STDIN_FILENO); // faire l'inverse
			close(p[1]);

			execve(path[0], &path[0], utils::mapStringToArray(env));
			exit(0);
		} else {
			close(p[1]);

			waitpid(pid, NULL, 0);
			bzero(&buffer, sizeof(buffer));
			read(p[0], buffer, sizeof(buffer));

//			serverResponse.setResponse(clientRequest, 200);
//			serverResponse.setBody(buffer, "text/html");
		}
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
