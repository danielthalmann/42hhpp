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
        JsonValue *j = new JsonString();
        _pos++;
        std::string buf(255, 0);
        size_t i = 0;

        while (_pos < _s.length())
        {
            if (_s[_pos] == '"'){
                break;
            }
            if (_s[_pos] == '\\')
            {
                _pos++;
                if (_pos < _s.length())
                {

                }
            }

            buf[i] = _s[_pos];
            i++;
            _pos++;
        }

        j->set(buf);
        return j;
    }

    JsonValue *Json::parseNumber()
    {
        return NULL;
    }
}


