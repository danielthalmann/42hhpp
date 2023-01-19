#ifndef JSON_HPP
#define JSON_HPP

#include <JsonObject.hpp>
#include <JsonArray.hpp>
#include <JsonNumber.hpp>
#include <JsonString.hpp>

#include <string>

namespace json
{

	class Json
	{
		
	private:
		Json(const std::string &s);

		
	public:
		~Json();

		static JsonValue *parse(const std::string &s)
		{
			Json j(s);
			return j.parseValue();
		};

	private:
		JsonValue *parseValue();

		JsonValue *parseObject();
		JsonValue *parseArray();
		JsonValue *parseString();
		JsonValue *parseNumber();

	private:
		std::string _s;
		size_t _pos;

	};

};

#endif
