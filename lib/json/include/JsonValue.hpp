#ifndef JSONVALUE_HPP
#define JSONVALUE_HPP

namespace json
{
	typedef enum JsonType_t
	{
		json_type_null,
		json_type_string,
		json_type_number,
		json_type_object,
		json_type_array,
		json_type_true,
		json_type_false

	} JsonType;

	
	class JsonValue
	{

	public:

		JsonValue() {};
		virtual ~JsonValue() {};

		JsonType getValueType();


	private:

		JsonType _valueType;


	};

};

#endif
