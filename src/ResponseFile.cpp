#include "ResponseFile.hpp"
#include <utility.hpp>
#include <fstream>
#include <sstream>

namespace hhpp {
	ResponseFile::ResponseFile(std::string filename, MimeType* mimetype)
	: Response()
	{
		std::fstream fs;
		std::stringstream buffer;
		std::string content;

		if (mimetype->isBinary()) {
			fs.open(filename.c_str(), std::ios::in);
			getHeaders()["Content-Transfer-Encoding"] = "base64";
		}
		else {
			fs.open(filename.c_str(), std::ios::in);
		}

		if (!fs){
			setStatus(500);
			setBody(getStatusMessage());
			setContentType("text/plain");
		} else {
			buffer << fs.rdbuf();
			// content.append(buffer.str());
			// TODO : voir comment encoder correctement l'image
			if (false) {
//			if (mimetype->isBinary())
//			{
//				setBody(utils::base64Encode(reinterpret_cast<const unsigned char*>(content.c_str()), content.size()));
				setBody(content.c_str());
				std::cout << getBody() << std::endl;
			}
			else
				setBody(buffer.str());
			setContentType(mimetype->getMimeType());
		}
		buffer << fs.rdbuf();
		fs.close();
		
	}

	ResponseFile::~ResponseFile() 
	{

	}

}
