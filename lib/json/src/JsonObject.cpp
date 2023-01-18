#include <JsonObject.hpp>

namespace json
{
	JsonObject::JsonObject()
    {
        _valueType = json_type_object;
    }

	JsonObject::JsonObject(const JsonObject& other) : JsonValue()
    {
        *this = other;
    }

	JsonObject::~JsonObject()
    {

    }

    JsonObject &JsonObject::operator=(const JsonObject& other)
    {
        _value = other._value;
        return *this;
    }

	JsonValue *JsonObject::at(const std::string& s)
    {
        (void) s;
        return NULL;
    }

	void JsonObject::put(const std::string key, const int i)
    {
        (void) key;
        (void) i;
    }

	void JsonObject::put(const std::string key, const float f)
    {
        (void) key;
        (void) f;
    }

	void JsonObject::put(const std::string key, const std::string& s)
    {
        (void) key;
        (void) s;
    }

	void JsonObject::put(const std::string key, const JsonValue* v)
    {
        (void) key;
        (void) v;
    }

	void JsonObject::put(const std::string key, const JsonArray* a)
    {
        (void) key;
        (void) a;
    }

	void JsonObject::put(const std::string key, const JsonObject* o)
    {
        (void) key;
        (void) o;
    }
}


