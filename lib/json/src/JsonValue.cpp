#include <JsonValue.hpp>

namespace json
{

	JsonValue::JsonValue()
	{
		_valueType = json_type_null;
	}

	JsonValue::JsonValue(const JsonValue &other)
	{
		_valueType = other._valueType;
	}

	JsonValue::~JsonValue()
	{
	}

	void JsonValue::set(const bool b)
	{
		(void)b;
		throw std::logic_error("Cannot set bool");
	}

	void JsonValue::set(const int i)
	{
		(void)i;
		throw std::logic_error("Cannot set int");
	}

	void JsonValue::set(const float f)
	{
		(void)f;
		throw std::logic_error("Cannot set float");
	}

	void JsonValue::set(const char *c)
	{
		set(std::string(c));
	}

	void JsonValue::set(const std::string &s)
	{
		(void)s;
		throw std::logic_error("Cannot set string");
	}

	void JsonValue::set(const JsonValue &v)
	{
		(void)v;
		throw std::logic_error("Cannot set value");
	}

	void JsonValue::set(const JsonArray &a)
	{
		(void)a;
		throw std::logic_error("Cannot set array");
	}

	void JsonValue::set(const JsonObject &o)
	{
		(void)o;
		throw std::logic_error("Cannot set object");
	}

	bool JsonValue::getBool()
	{
		return false;
	}

	int JsonValue::getInt()
	{
		return 0;
	}

	float JsonValue::getFloat()
	{
		return 0.0f;
	}

	std::string JsonValue::getString()
	{
		return std::string();
	}

	JsonValue *JsonValue::getValue()
	{
		return NULL;
	}

	JsonArray *JsonValue::getArray()
	{
		return NULL;
	}

	JsonObject *JsonValue::getObject()
	{
		return NULL;
	}

	JsonValue *JsonValue::at(const std::string &s)
	{
		(void)s;
		return NULL;
	}

	JsonValue *JsonValue::at(const std::size_t i)
	{
		(void)i;
		return NULL;
	}

	bool JsonValue::exists(const std::string &s)
	{
		(void)s;
		return false;
	}

	void JsonValue::push(const bool value)
	{
		(void)value;
	}


	void JsonValue::push(const int value)
	{
		(void)value;
	}

	void JsonValue::push(const float value)
	{
		(void)value;
	}

	void JsonValue::push(const char *value)
	{
		push(std::string(value));
	}

	void JsonValue::push(const std::string &value)
	{
		(void)value;
	}

	void JsonValue::push(JsonValue *value)
	{
		(void)value;
	}

	void JsonValue::push(const JsonArray &value)
	{
		(void)value;
	}

	void JsonValue::push(const JsonObject &value)
	{
		(void)value;
	}

	JsonValue::JsonType JsonValue::getValueType()
	{
		return _valueType;
	}

	void JsonValue::put(const std::string &key, const bool i)
	{
		(void)key;
		(void)i;
	}

	void JsonValue::put(const std::string &key, const int i)
	{
		(void)key;
		(void)i;
	}

	void JsonValue::put(const std::string &key, const float f)
	{
		(void)key;
		(void)f;
	}

	void JsonValue::put(const std::string &key, const char *c)
	{
		put(key, std::string(c));
	}

	void JsonValue::put(const std::string &key, const std::string &s)
	{
		(void)key;
		(void)s;
	}

	void JsonValue::put(const std::string &key, JsonValue *v)
	{
		(void)key;
		(void)v;
	}

	void JsonValue::put(const std::string &key, JsonArray *a)
	{
		(void)key;
		(void)a;
	}

	void JsonValue::put(const std::string &key, JsonObject *o)
	{
		(void)key;
		(void)o;
	}

	void JsonValue::put(const int key, const bool b)
	{
		(void)key;
		(void)b;
	}

	void JsonValue::put(const int key, const int i)
	{
		(void)key;
		(void)i;
	}

	void JsonValue::put(const int key, const float f)
	{
		(void)key;
		(void)f;
	}

	void JsonValue::put(const int key, const char *c)
	{
		put(key, std::string(c));
	}

	void JsonValue::put(const int key, const std::string &s)
	{
		(void)key;
		(void)s;
	}

	void JsonValue::put(const int key, const JsonValue &v)
	{
		(void)key;
		(void)v;
	}

	void JsonValue::put(const int key, const JsonArray &a)
	{
		(void)key;
		(void)a;
	}

	void JsonValue::put(const int key, const JsonObject &o)
	{
		(void)key;
		(void)o;
	}

	std::size_t JsonValue::length() const
	{
		return 1;
	}

	std::vector<std::string> JsonValue::keys() const
	{
		return std::vector<std::string>();
	}

	bool JsonValue::isNull() const
	{
		if (_valueType == json_type_null)
			return true;
		else
			return false;
	}
} // namespace json