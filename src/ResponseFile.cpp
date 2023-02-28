#include "ResponseFile.hpp"
#include <utility.hpp>
#include <fstream>
#include <sstream>
#include <Base64.hpp>

namespace hhpp {
	ResponseFile::ResponseFile(std::string filename, MimeType* mimetype)
	: Response()
	{
		std::fstream fs;
		std::stringstream buffer;
		std::string content;

		fs.open(filename.c_str(), std::ios::in);

		if (!fs){
			setStatus(500);
			setBody(getStatusMessage());
			setContentType("text/plain");
		} else {
			
			buffer << fs.rdbuf();
			if (mimetype->isBinary()) {
				getHeaders()["Content-Transfer-Encoding"] = "base64";
				getHeaders()["Content-Encoding"] = "base64";
				setBody(Base64::Encode(buffer.str()));
			}
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
