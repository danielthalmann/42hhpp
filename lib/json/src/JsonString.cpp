#include <JsonString.hpp>

namespace json
{
    
	JsonString::JsonString()
    {
        _valueType = json_type_string;
    }

	JsonString::JsonString(const JsonString& other) : JsonValue()
    {
        *this = other;
    }

	JsonString::~JsonString()
    {

    }

    JsonString &JsonString::operator=(const JsonString& other)
    {
        _value = other._value;
        return *this;
    }

    std::string JsonString::getString()
    {
        return _value;
    }

    void JsonString::set(const std::string &s)
    {
        _value = s;
    }


    JsonString &JsonString::operator=(const std::string &s)
    {
        _value = s;
        return *this;
    }

}


