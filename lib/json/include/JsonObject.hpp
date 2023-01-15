#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP

#include <string>
#include <map>

namespace json
{
	
	class JsonObject
	{

	public:

		float getFloat(std::string);
		void setFloat(std::string, float);
		int getInt(std::string);
		void setInt(std::string, int);
		std::string getString(std::string);
		void setString(std::string, std::string&);
		JsonValue getValue(std::string);
		void setValue(std::string, JsonValue*);
		JsonArray getArray(std::string);
		void setArray(std::string, JsonArray&);
		JsonObject getObject(std::string);
		void setObject(std::string, JsonObject&);


	private:

		std::map<std::string, JsonValue> _value;

	};

};

#endif
