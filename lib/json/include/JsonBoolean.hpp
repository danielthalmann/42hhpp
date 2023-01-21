#ifndef JSONSTRING_HPP
#define JSONSTRING_HPP

#include <JsonValue.hpp>
#include <string>

namespace json
{
		
	class JsonBoolean : public JsonValue
	{

	public:
		JsonBoolean();
		JsonBoolean(const JsonBoolean& other);
		virtual ~JsonBoolean();
		JsonBoolean &operator=(const JsonBoolean& other);

		virtual std::string getString();
		virtual bool getBool();
		virtual void set(const bool s);

		JsonBoolean &operator=(const bool &b);

	private:

		bool _value;


	};

};

#endif
