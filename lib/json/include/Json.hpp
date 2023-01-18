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

	public:

		//static JsonValue *parse(const std::string &s, size_t i = 0);

		static JsonValue *parse(const std::string &s, size_t i = 0)
		{
			JsonValue *j = NULL;

			while (i < s.length())
			{
				switch (s[i])
				{
					case '{':
						j = parseObject(s, i);
					break;
					case '[':
						j = parseArray(s, i);
					break;
					case '"':
						j = parseString(s, i);

				}
			}

			return j;
		};

		JsonValue *parseObject(const std::string &s, size_t i = 0)
		{
			(void) s;
			(void) i;

			JsonValue *j = new JsonObject();
			return j;

		};

		JsonValue *parseArray(const std::string &s, size_t i = 0)
		{
			(void) s;
			(void) i;
			return NULL;
		}

		JsonValue *parseString(const std::string &s, size_t i = 0)
		{
			(void) s;
			(void) i;
			return NULL;
		}

	private:


	};

};

#endif
