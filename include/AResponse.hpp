#ifndef ARESPONSE_HPP
#define ARESPONSE_HPP

#include <string>
#include "Header.hpp"

namespace hhpp {
	class AResponse
	{

	public:

		AResponse();
		virtual ~AResponse();

		void setStatus(int status);
		std::string getBlob();
		hhpp::Header& headers();


	protected:

		int _status;
		hhpp::Header _header;


	};
}

#endif
