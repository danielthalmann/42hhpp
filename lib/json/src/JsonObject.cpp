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
        return _value.at(s);
    }

	void JsonObject::put(const std::string key, const int i)
    {
        JsonValue *j;
        try {
            j = at(key);
            delete j;
        } catch(std::exception &e) {
            // on ne fait rien
        }
        j = new JsonNumber();
        j->set(i);
        _value[key] = j;
    }

	void JsonObject::put(const std::string key, const float f)
    {
        JsonValue *j;
        try {
            j = at(key);
            delete j;
        } catch(std::exception &e) {
            // on ne fait rien
        }
        j = new JsonNumber();
        j->set(f);
        _value[key] = j;
    }

	void JsonObject::put(const std::string key, const std::string& s)
    {
        JsonValue *j;
        try {
            j = at(key);
            delete j;
        } catch(std::exception &e) {
            // on ne fait rien
        }
        j = new JsonString();
        j->set(s);
        _value[key] = j;
    }

	void JsonObject::put(const std::string key, JsonValue* v)
    {
        try {
            JsonValue *j = at(key);
            delete j;
        } catch(std::exception &e) {
            // on ne fait rien
        }
        _value[key] = v;
    }

	void JsonObject::put(const std::string key, JsonArray* a)
    {
        try {
            JsonValue *j = at(key);
            delete j;
        } catch(std::exception &e) {
            // on ne fait rien
        }
        _value[key] = a;
    }

	void JsonObject::put(const std::string key, JsonObject* o)
    {
        try {
            JsonValue *j = at(key);
            delete j;
        } catch(std::exception &e) {
            // on ne fait rien
        }
        _value[key] = o;
    }
}


