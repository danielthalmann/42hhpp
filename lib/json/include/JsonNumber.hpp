#ifndef JSONNUMBER_HPP
#define JSONNUMBER_HPP

namespace json
{

	class JsonNumber
	{

	public:

		void setInt(int);
		void setFloat(float);
		int getInt();
		float getFloat();


	private:

		void* _value;
		JsonType _valueType;


	};
	
};

#endif
