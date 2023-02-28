#ifndef JSON_HPP
#define JSON_HPP

#include <JsonArray.hpp>
#include <JsonBoolean.hpp>
#include <JsonNumber.hpp>
#include <JsonObject.hpp>
#include <JsonString.hpp>

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

} // namespace json

#endif
