#ifndef JSONNUMBER_HPP
#define JSONNUMBER_HPP

#include <JsonValue.hpp>

namespace json
{

	class JsonNumber : public JsonValue
	{

	public:
		JsonNumber() {};
		virtual ~JsonNumber() {};

		void setInt(int);
		void setFloat(float);
		int getInt();
		float getFloat();


	private:

		int _value;

	};
	
};

#endif
