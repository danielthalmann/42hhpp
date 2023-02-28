#include "HHPP.hpp"
#include "utility.hpp"
#include <Json.hpp>
#include <stdlib.h>

namespace hhpp
{
	HHPP::HHPP()
	{
	}

	HHPP::~HHPP()
	{
		for (std::vector<IServer *>::iterator it = _servers.begin(); it != _servers.end(); ++it)
		{
			delete (*it);
		}
		_servers.clear();

		for (std::vector<IBinding *>::iterator it = _bindings.begin(); it != _bindings.end(); ++it)
		{
			delete (*it);
		}
		_bindings.clear();
	}

	void HHPP::loadConfig(std::string pathConfig)
	{

		std::string jsonString;
		json::JsonValue *jsonEl, *json;

		jsonString = readFileConfig(pathConfig);

		json = json::Json::parse(jsonString);

		for (size_t i = 0; i < json->at("servers")->length(); i++)
		{
			IServer *newServer = new Server();
			IBinding *newBinding = NULL;

			_servers.push_back(newServer);


			//
			// binding
			//
			std::string ip = json->at("servers")->at(i)->at("binding")->at("ip")->getString();
			int port = json->at("servers")->at(i)->at("binding")->at("port")->getInt();

			for (std::vector<IBinding *>::iterator it = _bindings.begin(); it != _bindings.end(); ++it)
			{
				if ((*it)->isBinding(ip, port))
				{
					newBinding = (*it);
					break;
				}
			}

			if (!newBinding)
			{
				newBinding = new Binding();
				_bindings.push_back(newBinding);
				newBinding->setIP(ip);
				newBinding->setPort(port);
				if (newBinding->getPort() < 1024 || newBinding->getPort() > 65535)
					throw Binding::socketStatus();
			}

			newServer->setBinding(newBinding);

			//
			// domain
			//
			if (json->at("servers")->at(i)->exists("domain"))
				jsonEl = json->at("servers")->at(i)->at("domain");
			else
				jsonEl = json->at("domain");

			for (size_t j = 0; j < jsonEl->length(); j++)
			{
				newServer->addDomain(jsonEl->at(j)->getString());
			}

			//
			// index
			//
			if (json->at("servers")->at(i)->exists("index"))
				jsonEl = json->at("servers")->at(i)->at("index");
			else
				jsonEl = json->at("index");

			for (size_t j = 0; j < jsonEl->length(); j++)
			{
				newServer->addIndex(jsonEl->at(j)->getString());
			}

			//
			// root
			//
			if (json->at("servers")->at(i)->exists("root"))
				newServer->setRoot(json->at("servers")->at(i)->at("root")->getString());
			else
				newServer->setRoot(json->at("root")->getString());

			//
			// redirect (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("redirect"))
				jsonEl = json->at("servers")->at(i)->at("redirect");
			else if (json->exists("redirect"))
				jsonEl = json->at("redirect");

			if (jsonEl)
			{
				Redirect *red;
				for (size_t j = 0; j < jsonEl->length(); j++)
				{
					red = new Redirect();
					red->setPath(jsonEl->at(j)->at("path")->getString());
					red->setDestination(jsonEl->at(j)->at("destination")->getString());
					if (jsonEl->at(j)->exists("status"))
					{
						red->setStatus(jsonEl->at(j)->at("status")->getInt());
					}
					newServer->addRedirect(red);
				}
			}

			//
			// error pages (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("error_pages"))
				jsonEl = json->at("servers")->at(i)->at("error_pages");
			else if (json->exists("error_pages"))
				jsonEl = json->at("error_pages");

			if (jsonEl)
			{
				ErrorPage *ep;
				std::vector<std::string> errorCodes = jsonEl->keys();

				for (size_t j = 0; j < errorCodes.size(); j++)
				{

					ep = new ErrorPage();

					ep->setLocation(jsonEl->at(errorCodes[j])->getString());
					ep->setStatus(atoi(errorCodes[j].c_str()));

					newServer->addErrorPage(ep);
				}
			}

			//
			// location (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("location"))
				jsonEl = json->at("servers")->at(i)->at("location");
			else if (json->exists("location"))
				jsonEl = json->at("location");

			if (jsonEl)
			{
				Location *loc;
				for (size_t j = 0; j < jsonEl->length(); j++)
				{
					loc = new Location();
					loc->setPath(jsonEl->at(j)->at("path")->getString());
					loc->setRoot(jsonEl->at(j)->at("root")->getString());
					if (jsonEl->at(j)->exists("allow_update"))
						loc->setAllowUpdate(jsonEl->at(j)->at("allow_update")->getBool());
					newServer->addLocation(loc);
				}
			}


			//
			// auto_index (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("auto_index"))
				jsonEl = json->at("servers")->at(i)->at("auto_index");
			else if (json->exists("auto_index"))
				jsonEl = json->at("auto_index");
			if (jsonEl)
			{
				newServer->setAutoIndex(jsonEl->getBool());
			}

			//
			// access_log (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("access_log"))
				jsonEl = json->at("servers")->at(i)->at("access_log");
			else if (json->exists("access_log"))
				jsonEl = json->at("access_log");
			if (jsonEl)
			{
				newServer->setAccessLog(jsonEl->getString());
			}

			//
			// client_max_body_size (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("client_max_body_size"))
				jsonEl = json->at("servers")->at(i)->at("client_max_body_size");
			else if (json->exists("client_max_body_size"))
				jsonEl = json->at("client_max_body_size");
			if (jsonEl)
			{
				newServer->setClientMaxBodySize(jsonEl->getInt());
			}

			//
			// allowed method
			//
			if (json->at("servers")->at(i)->exists("allowed_methods"))
				jsonEl = json->at("servers")->at(i)->at("allowed_methods");
			else
				jsonEl = json->at("allowed_methods");

			for (size_t j = 0; j < jsonEl->length(); j++)
			{
				newServer->addAllowedMethod(jsonEl->at(j)->getString());
			}

			//
			// cgi (optional)
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("cgi"))
				jsonEl = json->at("servers")->at(i)->at("cgi");
			else if (json->exists("cgi"))
				jsonEl = json->at("cgi");

			if (jsonEl)
			{
				CGI *cgi;
				for (size_t j = 0; j < jsonEl->length(); j++)
				{

					cgi = new CGI();
					cgi->setLocation(jsonEl->at(j)->at("location")->getString());
					for (size_t k = 0; k < jsonEl->at(j)->at("extension")->length(); k++)
					{
						cgi->addExtension(jsonEl->at(j)->at("extension")->at(k)->getString());
					}
					newServer->addCGI(cgi);
				}
			}

			//
			// mimetype
			//
			jsonEl = NULL;
			if (json->at("servers")->at(i)->exists("mime_types"))
				jsonEl = json->at("servers")->at(i)->at("mime_types");
			else
				jsonEl = json->at("mime_types");

			std::vector<std::string> mimes = jsonEl->keys();

			MimeType *mimeType;
			for (size_t j = 0; j < mimes.size(); j++)
			{

				for (size_t k = 0; k < json->at("mime_types")->at(mimes[j])->length(); k++)
				{
					mimeType = new MimeType();
					mimeType->setMimeType(mimes[j]);
					mimeType->setExtension(json->at("mime_types")->at(mimes[j])->at(k)->getString());

					newServer->addMimeType(mimeType);
				}
			}
		}


