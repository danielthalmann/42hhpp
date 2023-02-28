#ifndef JSONARRAY_HPP
#define JSONARRAY_HPP

#include <JsonBoolean.hpp>
#include <JsonNumber.hpp>
#include <JsonObject.hpp>
#include <JsonString.hpp>
#include <JsonValue.hpp>
#include <string>
#include <vector>

namespace json
{
	class JsonObject;

	class JsonArray : public JsonValue
	{

	public:
		typedef std::vector<JsonValue *> list;

		JsonArray();
		JsonArray(const JsonArray &other);
		virtual ~JsonArray();
		JsonArray &operator=(const JsonArray &other);

		std::size_t length() const;

		virtual JsonValue *at(const std::size_t i);

		void push(const bool value);
		void push(const int value);
		void push(const float value);
		void push(const char *value);
		void push(const std::string &value);
		void push(JsonValue *v);
		void push(const JsonArray &value);
		void push(const JsonObject &value);

		void put(const int key, const bool b);
		void put(const int key, const int i);
		void put(const int key, const float f);
		void put(const int key, const char *c);
		void put(const int key, const std::string &s);
		void put(const int key, const JsonValue &v);
		void put(const int key, const JsonArray &a);
		void put(const int key, const JsonObject &o);

	private:
		void clear();

		std::vector<JsonValue *> _value;
	};

} // namespace json

#endif
