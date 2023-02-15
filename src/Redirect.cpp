#include "Redirect.hpp"

namespace hhpp {

	Redirect::Redirect() 
	: _path(""), _destination(""), _status(301)
	{

	}

	Redirect::~Redirect() {}

	void Redirect::setPath(const std::string& path)
	{
		_path = path;
	}

	void Redirect::setDestination(const std::string& destination)
	{
		_destination = destination;
	}

	void Redirect::setStatus(int status)
	{
		_status = status;
	}

	std::string Redirect::getDestination() const
	{
		return _destination;
	}

	int Redirect::getStatus() const
	{
		return _status;
	}

	bool Redirect::match(const std::string& query) const
	{
		if (_path == query)
			return true;
		return false;
	}

}
