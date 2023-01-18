#include <JsonString.hpp>

namespace json
{
	JsonString::JsonString() : Json_Value::_valueType(json_type_string)
    {

    }

	JsonString::~JsonString()
    {

    }

    std::string JsonString::get()
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


