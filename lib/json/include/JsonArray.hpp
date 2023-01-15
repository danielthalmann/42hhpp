#ifndef JSONARRAY_HPP
#define JSONARRAY_HPP

#include <string>
#include <vector>

namespace json
{

	class JsonArray
	{

	public:

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

		vector<JsonValue> _value;


	};

};

#endif
