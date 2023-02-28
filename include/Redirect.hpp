#ifndef REDIRECT_HPP
#define REDIRECT_HPP

#include <string>
namespace hhpp
{
	class Redirect
	{
	public:
		Redirect();
		~Redirect();

		void setPath(const std::string &path);
		void setDestination(const std::string &destination);
		void setStatus(int status);
		bool match(const std::string &query) const;
		std::string getDestination() const;
		int getStatus() const;

	private:
		std::string _path;
		std::string _destination;
		int _status;
	};
} // namespace hhpp

#endif
