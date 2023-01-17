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

		static JsonValue *parse(std::string s)
		{
			s = "ok";
			JsonObject obj;

			JsonValue *j = new JsonObject();
			JsonObject *jobject = dynamic_cast<JsonObject*>(j);
			jobject->setInt("essai", 5);

			return j;
		};

	private:


	};

};

#endif
