#include "ResponseError.hpp"
#include "utility.hpp"

namespace hhpp {
	ResponseError::ResponseError(int error) 
	: Response()
	{
		setStatus(error);

		std::string page;
		std::string errorMsg = "Error " + utils::numberToString(error) + ": " + _totalStatus[error];

		page.append("<html><head>"
					"<title>" + errorMsg + "</title>"
					"<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
					"</head><body>"
					"<h1>" + errorMsg + "</h1>"
					"<p>Oops! Something went wrong...</p>"
					"<p>We seem to be having some technical difficulties. Hang tight.</p>"
					"</body></html>");

		setBody(page);
		setContentType("text/html");
	}

	ResponseError::~ResponseError() {}

	void ResponseError::filename(std::string filename) {
		(void)filename;
	}

	void ResponseError::prepareResponse() {
		std::cout << "ResponseError prepareResponse" << std::endl;
//		_server->

//		for (size_t k = 0; k < _server->getErrorPages().size(); ++k) {
//			if (_server->getErrorPages()[k]->getStatus() == _status)
//			{
//				setContentType("text/html");
//				setBody(_server->getErrorPages()[k]->getPage());
//				break;
//			}
//		}
	}

}
