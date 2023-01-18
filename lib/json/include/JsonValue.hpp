#ifndef JSONVALUE_HPP
#define JSONVALUE_HPP

namespace json
{
	class JsonValue
	{

	public:

		typedef enum JsonType_e
		{
			json_type_null,
			json_type_string,
			json_type_number,
			json_type_object,
			json_type_array,
			json_type_true,
			json_type_false

		} JsonType;


		JsonValue() {};
		virtual ~JsonValue() {};

		JsonType getValueType();


	protected:

		JsonType _valueType;


	};

};

#endif
