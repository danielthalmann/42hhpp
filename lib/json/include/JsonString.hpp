#ifndef JSONSTRING_HPP
#define JSONSTRING_HPP

namespace json
{
		
	class JsonString
	{

	public:

		string get();
		void set(string);


	private:

		string _value;


	};

};

#endif
