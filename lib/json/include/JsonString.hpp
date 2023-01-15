#ifndef JSONSTRING_HPP
#define JSONSTRING_HPP

#include <JsonValue.hpp>
#include <string>
namespace json
{
		
	class JsonString
	{

	public:

		std::string get();
		void set(std::string);


	private:

		std::string _value;


	};

};

#endif
