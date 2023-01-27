#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP

#include <JsonValue.hpp>
#include <JsonArray.hpp>
#include <string>
#include <map>

namespace json
{
	
	class JsonObject : public JsonValue
	{

	public:

		JsonObject();
		JsonObject(const JsonObject &other);
		virtual ~JsonObject();
		JsonObject &operator=(const JsonObject &other);

		JsonValue *at(const std::string& s);

		virtual bool exists(const std::string& s);
		
		void put(const std::string& key, const int i);
		void put(const std::string& key, const float f);
		void put(const std::string& key, const std::string& s);
		void put(const std::string& key, JsonValue* v);
		void put(const std::string& key, JsonArray* a);
		void put(const std::string& key, JsonObject* o);

	private:

		void clear();

		std::map<std::string, JsonValue*> _value;

	};

}

#endif
