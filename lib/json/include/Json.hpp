#ifndef JSON_HPP
#define JSON_HPP

#include <JsonObject.hpp>
#include <JsonArray.hpp>
#include <JsonNumber.hpp>
#include <JsonString.hpp>
#include <JsonBoolean.hpp>

#include <string>

namespace json
{

	class Json
	{
		
	private:
		Json(const std::string &s);

		
	public:
		virtual ~Json();

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
		JsonValue *parseBoolean();
		JsonValue *parseNull();

		bool isWhitespace();
		bool isNumber();
		bool isDigit();
		bool isBoolean();
		bool isNull();
		bool isEndOfString();
		bool isEndOfAccolade();

		void invalidCharacter();
		
	private:
		std::string _s;
		size_t _pos;

	};

}

#endif
