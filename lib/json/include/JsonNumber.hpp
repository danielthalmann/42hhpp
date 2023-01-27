#ifndef JSONNUMBER_HPP
#define JSONNUMBER_HPP

#include <JsonValue.hpp>

namespace json
{

	class JsonNumber : public JsonValue
	{

	public:
		JsonNumber();
		JsonNumber(const JsonNumber &other);
		virtual ~JsonNumber();
		JsonNumber &operator=(const JsonNumber &other);

		virtual void set(const int i);
		virtual void set(const float f);
		virtual float get();

		int getInt();
		float getFloat();

		JsonNumber &operator=(const int &i);
		JsonNumber &operator=(const float &i);

	private:

		float _value;

	};
	
}

#endif
