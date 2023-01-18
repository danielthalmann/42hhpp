#ifndef JSONVALUE_HPP
#define JSONVALUE_HPP

#include <stdexcept>
#include <string>

namespace json
{
	class JsonObject;
	class JsonArray;
	class JsonValue
	{

	public:

		typedef enum JsonType_e
		{
			json_type_null,
			json_type_string,
			json_type_number,
			json_type_object,
			json_type_array,
			json_type_true,
			json_type_false

		} JsonType;


		JsonValue();
		JsonValue(const JsonValue& other);
		virtual ~JsonValue();

		virtual void setInt(const int i);
		virtual void setFloat(const float f);
		virtual void setString(const std::string& s);
		virtual void setValue(const JsonValue& v);
		virtual void setArray(const JsonArray& a);
		virtual void setObject(const JsonObject& o);

		virtual void putInt(const std::string key, const int i);
		virtual void putFloat(const std::string key, const float f);
		virtual void putString(const std::string key, const std::string& s);
		virtual void putValue(const std::string key, const JsonValue* v);
		virtual void putArray(const std::string key, const JsonArray* a);
		virtual void putObject(const std::string key, const JsonObject* o);
		
		virtual void putInt(const int key, const int i);
		virtual void putFloat(const int key, const float f);
		virtual void putString(const int key, const std::string& s);
		virtual void putValue(const int key, const JsonValue& v);
		virtual void putArray(const int key, const JsonArray& a);
		virtual void putObject(const int key, const JsonObject& o);

		virtual int 		getInt();
		virtual float 		getFloat();
		virtual std::string getString();
		virtual JsonValue 	*getValue();
		virtual JsonArray 	*getArray();
		virtual JsonObject 	*getObject();

		virtual JsonValue *at(const std::string& s);
		virtual JsonValue *at(const std::size_t i);
	
		virtual void push(const int value);
		virtual void push(const float value);
		virtual void push(const std::string& value);
		virtual void push(const JsonArray& value);
		virtual void push(const JsonObject& value);

		JsonType 			getValueType();

	protected:
		JsonType _valueType;


	};

};

#endif
