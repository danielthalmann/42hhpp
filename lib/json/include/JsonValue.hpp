#ifndef JSONVALUE_HPP
#define JSONVALUE_HPP

namespace json
{
		
	class JsonValue
	{

	public:

		std::string getValueType();


	private:

		JsonType _valueType;


	};

};

#endif
