#ifndef REDIRECT_HPP
#define REDIRECT_HPP

#include <string>
namespace hhpp {
	class Redirect
	{
	public:
		Redirect(std::string& path, std::string& destination, int status);
		~Redirect();

	private:
		std::string _path;
		std::string _destination;
		int _status;

	};
}

#endif
