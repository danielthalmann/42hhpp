#include <JsonBoolean.hpp>

namespace json
{

	JsonBoolean::JsonBoolean()
	{
		_valueType = json_type_boolean;
	}

	JsonBoolean::JsonBoolean(const JsonBoolean &other) : JsonValue()
	{
		*this = other;
	}

	JsonBoolean::~JsonBoolean()
	{
	}

	JsonBoolean &JsonBoolean::operator=(const JsonBoolean &other)
	{
		_value = other._value;
		return *this;
	}

	bool JsonBoolean::getBool()
	{
		return _value;
	}

	void JsonBoolean::set(const bool b)
	{
		_value = b;
	}


	JsonBoolean &JsonBoolean::operator=(const bool &b)
	{
		_value = b;
		return *this;
	}

} // namespace json
