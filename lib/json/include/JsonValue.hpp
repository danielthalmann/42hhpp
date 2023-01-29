#ifndef JSONVALUE_HPP
#define JSONVALUE_HPP

#include <stdexcept>
#include <string>
#include <vector>

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
			json_type_boolean

		} JsonType;


		JsonValue();
		JsonValue(const JsonValue& other);
		virtual ~JsonValue();

		virtual void set(const bool b);
		virtual void set(const int i);
		virtual void set(const float f);
		virtual void set(const char* c);
		virtual void set(const std::string& s);
		virtual void set(const JsonValue& v);
		virtual void set(const JsonArray& a);
		virtual void set(const JsonObject& o);

		virtual void put(const std::string& key, const bool b);
		virtual void put(const std::string& key, const int i);
		virtual void put(const std::string& key, const float f);
		virtual void put(const std::string& key, const char* c);
		virtual void put(const std::string& key, const std::string& s);
		virtual void put(const std::string& key, JsonValue* v);
		virtual void put(const std::string& key, JsonArray* a);
		virtual void put(const std::string& key, JsonObject* o);
		
		virtual void put(const int key, const bool b);
		virtual void put(const int key, const int i);
		virtual void put(const int key, const float f);
		virtual void put(const int key, const char* c);
		virtual void put(const int key, const std::string& s);
		virtual void put(const int key, const JsonValue& v);
		virtual void put(const int key, const JsonArray& a);
		virtual void put(const int key, const JsonObject& o);

		virtual bool 		getBool();
		virtual int 		getInt();
		virtual float 		getFloat();
		virtual std::string getString();
		virtual JsonValue 	*getValue();
		virtual JsonArray 	*getArray();
		virtual JsonObject 	*getObject();

		virtual JsonValue *at(const std::string& s);
		virtual JsonValue *at(const std::size_t i);
		
		virtual bool exists(const std::string& s);
	
		virtual void push(const bool value);
		virtual void push(const int value);
		virtual void push(const float value);
		virtual void push(const char* value);
		virtual void push(const std::string& value);
		virtual void push(JsonValue* v);
		virtual void push(const JsonArray& value);
		virtual void push(const JsonObject& value);

		JsonType getValueType();

	    virtual std::size_t length() const;
		virtual std::vector<std::string> keys() const;

		bool isNull() const;
		

		//JsonValue &operator[]()
    
	protected:
		JsonType _valueType;

	};

}

#endif
