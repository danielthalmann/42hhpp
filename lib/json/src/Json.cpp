#include <Json.hpp>

namespace json
{
    Json::Json(const std::string &s)
    {
        _s = s;
        _pos = 0;
    }

    Json::~Json()
    {

    }
    
    JsonValue *Json::parseValue()
    {

        JsonValue *j = NULL;

        while (_pos < _s.length())
        {
            switch (_s[_pos])
            {
                case '{':
                    j = parseObject();
                break;
                case '[':
                    j = parseArray();
                break;
                case '"':
                    j = parseString();

            }
            _pos++;
        }

        return j;

    };

    JsonValue *Json::parseObject()
    {

        JsonValue *j = new JsonObject();
        return j;

    };

    JsonValue *Json::parseArray()
    {
        return NULL;
    }

    JsonValue *Json::parseString()
    {
        return NULL;
    }

    JsonValue *Json::parseNumber()
    {
        return NULL;
    }
}


