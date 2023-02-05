#include "ResponseFile.hpp"
#include <fstream>
#include <sstream>

namespace hhpp {
	ResponseFile::ResponseFile(std::string filename, std::string mimetype) 
	: Response()
	{
		std::fstream fs;
		std::stringstream buffer;

		fs.open(filename.c_str(), std::ios_base::in);
		buffer << fs.rdbuf();

		setBody(buffer.str());
		setContentType(mimetype);

		fs.close();
	}

	ResponseFile::~ResponseFile() 
	{

	}

}
