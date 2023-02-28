#include <JsonNumber.hpp>

namespace json
{
	JsonNumber::JsonNumber()
	{
		_valueType = json_type_number;
	}

	JsonNumber::JsonNumber(const JsonNumber &other) : JsonValue()
	{
		*this = other;
	}

	JsonNumber::~JsonNumber()
	{
	}

	JsonNumber &JsonNumber::operator=(const JsonNumber &other)
	{
		_value = other._value;
		return *this;
	}

	float JsonNumber::get()
	{
		return _value;
	}

	int JsonNumber::getInt()
	{
		return static_cast<int>(_value);
	}

	float JsonNumber::getFloat()
	{
		return _value;
	}

	void JsonNumber::set(const int i)
	{
		_value = i;
	}

	void JsonNumber::set(const float f)
	{
		_value = f;
	}

	JsonNumber &JsonNumber::operator=(const int &f)
	{
		_value = f;
		return *this;
	}

	JsonNumber &JsonNumber::operator=(const float &f)
	{
		_value = f;
		return *this;
	}

} // namespace json
