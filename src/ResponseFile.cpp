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
