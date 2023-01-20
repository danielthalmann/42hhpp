#ifndef JSONARRAY_HPP
#define JSONARRAY_HPP

#include <JsonObject.hpp>
#include <JsonValue.hpp>
#include <JsonNumber.hpp>
#include <JsonString.hpp>
#include <string>
#include <vector>

namespace json
{
	class JsonObject;

	class JsonArray : public JsonValue
	{

	public:
		JsonArray();
		JsonArray(const JsonArray &other);
		virtual ~JsonArray();
		JsonArray &operator=(const JsonArray &other);

		std::size_t length() const;

		virtual JsonValue *at(const std::size_t i);

		void push(const int value);
		void push(const float value);
		void push(const std::string& value);
		void push(const JsonArray& value);
		void push(const JsonObject& value);

		void put(const int key, const int i);
		void put(const int key, const float f);
		void put(const int key, const std::string& s);
		void put(const int key, const JsonValue& v);
		void put(const int key, const JsonArray& a);
		void put(const int key, const JsonObject& o);

	private:

		void checkRange();
		std::vector<JsonValue*> _value;

	};

};

#endif
