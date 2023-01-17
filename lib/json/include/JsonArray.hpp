#ifndef JSONARRAY_HPP
#define JSONARRAY_HPP

#include <JsonObject.hpp>
#include <JsonValue.hpp>
#include <string>
#include <vector>

namespace json
{
	class JsonObject;

	class JsonArray : public JsonValue
	{

	public:
		JsonArray() {};
		virtual ~JsonArray() {};

		int getLenght();
		float getFloat(int);
		int getInt(int);
		std::string getString(int);
		JsonValue getValue(int);
		JsonArray getArray(int);
		JsonObject getObject(int);
		void pushString(std::string&);
		void pushArray(JsonArray&);
		void pushObject(JsonObject&);
		void pushInt(int);
		void pushFloat(float);


	private:

		std::vector<JsonValue> _value;

	};

};

#endif
