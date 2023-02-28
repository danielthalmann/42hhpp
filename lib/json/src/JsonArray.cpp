#include <JsonArray.hpp>
#include <iostream>
#include <stdexcept>

namespace json
{
	JsonArray::JsonArray()
	{
		_valueType = json_type_array;
	}

	JsonArray::JsonArray(const JsonArray &other) : JsonValue()
	{
		*this = other;
	}

	JsonArray::~JsonArray()
	{
		clear();
	}

	JsonArray &JsonArray::operator=(const JsonArray &other)
	{
		clear();
		JsonValue *j;
		JsonBoolean *b;
		JsonNumber *n;
		JsonString *s;
		JsonObject *o;
		JsonArray *a;

		for (std::vector<JsonValue *>::const_iterator it = other._value.begin(); it != other._value.end(); ++it)
		{

			j = NULL;

			switch ((*it)->getValueType())
			{
			case json_type_boolean:
				b = dynamic_cast<JsonBoolean *>(*it);
				j = new JsonBoolean(*b);
				break;

			case json_type_number:
				n = dynamic_cast<JsonNumber *>(*it);
				j = new JsonNumber(*n);
				break;

			case json_type_string:
				s = dynamic_cast<JsonString *>(*it);
				j = new JsonString(*s);
				break;

			case json_type_object:
				o = dynamic_cast<JsonObject *>(*it);
				j = new JsonObject(*o);
				break;

			case json_type_array:
				a = dynamic_cast<JsonArray *>(*it);
				j = new JsonArray(*a);
				break;

			case json_type_null:
			default:
				j = new JsonValue();
				break;
			}
			_value.push_back(j);
		}

		return *this;
	}

	void JsonArray::clear()
	{
		for (std::vector<JsonValue *>::iterator it = this->_value.begin(); it != this->_value.end(); ++it)
		{
			delete (*it);
			*it = 0;
		}
		_value.clear();
	}

	std::size_t JsonArray::length() const
	{
		return _value.size();
	}

	JsonValue *JsonArray::at(const std::size_t idx)
	{
		if (idx >= length())
			throw std::out_of_range("Array out of range");

		return _value[idx];
	}

	void JsonArray::push(const bool value)
	{
		JsonBoolean *j = new JsonBoolean();
		j->set(value);
		_value.push_back(j);
	}

	void JsonArray::push(const int value)
	{
		JsonNumber *j = new JsonNumber();
		j->set(value);
		_value.push_back(j);
	}

	void JsonArray::push(const float value)
	{
		JsonNumber *j = new JsonNumber();
		j->set(value);
		_value.push_back(j);
	}

	void JsonArray::push(const char *value)
	{
		push(std::string(value));
	}

	void JsonArray::push(const std::string &value)
	{
		JsonString *j = new JsonString();
		j->set(value);
		_value.push_back(j);
	}

	void JsonArray::push(const JsonArray &value)
	{
		JsonArray *j = new JsonArray();
		*j = value;
		_value.push_back(j);
	}

	void JsonArray::push(const JsonObject &value)
	{
		JsonObject *j = new JsonObject();
		*j = value;
		_value.push_back(j);
	}

	void JsonArray::push(JsonValue *v)
	{
		_value.push_back(v);
	}

	void JsonArray::put(const int key, const bool b)
	{
		JsonValue *j = at(key);
		delete j;
		j = new JsonBoolean();
		j->set(b);
		_value[key] = j;
	}

	void JsonArray::put(const int key, const int i)
	{
		JsonValue *j = at(key);
		delete j;
		j = new JsonNumber();
		j->set(i);
		_value[key] = j;
	}

	void JsonArray::put(const int key, const float f)
	{
		JsonValue *j = at(key);
		delete j;
		j = new JsonNumber();
		j->set(f);
		_value[key] = j;
	}

	void JsonArray::put(const int key, const char *c)
	{
		put(key, std::string(c));
	}

	void JsonArray::put(const int key, const std::string &s)
	{
		JsonValue *j = at(key);
		delete j;
		j = new JsonString();
		j->set(s);
		_value[key] = j;
	}

	void JsonArray::put(const int key, const JsonValue &v)
	{
		JsonValue *j = at(key);
		delete j;
		j = new JsonValue();
		*j = v;
		_value[key] = j;
	}

	void JsonArray::put(const int key, const JsonArray &a)
	{
		JsonValue *j = at(key);
		delete j;
		j = new JsonArray();
		*j = a;
		_value[key] = j;
	}

	void JsonArray::put(const int key, const JsonObject &o)
	{
		JsonValue *j = at(key);
		delete j;
		j = new JsonArray();
		*j = o;
		_value[key] = j;
	}


} // namespace json
