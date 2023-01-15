#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP

namespace json
{
	
	class JsonObject
	{

	public:

		float getFloat(string);
		void setFloat(string, float);
		int getInt(string);
		void setInt(string, int);
		String getString(string);
		void setString(string, string&);
		JsonValue getValue(string);
		void setValue(string, JsonValue*);
		JsonArray getArray(string);
		void setArray(string, JsonArray&);
		JsonObject getObject(string);
		void setObject(string, JsonObject&);


	private:

		map<string, JsonValue> _value;


	};

};

#endif
