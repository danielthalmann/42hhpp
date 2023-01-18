#include <JsonValue.hpp>

namespace json
{
    
	JsonValue::JsonValue()
    {
        _valueType = json_type_null;
    }

	JsonValue::JsonValue(const JsonValue& other)
    {
        _valueType = other._valueType;
    }

	JsonValue::~JsonValue()
    {

    }

	void JsonValue::setInt(const int i)
    {
        (void) i;
        throw std::domain_error("Cannot set int");
    }

	void JsonValue::setFloat(const float f)
    {
        (void) f;
        throw std::domain_error("Cannot set float");
    }

	void JsonValue::setString(const std::string& s)
    {
        (void) s;
        throw std::domain_error("Cannot set string");
    }

	void JsonValue::setValue(const JsonValue& v)
    {
        (void) v;
        throw std::domain_error("Cannot set value");
    }

	void JsonValue::setArray(const JsonArray& a)
    {
        (void) a;
        throw std::domain_error("Cannot set array");
    }

	void JsonValue::setObject(const JsonObject& o)
    {
        (void) o;
        throw std::domain_error("Cannot set object");
    }

    int 		JsonValue::getInt()
    {
        return 0;
    }

    float 		JsonValue::getFloat()
    {
        return 0;
    }

    std::string JsonValue::getString()
    {
        return std::string();
    }

    JsonValue 	*JsonValue::getValue()
    {
        return NULL;
    }

    JsonArray 	*JsonValue::getArray()
    {
        return NULL;
    }

    JsonObject 	*JsonValue::getObject()
    {
        return NULL;
    }

	JsonValue *JsonValue::at(const std::string& s)
    {
        (void) s;
        return NULL;
    }

	JsonValue *JsonValue::at(const std::size_t i)
    {
        (void) i;
        return NULL;
    }

    void JsonValue::push(const int value)
    {
        (void) value;
    }

    void JsonValue::push(const float value)
    {
        (void) value;
    }

    void JsonValue::push(const std::string& value)
    {
        (void) value;
    }

    void JsonValue::push(const JsonArray& value)
    {
        (void) value;
    }

    void JsonValue::push(const JsonObject& value)
    {
        (void) value;
    }

    JsonValue::JsonType JsonValue::getValueType()
    {
        return _valueType;
    }

	void JsonValue::putInt(const std::string key, const int i)
    {
        (void) key;
        (void) i;
    }

	void JsonValue::putFloat(const std::string key, const float f)
    {
        (void) key;
        (void) f;
    }

	void JsonValue::putString(const std::string key, const std::string& s)
    {
        (void) key;
        (void) s;
    }

	void JsonValue::putValue(const std::string key, const JsonValue* v)
    {
        (void) key;
        (void) v;
    }

	void JsonValue::putArray(const std::string key, const JsonArray* a)
    {
        (void) key;
        (void) a;
    }

	void JsonValue::putObject(const std::string key, const JsonObject* o)
    {
        (void) key;
        (void) o;
    }

	void JsonValue::putInt(const int key, const int i)
    {
        (void) key;
        (void) i;
    }

	void JsonValue::putFloat(const int key, const float f)
    {
        (void) key;
        (void) f;
    }

	void JsonValue::putString(const int key, const std::string& s)
    {
        (void) key;
        (void) s;
    }

	void JsonValue::putValue(const int key, const JsonValue& v)
    {
        (void) key;
        (void) v;
    }

	void JsonValue::putArray(const int key, const JsonArray& a)
    {
        (void) key;
        (void) a;
    }

	void JsonValue::putObject(const int key, const JsonObject& o)
    {
        (void) key;
        (void) o;
    }


}