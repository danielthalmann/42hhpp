#ifndef JSONSTRING_HPP
#define JSONSTRING_HPP

#include <JsonValue.hpp>
#include <string>

namespace json
{
		
	class JsonString : public JsonValue
	{

	public:
		JsonString();
		JsonString(const JsonString& other);
		virtual ~JsonString();
		JsonString &operator=(const JsonString& other);

		virtual std::string getString();
		virtual void set(const std::string &s);

		JsonString &operator=(const std::string &s);

	private:

		std::string _value;


	};

};

#endif
