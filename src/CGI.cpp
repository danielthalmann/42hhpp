#include "CGI.hpp"

//TODO check upload into nginx for example (POST AND DELETE)

namespace hhpp {
	CGI::CGI() {}
	CGI::~CGI() {}

	std::string CGI::execute(std::string script, Request request) {
		int p_out[2];
		int p_in[2];
//		char buffer[4096];
//TODO change to dynamic size
		char buffer[100000];

		pipe(p_out);
		pipe(p_in);

		fcntl(p_out[0], F_SETFL, O_NONBLOCK);
		fcntl(p_out[1], F_SETFL, O_NONBLOCK);
		fcntl(p_in[0], F_SETFL, O_NONBLOCK);
		fcntl(p_in[1], F_SETFL, O_NONBLOCK);

		std::vector<char*> path;
		path.push_back(const_cast<char*>(_location.c_str()));
		path.push_back(const_cast<char*>(script.c_str()));
		if (!request.getQuery().empty())
			path.push_back(const_cast<char*>(request.getQuery().c_str()));
		path.push_back(NULL);

		std::map<std::string, std::string> env;
		if (request.getMethod() == "POST")
		{
			size_t pos = script.rfind("/");
			std::string nameScript = script.substr(pos + 1, script.size());

			env["AUTH_TYPE"] = "null";
			env["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
			env["CONTENT_LENGTH"] = utils::numberToString(request.getBodySize());

			env["GATEWAY_INTERFACE"] = "CGI/1.1";
			env["PATH_INFO"] = _location;

			env["SERVER_NAME"] = request.getHost();
			env["SERVER_PROTOCOL"] = request.getHttpVersion();
			env["SERVER_PORT"] = utils::numberToString(request.getPort());

			env["REQUEST_METHOD"] = "POST";
			env["SCRIPT_FILENAME"] = script;
			env["SCRIPT_NAME"] = nameScript;

			env["REDIRECT_STATUS"] = "CGI";
		}
		if (request.getHeaders()["Cookie"].length() > 0) {
			env["HTTP_COOKIE"] = request.getHeaders()["Cookie"];
		}

		int pid = fork();

		if (pid == 0) {
			close(p_out[0]);
			dup2(p_out[1], STDOUT_FILENO);
			close(p_out[1]);

			close(p_in[1]);
			dup2(p_in[0], STDIN_FILENO);
			close(p_in[0]);

			execve(path[0], &path[0], utils::mapStringToArray(env));
			exit(0);
		}
		else
		{
			close(p_in[0]);
			close(p_out[1]);

			write(p_in[1], request.getBody().c_str(), request.getBody().size());
			close(p_in[1]);

			waitpid(pid, NULL, 0);
			bzero(&buffer, sizeof(buffer));
			read(p_out[0], buffer, sizeof(buffer));
			close(p_out[0]);
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
