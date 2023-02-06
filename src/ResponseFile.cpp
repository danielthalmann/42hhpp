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

			fs.open(filename.c_str(), std::ios_base::binary);
			buffer << fs.rdbuf();

			setBody(utils::base64Encode(buffer.str()));
		}
		else {
			fs.open(filename.c_str(), std::ios_base::in);
			buffer << fs.rdbuf();

			setBody(buffer.str());
		}
		setContentType(mimetype->getMimeType());

		fs.close();
	}

	ResponseFile::~ResponseFile() 
	{

	}

}