		delete json;
	}

	IBinding *HHPP::isListen(int socket)
	{
		for (std::vector<IBinding *>::iterator it = _bindings.begin(); it != _bindings.end(); ++it)
		{
			if (socket == (*it)->getSocket())
				return (*it);
		}
		return NULL;
	}

	IBinding *HHPP::getBindingFromSocket(int socket)
	{

		for (std::vector<IBinding *>::iterator it = _bindings.begin(); it != _bindings.end(); ++it)
		{
			if (socket == (*it)->getSocket())
				return (*it);
			if ((*it)->hasConnection(socket))
				return (*it);
		}
		return NULL;
	}

	void HHPP::run()
	{
		int ret;
		fd_set current_set, working_set;
		int max_sd, new_sd;
		int listen_sd;
		int desc_ready, end_server = 0;
		int close_conn;
		int len;
		char buffer[4096];
		IBinding *currentBinding;

		FD_ZERO(&current_set);
		max_sd = _bindings.front()->getSocket();
		for (std::vector<IBinding *>::iterator it = _bindings.begin(); it != _bindings.end(); ++it)
		{
			listen_sd = (*it)->getSocket();
			if (listen_sd > 0)
				FD_SET(listen_sd, &current_set);
			if (max_sd < listen_sd)
				max_sd = listen_sd;
		}

		do
		{
			// copy into working set
			memcpy(&working_set, &current_set, sizeof(current_set));

			// select
			// std::cout << "Waiting on select()..." << std::endl;
			ret = select(max_sd + 1, &working_set, NULL, NULL, NULL);
			if (ret < 0)
			{
				std::cerr << "[-] select() failed" << std::endl;
				break;
			}

			desc_ready = ret;
			for (int i = 0; i <= max_sd && desc_ready > 0; ++i)
			{
				if (FD_ISSET(i, &working_set))
				{
					desc_ready -= 1;
					if ((currentBinding = isListen(i)) != NULL)
					{
						// std::cout << "Listening socket is readable" << std::endl;
						do
						{
							new_sd = currentBinding->acceptConnection();
							if (new_sd < 0)
							{
								if (errno != EWOULDBLOCK)
								{
									std::cerr << "[-] accept() failed" << std::endl;
									end_server = 1;
								}
								break;
							}
							// std::cout << "New incoming connection - " << new_sd << std::endl;
							FD_SET(new_sd, &current_set);
							if (new_sd > max_sd)
								max_sd = new_sd;

						} while (new_sd != -1);
					}
					else
					{
						// std::cout << "Descriptor " << i << " is readable" << std::endl;
						close_conn = 0;

						currentBinding = getBindingFromSocket(i);

						while (1)
						{
							bzero(buffer, sizeof(buffer));
							ret = recv(i, buffer, sizeof(buffer), 0);
							if (ret < 0)
							{
								if (errno != EWOULDBLOCK)
								{
									// std::cout << "recv() finish" << std::endl;
									close_conn = 1;
								}
								break;
							}
							if (ret == 0)
							{
								// std::cout << "Connection closed" << std::endl;
								close_conn = 1;
								break;
							}
							len = ret;
							std::cout << len << " bytes received" << std::endl;

							// prepare request
							Request *request = new Request();
							request->parseRequest(std::string(buffer, ret));

							IServer *server = NULL;
							server = currentBinding->getServerFor(*request);

							// take first server if not exists
							if (!server)
							{
								server = _servers[0];
							}

							Response *response = server->treatRequest(*request);
							response->setServer(server);

							std::string dataSend;
							try
							{
								dataSend = response->raw();
							}
							catch (std::exception &e)
							{
								delete response;
								response = new ResponseError(502);
								response->setServer(server);
								dataSend = response->raw();
							}

							ret = send(i, dataSend.c_str(), dataSend.size(), 0);
							std::cout << "[+] data send: " << ret << "/" << dataSend.size() << std::endl;
							if (ret < 0)
							{
								std::cerr << "[-] send() failed" << std::endl;
							}

							// free memory
							delete response;
							delete request;

							close_conn = 1;
							break;
						}

						if (close_conn)
						{
							std::cout << "close fd: " << i << std::endl;
							currentBinding->closeConnection(i);
							FD_CLR(i, &current_set);
							if (i == max_sd)
							{
								while (FD_ISSET(max_sd, &current_set) == 0)
									max_sd -= 1;
							}
						}
					}
				}
			}

		} while (end_server == 0);
	}

	std::string HHPP::readFileConfig(std::string pathConfig)
	{
		std::string file;
		char c;
		struct stat fileInfo;
		std::ifstream ifs(pathConfig.c_str());

		if (stat(pathConfig.c_str(), &fileInfo) != 0)
			throw(HHPP::fileStatus());

		if ((fileInfo.st_mode & S_IFMT) == S_IFDIR)
			throw(HHPP::fileStatus());


		if (!ifs.good() || pathConfig.empty())
			throw(HHPP::fileStatus());

		if (ifs.is_open())
		{

			c = ifs.get();

			do
			{
				file += c;
				c = ifs.get();
			} while (!ifs.eof());

			ifs.close();
		}
		else
		{
			throw(HHPP::fileStatus());
		}
		return (file);
	}

	void HHPP::setupSocket()
	{
		for (std::vector<IBinding *>::iterator it = _bindings.begin(); it != _bindings.end(); ++it)
		{
			(*it)->setSocket();
		}
		//		IBinding *newSocket = _bindings.front();
		//		newSocket->setSocket();
	}

	void HHPP::dispatchRequest(hhpp::Request request)
	{
		(void)request;
	}

	const char *HHPP::fileStatus::what() const throw()
	{
		return ("File Error");
	}

} // namespace hhpp
