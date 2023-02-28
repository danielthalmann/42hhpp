#include "CGI.hpp"
#include <sys/types.h>
#include <sys/wait.h>

namespace hhpp
{
	CGI::CGI()
	{
	}
	CGI::~CGI()
	{
	}

	std::vector<char *> CGI::preparePath(const std::string &query)
	{
		std::vector<char *> path;

		path.push_back(const_cast<char *>(_location.c_str()));
		path.push_back(const_cast<char *>(_scriptPath.c_str()));
		if (!query.empty())
			path.push_back(const_cast<char *>(_query.c_str()));
		path.push_back(NULL);

		return path;
	}

	std::map<std::string, std::string> CGI::prepareEnv(Request request)
	{
		std::map<std::string, std::string> env;


		size_t pos = _scriptPath.rfind("/");
		std::string nameScript = _scriptPath.substr(pos + 1, _scriptPath.size());

		env["AUTH_TYPE"] = "null";
		env["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
		env["CONTENT_LENGTH"] = utils::numberToString(request.getBodySize());

		env["GATEWAY_INTERFACE"] = "CGI/1.1";
		env["PATH_INFO"] = _location;

		env["SERVER_NAME"] = request.getHost();
		env["SERVER_PROTOCOL"] = request.getHttpVersion();
		env["SERVER_PORT"] = utils::numberToString(request.getPort());

		env["REQUEST_METHOD"] = request.getMethod();
		env["SCRIPT_FILENAME"] = _scriptPath;
		env["SCRIPT_NAME"] = nameScript;
		env["QUERY_STRING"] = _query;

		env["REDIRECT_STATUS"] = "CGI";

		if (request.getHeaders()["Cookie"].length() > 0)
		{
			env["HTTP_COOKIE"] = request.getHeaders()["Cookie"];
		}

		return env;
	}

	std::string CGI::execute(std::string scriptPath, Request request)
	{
		int p_out[2];
		int p_in[2];
		int ret;
		char buffer[4096];
		std::string result;

		if (access(_location.c_str(), X_OK))
			throw(std::exception());

		_scriptPath = scriptPath;
		_query = request.getQuery();

		pipe(p_out);
		pipe(p_in);

		fcntl(p_out[0], F_SETFL, O_NONBLOCK);
		fcntl(p_out[1], F_SETFL, O_NONBLOCK);
		fcntl(p_in[0], F_SETFL, O_NONBLOCK);
		fcntl(p_in[1], F_SETFL, O_NONBLOCK);

		std::vector<char *> path = preparePath(request.getQuery());
		std::map<std::string, std::string> env = prepareEnv(request);

		int pid = fork();

		if (pid == 0)
		{
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

			if (waitpid(pid, &ret, 0) == -1)
				throw(std::exception());
			if (ret != 0)
				throw(std::exception());

			std::cout << "cgi:" << ret << std::endl;

			do
			{
				bzero(&buffer, sizeof(buffer));
				ret = read(p_out[0], buffer, sizeof(buffer));
				if (ret > 0)
					result.append(std::string(buffer, ret));
			} while (ret == sizeof(buffer));
			close(p_out[0]);
		}

		return (result);
	}

	void CGI::addExtension(const std::string &extension)
	{
		_extension.push_back(extension);
	}

	void CGI::setLocation(const std::string &location)
	{
		_location = location;
	}

	bool CGI::match(const std::string &query) const
	{
		for (std::vector<std::string>::const_iterator it = _extension.begin(); it != _extension.end(); it++)
		{
			std::string extension = query.substr(query.size() - (*it).size());
			if (extension == (*it))
				return true;
		}
		return false;
	}

} // namespace hhpp
