#include <JsonArray.hpp>
#include <stdexcept>

namespace json
{
	JsonArray::JsonArray()
    {
        _valueType = json_type_array;
    }

	JsonArray::JsonArray(const JsonArray& other)
    {
        *this = other;
    }

	JsonArray::~JsonArray()
    {

    }

    JsonArray &JsonArray::operator=(const JsonArray& other)
    {
        _value = other._value;
        return *this;
    }

    std::size_t JsonArray::length()
    {
        return _value.size();
    }

    JsonValue *JsonArray::at(const std::size_t idx)
    {
        if (idx >= length())
            throw std::out_of_range("Array out of range");

        return _value[idx];
    }

    void JsonArray::push(const int value)
    {
        JsonNumber *j = new JsonNumber();
        j->setInt(value);
        _value.push_back(j);
    }

    void JsonArray::push(const float value)
    {
        JsonNumber *j = new JsonNumber();
        j->setFloat(value);
        _value.push_back(j);
    }

    void JsonArray::push(const std::string& value)
    {
        JsonString *j = new JsonString();
        j->setString(value);
        _value.push_back(j);
    }

    void JsonArray::push(const JsonArray& value)
    {
        JsonArray *j = new JsonArray();
        *j = value;
        _value.push_back(j);
    }

    void JsonArray::push(const JsonObject& value)
    {
        JsonObject *j = new JsonObject();
        *j = value;
        _value.push_back(j);
    }

    void JsonArray::putInt(const int key, const int i)
    {
        JsonValue *j = at(key);
        delete j;
        j = new JsonNumber();
        j->setInt(i);
        _value[key] = j;
    }

    void JsonArray::putFloat(const int key, const float f)
    {
        JsonValue *j = at(key);
        delete j;
        j = new JsonNumber();
        j->setFloat(f);
        _value[key] = j;
    }

    void JsonArray::putString(const int key, const std::string& s)
    {
        JsonValue *j = at(key);
        delete j;
        j = new JsonString();
        j->setString(s);
        _value[key] = j;
    }

    void JsonArray::putValue(const int key, const JsonValue& v)
    {
        JsonValue *j = at(key);
        delete j;
        j = new JsonValue();
        *j = v;
        _value[key] = j;
    }

    void JsonArray::putArray(const int key, const JsonArray& a)
    {
        JsonValue *j = at(key);
        delete j;
        j = new JsonArray();
        *j = a;
        _value[key] = j;
    }

    void JsonArray::putObject(const int key, const JsonObject& o)
    {
        JsonValue *j = at(key);
        delete j;
        j = new JsonArray();
        *j = o;
        _value[key] = j;
    }



}


