#include <JsonString.hpp>

namespace json
{

    JsonString &JsonString::operator=(std::string s)
    {
        _value = s;
        return *this;
    }

}


