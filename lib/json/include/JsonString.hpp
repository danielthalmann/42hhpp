#ifndef JSONSTRING_HPP
#define JSONSTRING_HPP

#include <JsonValue.hpp>
#include <string>
namespace json
{
		
	class JsonString : public JsonValue
	{

	public:
		JsonString() {};
		virtual ~JsonString() {};

		std::string get();
		void set(std::string);

		JsonString &operator=(std::string);


	private:

		std::string _value;


	};

};

#endif
