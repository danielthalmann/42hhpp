#include "ResponsePost.hpp"
#include "utility.hpp"

namespace hhpp
{

	ResponsePost::ResponsePost(Location *location, Request *request) : Response(), _location(location)
	{
		std::string headerRaw;
		std::string name;
		std::string filename;
		std::string composedBody;
		std::vector<std::string> header;

		std::string body;
		size_t pos;
		size_t endPos;

		if (request->isMultipart())
		{
			std::vector<std::string> parts = utils::split(request->getBody(), "--" + request->getBoundary());

			for (size_t i = 0; i < parts.size(); i++)
			{
				pos = parts[i].find("\r\n\r\n");
				if (pos != std::string::npos)
				{
					headerRaw = parts[i].substr(0, pos);
					body = parts[i].substr(pos + 4, parts[i].size() - 6 - pos);
					header = utils::split(headerRaw, "\r\n");
					
					for (size_t i = 0; i < header.size(); i++)
					{
						pos = header[i].find(": ");
						if (pos != std::string::npos)
						{
							if (header[i].substr(0, pos) == "Content-Disposition")
							{
								pos += 2;

								endPos = header[i].find("; ", pos);
								if (endPos != std::string::npos)
								{
									if (header[i].substr(pos, endPos - pos) == "form-data")
									{
										pos = endPos + 2;

										endPos = header[i].find("=", pos);
										if (endPos != std::string::npos)
										{
											if (header[i].substr(pos, endPos - pos) == "name")
											{
												pos = endPos + 2;

												endPos = header[i].find("; ", pos);
												if (endPos != std::string::npos)
												{
													name = header[i].substr(pos, endPos - pos - 1);
													// std::cout << name << "\n";

													pos = endPos + 2;

													// std::cout << header[i].substr(pos) << "\n";

													endPos = header[i].find("=", pos);
													if (endPos != std::string::npos)
													{
														if (header[i].substr(pos, endPos - pos) == "filename")
														{
															pos = endPos + 2;

															filename = header[i].substr(pos, header[i].size() - pos - 1);

															// std::cout << filename << "\n";
															location->put(body, utils::path(_location->getDirectory(), filename));
															
														}
													}

												} 
												else 
												{
													name = header[i].substr(pos, header[i].size() - pos - 1);
													// std::cout << name << "\n";

													composedBody.append(name);
													composedBody.append("=");
													composedBody.append(body);
													composedBody.append("\r\n");

												}

											}
										}
									}
								}
							}
						}
					}

				}
			}
			
			// std::cout << _location->getDirectory() << "\n";
			// std::cout << _location->getFilename() << "\n";
			
			location->put(composedBody);

			//const std::string head = request->getHeaders().raw();
			//location->put(head + request->getBody());
		}
		else
		{
			location->put(request->getBody());
		}

	}

	ResponsePost::~ResponsePost()
	{
	}

} // namespace hhpp
